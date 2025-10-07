#ifndef _SNGL_IO_BASEFILE_H_INCLUDED_
#define _SNGL_IO_BASEFILE_H_INCLUDED_

#include <sngl/io/IFile.h>

namespace sngl::io
{
	class BaseFile : public IFile
	{
	public:
		BaseFile(const std::string_view path);
		virtual ~BaseFile();

		inline size_t getSize() const override { return m_fileSize; };
		virtual size_t readSync(void* dest, size_t requestedSize) const override = 0;

	protected:
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
		using filehandle_t = void*;
#elif defined(SNGL_BUILD_PLATFORM_UNIX)
		using filehandle_t = int;
#endif

		inline const std::string& getPath() const { return m_path; }
		inline filehandle_t getFileHandle() const { return m_fileHandle; }

	private:
		std::string m_path;
		size_t m_fileSize;

		filehandle_t m_fileHandle;
	};
}

#endif
