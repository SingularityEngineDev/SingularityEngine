#include <sngl/fs/IFile.h>
#include <argparse/argparse.hpp>

int main(int argc, char** argv)
{
	argparse::ArgumentParser parser("io_subsystem_app.exe");
	parser.add_argument("file_to_open")
		.nargs(1)
		.required();

	try
	{
		parser.parse_args(argc, argv);
	}
	catch (const std::runtime_error& e)
	{
		std::cerr << e.what() << "\n";
		std::cout << parser << "\n";
		return -1;
	}

	std::string path = parser.get<std::string>("file_to_open");
	auto file = sngl::fs::IFile::OpenRO(path);

	return 0;
}