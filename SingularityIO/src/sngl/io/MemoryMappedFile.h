#ifndef _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_
#define _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_

#include <sngl/io/BaseFile.h>

namespace sngl::io
{
	class MemoryMappedFile final : public BaseFile
	{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
		void* m_mappingHandle;
#endif
		mutable size_t m_currentReadOffset = 0;
		// size_t m_currentWriteOffset; // TODO: Implement memory-mapped writes
		void* m_data;

	public:
		MemoryMappedFile(const std::string_view path);
		~MemoryMappedFile() override;

		size_t readSync(void* dest, size_t requestedSize) const override;
	};
}

#endif