#include <sngl/shared/SnglPak/structs.h>
#include <sngl/io/IFile.h>

namespace fs = std::filesystem;

class Application
{
private:
	// local type aliases
	using TocEntry = sngl::shared::sngl_pak::TocEntry;
	using IFile = sngl::io::IFile;

	// typedefs
	SNGL_BEGIN_PACK
		struct StorageTocEntry : TocEntry
	{
		inline StorageTocEntry(const std::string& archivePath, size_t filesize, size_t blockIndex, const std::string& _path)
			: TocEntry(archivePath, filesize, blockIndex), path(_path)
		{
		}

		std::string path;
	} SNGL_PACK;
	SNGL_END_PACK

	// constants
	static constexpr size_t BLOCK_SIZE_THRESHOLD = (1 << 18);
	static constexpr size_t DEFAULT_LZ4_OUTBUFFER_SIZE = LZ4_COMPRESSBOUND(BLOCK_SIZE_THRESHOLD);


	// data
	std::string m_outputPath;
	std::vector<std::string> m_filesToInclude;
	std::vector<StorageTocEntry> m_tocEntries;
	std::ofstream m_outputFile;
	std::vector<char> m_blockdata;
	std::vector<char> m_lz4outbuf;
	size_t m_currentBlockIndex;
	size_t m_currentBlockSize;
	size_t m_currentBlockOffset;
	size_t m_currentLz4BufferSize;

public:
	Application(std::string&& outputPath, std::vector<std::string>&& filesToInclude)
		: m_outputPath(std::move(outputPath)), 
		m_filesToInclude(std::move(filesToInclude)), 
		m_outputFile(m_outputPath, std::ios::binary | std::ios::trunc),
		m_blockdata(BLOCK_SIZE_THRESHOLD),
		m_lz4outbuf(DEFAULT_LZ4_OUTBUFFER_SIZE),
		m_currentBlockIndex(0),
		m_currentBlockSize(m_blockdata.size()),
		m_currentBlockOffset(0),
		m_currentLz4BufferSize(m_lz4outbuf.size())
	{
		m_tocEntries.reserve(m_filesToInclude.size());
	}

	void run()
	{
		for (const auto& path : m_filesToInclude)
		{
			fmt::println("Processing {}", path);

			if (!fs::exists(path))
			{
				fmt::println("Skipping {}. File doesn't exist.", path);
				continue;
			}

			if (!fs::is_directory(path))
			{
				addFile(path);
				continue;
			}

			std::string root = fs::path(path).parent_path().generic_string();
			for (const auto& entry : fs::recursive_directory_iterator(path))
			{
				if (entry.is_directory())
					continue;

				std::string p = entry.path().generic_string();
				fmt::println("Processing {}", p);
				addDirectoryFile(p, root);
			}
		}

		for (const auto& entry : m_tocEntries)
		{
			TocEntry toc = static_cast<TocEntry>(entry);
			m_outputFile.write(reinterpret_cast<const char*>(&toc), sizeof(TocEntry));
		}

		{
			size_t entries = m_tocEntries.size();
			m_outputFile.write(reinterpret_cast<const char*>(&entries), sizeof(size_t));
		}
	}

private:
	// for standalone files
	void addFile(const std::string& path)
	{
		fs::path p(path);
		assert(!fs::is_directory(p));
		assert(p.has_filename());

		addToToc(p.filename().generic_string(), path);

	}

	// for files inside directories
	void addDirectoryFile(const std::string& path, const std::string& root)
	{
		assert(!fs::is_directory(path));
		
		std::string archivePath = fs::relative(path, root).generic_string();
		addToToc(archivePath, path);
	}

	void addToToc(const std::string& archivePath, const std::string& filePath)
	{
		auto file = IFile::Open(filePath, IFile::IoType::IT_MAPPED);
		size_t filesize = file->getSize();
		m_tocEntries.emplace_back(archivePath, filesize, m_currentBlockIndex, filePath);

		// fill the block data with file data, if current block size + current file size exceeds the threshold,
		// compress the block, write compressed data to the file and create a new block
		if (m_currentBlockSize + filesize > m_blockdata.size())
		{
			m_currentBlockSize += filesize;
			m_currentLz4BufferSize = LZ4_compressBound(m_currentBlockSize);
			m_lz4outbuf.resize(m_currentLz4BufferSize);
			m_blockdata.resize(m_currentBlockSize);
		}

		// write file contents to archive, TOC is written at the end
		while (true)
		{
			size_t readSize = file->readSync(m_blockdata.data() + m_currentBlockOffset, filesize);
			if (readSize == 0)
				break;

			m_currentBlockOffset += readSize;
		}

		if (m_currentBlockSize >= BLOCK_SIZE_THRESHOLD)
		{
			int toWrite = LZ4_compress_default(m_blockdata.data(), m_lz4outbuf.data(), m_currentBlockSize, m_currentLz4BufferSize);
			if (toWrite == 0)
				throw std::runtime_error(fmt::format("Failed to compress block {}", m_currentBlockIndex));

			m_outputFile.write(m_lz4outbuf.data(), toWrite);
			m_currentBlockSize = BLOCK_SIZE_THRESHOLD;
			m_currentBlockOffset = 0;
			m_currentLz4BufferSize = DEFAULT_LZ4_OUTBUFFER_SIZE;
			m_currentBlockIndex++;
		}
	}
};

int main(int argc, char** argv)
{
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
		fmt::println("{}\n\n{}", e.what(), program.help().str());
		return -1;
	}

	std::string outputPath = program.get<std::string>("-o");
	std::vector<std::string> filesToInclude = program.get<std::vector<std::string>>("files");

	fmt::print("Writing assets to: {}\n", outputPath);

	Application app(std::move(outputPath), std::move(filesToInclude));

	try
	{
		app.run();
	}
	catch (const std::runtime_error& e)
	{
		fmt::println("Application error: {}", e.what());
		return -1;
	}

	return 0;
}