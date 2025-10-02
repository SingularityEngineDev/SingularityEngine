#include <sngl/io/MemoryMappedFile.h>
#include <sngl/io/SequentialFile.h>

using namespace sngl::io;
using IoType = IFile::IoType;

std::unique_ptr<IFile> IFile::Open(const std::string_view path, IoType type)
{
	if (type == IoType::IT_MAPPED)
		return std::make_unique<MemoryMappedFile>(path);

	return std::make_unique<SequentialFile>(path);
}