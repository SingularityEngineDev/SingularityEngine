#ifndef _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_
#define _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_

#include <sngl/io/IFile.h>

namespace sngl::io
{
	class MemoryMappedFile final : public IFile
	{
	public:
		MemoryMappedFile(const std::string_view path);
		~MemoryMappedFile() override;
	};
}

#endif