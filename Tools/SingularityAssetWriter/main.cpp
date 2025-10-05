#include <sngl/shared/SinularityPak/entries.h>

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
		std::cout << e.what() << "\n\n" << program << "\n";
		return -1;
	}

	std::string outputPath = program.get<std::string>("-o");
	std::vector<std::string> filesToInclude = program.get<std::vector<std::string>>("files");
}