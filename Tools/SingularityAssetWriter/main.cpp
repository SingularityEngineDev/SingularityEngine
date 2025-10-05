#include <sngl/shared/SnglPak/structs.h>
#include <sngl/io/IFile.h>

namespace fs = std::filesystem;

// type aliases
using TocEntry = sngl::shared::sngl_pak::TocEntry;

// extending types
SNGL_BEGIN_PACK
struct ExtendedTocEntry : TocEntry
{
	inline ExtendedTocEntry(const std::string& _filename, size_t filesize, size_t blockIndex, const std::string& _path)
		: TocEntry(_filename, filesize, blockIndex), filename(_filename), path(_path)
	{ }

	std::string filename;
	std::string path;
} SNGL_PACK;
SNGL_END_PACK

// constants
constexpr size_t BLOCK_SIZE_THRESHOLD = (1 << 18); // 256kb

int main(int argc, char** argv)
{
	using IFile = sngl::io::IFile;

	// parse arguments
	argparse::ArgumentParser program("SingularityAssetWriter", "1.0");
	program.add_argument("-o", "--output")
		.nargs(1)
		.default_value("output.pak")
		.help("Output path");

	program.add_argument("files")
		.nargs(argparse::nargs_pattern::at_least_one)
		.required()
		.help("List of files to include in the asset package");

	try
	{
		program.parse_args(argc, argv);
	}
	catch (const std::runtime_error& e)
	{
		fmt::println("{}\n\n{}", e.what(), program.print_help());
		return -1;
	}

	std::string outputPath = program.get<std::string>("-o");
	std::vector<std::string> filesToInclude = program.get<std::vector<std::string>>("files");

	fmt::print("Writing assets to: {}\n", outputPath);

	try
	{
		std::vector<ExtendedTocEntry> tocEntries;
		tocEntries.reserve(filesToInclude.size()); // reduce allocations count

		std::ofstream outFile(outputPath, std::ios::binary | std::ios::trunc);
		std::vector<uint8_t> buffer(BLOCK_SIZE_THRESHOLD);

		size_t blockIndex = 0;
		{
			size_t uncompressedBlockSize = 0;
			auto addToToc = [&blockIndex, &uncompressedBlockSize, &tocEntries](const std::string& path)
				{
					assert(!fs::is_directory(path));

					size_t filesize = IFile::GetSize(path);
					std::string filename = fs::path(path).filename().generic_string();

					uncompressedBlockSize += filesize;
					tocEntries.emplace_back(std::move(filename), filesize, blockIndex, path);

					if (uncompressedBlockSize > BLOCK_SIZE_THRESHOLD)
						blockIndex++;
				};

			auto addToTocDir = [&blockIndex, &uncompressedBlockSize, &tocEntries](const std::string& path, const std::string& rootDir)
				{
					assert(!fs::is_directory(path));

					size_t filesize = IFile::GetSize(path);
					std::string filename = fs::relative(path, rootDir).generic_string();

					uncompressedBlockSize += filesize;
					tocEntries.emplace_back(std::move(filename), filesize, blockIndex, path);

					if (uncompressedBlockSize > BLOCK_SIZE_THRESHOLD)
						blockIndex++;
				};

			auto writeFileToArchive = [&outFile, &buffer](const std::string& path)
				{
					auto file = IFile::Open(path, IFile::IoType::IT_MAPPED);

					size_t readSize = 0;
					while (true)
					{
						readSize = file->readSync(buffer.data(), buffer.size());
						if (readSize == 0)
							break;

						outFile.write((const char*)buffer.data(), readSize);
					}
				};

			for (const auto& path : filesToInclude)
			{
				fmt::println("Processing {}", path);

				if (not fs::exists(path))
				{
					fmt::println("Failed to process {}. File or directory doesn't exist", path);
					continue;
				}

				if (not fs::is_directory(path))
				{
					addToToc(path);
					writeFileToArchive(path);
				}

				std::string relativeTo = fs::path(path).parent_path().generic_string();
				for (const auto& entry : fs::recursive_directory_iterator(path))
				{
					const fs::path& entryPath = entry.path();
					const std::string entryPathStr = entryPath.generic_string();

					if (entry.is_directory())
						continue;

					fmt::println("Processing {}", entryPathStr);
					addToTocDir(entryPathStr, relativeTo);
					writeFileToArchive(entryPathStr);
				}
			}

			for (const auto& extendedTocEntry : tocEntries)
			{
				const auto& filename = extendedTocEntry.filename;
				const TocEntry& tocEntry = static_cast<const TocEntry&>(extendedTocEntry);
				outFile.write((const char*)&tocEntry, sizeof(TocEntry));
				outFile.write(filename.data(), filename.size());
			}
		}
	}
	catch (const std::runtime_error& e)
	{
		fmt::println("Critical error: {}", e.what());
		return -1;
	}

	return 0;
}