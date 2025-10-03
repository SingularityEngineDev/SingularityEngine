#ifndef _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_
#define _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_

#include <sngl/io/IFile.h>
#include <sngl/shared/WindowsHeaders.h>

namespace sngl::io
{
	class MemoryMappedFile final : public IFile
	{
		using handle_t = void*;

#ifdef SNGL_BUILD_PLATFORM_WINDOWS
		handle_t m_fileHandle;
		handle_t m_mappingHandle;
#endif
		size_t m_fileSize;
		void* m_data;

	public:
		MemoryMappedFile(const std::string_view path);
		~MemoryMappedFile() override;

		const size_t getSize() const;
	};
}

#endif