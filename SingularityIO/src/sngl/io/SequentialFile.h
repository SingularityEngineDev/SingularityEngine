#ifndef _SNGL_IO_SEQUENTIALFILE_H_INCLUDED_
#define _SNGL_IO_SEQUENTIALFILE_H_INCLUDED_

#include <sngl/shared/WindowsHeaders.h>

namespace sngl::io
{
	class SequentialFile final : public IFile
	{
		using handle_t = void*;
		handle_t m_fileHandle;

		std::string m_path;
		size_t m_fileSize;
		mutable size_t m_currentReadOffset;
		// size_t m_currentWriteOffset; // TODO: Implement memory-mapped writes

	public:
		SequentialFile(const std::string_view path);
		~SequentialFile() override;

		inline size_t getSize() const override { return m_fileSize; }
		size_t readSync(void* dest, size_t requestedSize) const override;

	};
}

#endif