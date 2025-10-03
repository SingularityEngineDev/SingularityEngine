#ifndef _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_
#define _SNGL_IO_MEMORYMAPPEDFILE_H_INCLUDED_

#include <sngl/io/OsFile.h>

namespace sngl::io
{
	class MemoryMappedFile final : public OsFile
	{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
		void* m_mappingHandle;
#endif
		size_t m_currentReadOffset;
		// size_t m_currentWriteOffset; // TODO: Implement memory-mapped writes
		void* m_data;

	public:
		MemoryMappedFile(const std::string_view path);
		~MemoryMappedFile() override;

		size_t readSync(void* dest, size_t requestedSize) const override;
	};
}

#endif