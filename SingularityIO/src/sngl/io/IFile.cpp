#include <sngl/io/BaseFile.h>
#include <sngl/io/MemoryMappedFile.h>
#include <sngl/io/SequentialFile.h>

using namespace sngl::io;
using IoType = IFile::IoType;

IFile* IFile::Open(const std::string_view path, IoType type)
{
	if (type == IoType::IT_MAPPED)
		return new MemoryMappedFile(path);

	if (type == IoType::IT_AUTO && GetSize(path) >= (1 << 30))
		return new MemoryMappedFile(path);

	return new SequentialFile(path);
}

size_t IFile::GetSize(const std::string_view path)
{
	auto file = SequentialFile(path);
	return file.getSize();
}