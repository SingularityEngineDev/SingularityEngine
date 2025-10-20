namespace fs = std::filesystem;

using ArchiveHeader = sngl::shared::spak::ArchiveHeader;
using FileEntry = sngl::shared::spak::FileEntry;

class Application
{
private:
	using path_t = fs::path;

	struct MakeContext
	{
		inline MakeContext(const std::string& outFilePath)
			: outFile(outFilePath, std::ios::binary | std::ios::trunc),
			header(),
			currentBlockOffset(0),
			currentDataOffset(0),
			blockBuffer(header.blockSize),
			compressedBlockBuffer(LZ4_COMPRESSBOUND(header.blockSize))
		{ }
		
		inline void setFileCountAndCalculateOffsets(uint64_t filecount)
		{
			header.filecount = filecount;
			entries.resize(filecount);

			header.dataOffset = filecount * sizeof(FileEntry);
		}

		void commitBlock()
		{
			int compressedSize = LZ4_compress_default(
				blockBuffer.data(), 
				compressedBlockBuffer.data(),
				static_cast<int>(header.blockSize), 
				static_cast<int>(compressedBlockBuffer.size())
			);

			outFile.write(reinterpret_cast<const char*>(&compressedSize), sizeof(decltype(compressedSize)));
			outFile.write(compressedBlockBuffer.data(), compressedSize);
			currentBlockOffset = 0;
		}

		void writeEntry(uint64_t index)
		{
			uint64_t fileOffset = header.filetableOffset + index * sizeof(FileEntry);
			uint64_t currentFileOffset = outFile.tellp();
			outFile.seekp(fileOffset);
			outFile.write(reinterpret_cast<const char*>(entries.data() + index), sizeof(FileEntry));
			outFile.seekp(currentFileOffset);
		}

		std::ofstream outFile;

		ArchiveHeader header;
		std::vector<FileEntry> entries;

		uint64_t currentBlockOffset;
		uint64_t currentDataOffset;
		std::vector<char> blockBuffer;
		std::vector<char> compressedBlockBuffer;
	};

public:
	int make(const std::string& archivePath, const std::vector<std::string>& paths)
	{
		std::vector<std::pair<const std::string, std::string>> files;
		MakeContext ctx(archivePath);
		files.reserve(paths.size()); // reduce allocations, best case scenario 

		for (const auto& path : paths)
		{
			if (not fs::is_directory(path))
				files.emplace_back(path, fs::path(path).filename().string());

			for (const auto& entry : fs::recursive_directory_iterator(path))
			{
				if (entry.is_directory())
					continue;

				files.emplace_back(entry.path().generic_string(), fs::relative(entry, path).generic_string());
			}
		}

		ctx.setFileCountAndCalculateOffsets(files.size());
		ctx.outFile.write(reinterpret_cast<const char*>(&ctx.header), sizeof(ctx.header));

		for (uint64_t i = 0; i < ctx.header.filecount; i++)
		{
			const auto& path = files[i];
			auto& entry = ctx.entries[i];
			std::memset(&entry, 0, sizeof(entry));
			std::ifstream file(path.first, std::ios::binary);

			entry.startBlockOffset = ctx.outFile.tellp();
			entry.startBlockDataOffset = ctx.currentBlockOffset;
			entry.blockCount = 1;
			std::memcpy(entry.path, path.second.data(), path.second.size());

			fmt::println("Processing: {}", path.first);

			while (file)
			{
				file.read(ctx.blockBuffer.data(), ctx.header.blockSize - ctx.currentBlockOffset);
				ctx.currentBlockOffset += file.gcount();

				if (ctx.currentBlockOffset == ctx.header.blockSize)
				{
					ctx.commitBlock();
					entry.blockCount++;
				}
			}

			ctx.writeEntry(i);
		}

		return 0;
	}
};

int main(int argc, char** argv)
{
	argparse::ArgumentParser program("SingularityAssetWriter");
	
	// subcommands
	// make
	argparse::ArgumentParser make_parser("make");

	make_parser.add_argument("archive")
		.nargs(1)
		.required();
	make_parser.add_argument("files")
		.nargs(argparse::nargs_pattern::at_least_one)
		.required();

	program.add_subparser(make_parser);

	try
	{
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << "\n" << program << "\n";
		return -1;
	}

	Application app;
	if (program.is_subcommand_used(make_parser))
		return app.make(make_parser.get("archive"), make_parser.get<std::vector<std::string>>("files"));
	else
		std::cout << program << "\n";

	return 0;
}