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
		size_t m_currentReadOffset;
		// size_t m_currentWriteOffset; // TODO: Implement memory-mapped writes
		void* m_data;

	public:
		MemoryMappedFile(const std::string_view path);
		~MemoryMappedFile() override;

		inline size_t getSize() const override { return m_fileSize; };
		size_t readSync(void* dest, size_t requestedSize) const override;
	};
}

#endif