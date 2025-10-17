#include <sngl/io/Filesystem.h>

using namespace sngl::io;

IFilesystem* IFilesystem::create()
{
	return new Filesystem();
}

bool Filesystem::mountArchive(const std::string_view path)
{
	return true;
}

bool Filesystem::openFile(const std::string_view path, const std::string_view mountPath)
{
	return true;
}