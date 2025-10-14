#include <sngl/io/Filesystem.h>

using namespace sngl::io;

std::unique_ptr<Filesystem> Filesystem::s_instance = nullptr;

bool Filesystem::mountArchive(const std::string_view path)
{
	return true;
}

IFilesystem* IFilesystem::Get()
{
	if (!Filesystem::s_instance)
		Filesystem::s_instance = std::make_unique<Filesystem>();

	return Filesystem::s_instance.get();
}