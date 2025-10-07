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

	// data
	std::string m_outputPath;
	std::vector<std::string> m_filesToInclude;
	std::vector<StorageTocEntry> m_tocEntries;
	std::ofstream m_outputFile;
	std::vector<char> m_buffer;
	size_t m_currentBlockIndex;
	size_t m_currentBlockSize;

public:
	Application(std::string&& outputPath, std::vector<std::string>&& filesToInclude)
		: m_outputPath(std::move(outputPath)), 
		m_filesToInclude(std::move(filesToInclude)), 
		m_outputFile(m_outputPath, std::ios::binary | std::ios::trunc),
		m_buffer(BLOCK_SIZE_THRESHOLD)
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
		m_tocEntries.emplace_back(archivePath, filesize, m_currentBlockSize, filePath);
		
		// write file contents to archive, TOC is written at the end
		while (true)
		{
			size_t readSize = file->readSync(m_buffer.data(), m_buffer.size());
			if (readSize == 0)
				break;

			m_outputFile.write(m_buffer.data(), readSize);
		}

		m_currentBlockSize += filesize;
		if (m_currentBlockSize >= BLOCK_SIZE_THRESHOLD)
		{
			m_currentBlockSize = 0;
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