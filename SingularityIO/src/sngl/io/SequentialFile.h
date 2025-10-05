#ifndef _SNGL_IO_SEQUENTIALFILE_H_INCLUDED_
#define _SNGL_IO_SEQUENTIALFILE_H_INCLUDED_

#include <sngl/io/BaseFile.h>

namespace sngl::io
{
	class SequentialFile final : public BaseFile
	{
		mutable size_t m_currentReadOffset = 0;
		// size_t m_currentWriteOffset; // TODO: Implement memory-mapped writes

	public:
		inline SequentialFile(const std::string_view path) 
			: BaseFile(path) 
		{}

		inline ~SequentialFile() override {};

		size_t readSync(void* dest, size_t requestedSize) const override;
	};
}

#endif