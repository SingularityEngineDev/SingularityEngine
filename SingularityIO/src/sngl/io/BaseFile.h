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
		virtual size_t readSync(void* dest, size_t requestedSize) const = 0;

	protected:
		inline const std::string& getPath() const { return m_path; }
		inline void* getFileHandle() const { return m_fileHandle; }

	private:
		std::string m_path;
		size_t m_fileSize;
		void* m_fileHandle;
	};
}

#endif
