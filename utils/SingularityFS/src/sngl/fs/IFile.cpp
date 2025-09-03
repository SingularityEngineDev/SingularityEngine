#include <sngl/fs/IFile.h>
#include <sngl/fs/MemoryMappedFile.h>
#include <cassert>

using IFile = sngl::fs::IFile;

std::unique_ptr<IFile> IFile::OpenRO(const std::string& path, bool memoryMapped)
{
	if (memoryMapped)
		return std::make_unique<fs::MemoryMappedFile>(path);
	else
		return nullptr;
}