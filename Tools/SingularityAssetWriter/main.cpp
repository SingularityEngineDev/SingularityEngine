#include <sngl/shared/SnglPak/structs.h>
#include <sngl/io/IFile.h>

namespace fs = std::filesystem;

// type aliases
using TocEntry = sngl::shared::sngl_pak::TocEntry;

// constants
constexpr size_t BLOCK_SIZE = (1 << 18); // 256kb

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
	std::ofstream outputFile(outputPath, std::ios::binary | std::ios::trunc);

	std::vector<TocEntry> tocEntries;
	tocEntries.reserve(filesToInclude.size()); // reduce allocations count

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
		}
	}

	return 0;
}