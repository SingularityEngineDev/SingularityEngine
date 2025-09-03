#ifndef _SNGL_FS_MEMORYMAPPEDFILE_H_INCLUDED_
#define _SNGL_FS_MEMORYMAPPEDFILE_H_INCLUDED_

#include <sngl/fs/IFile.h>
#include <string>

#ifdef SNGL_BUILD_TYPE_WINDOWS
	#include <Windows.h>
#else
	#error "Other platforms are not supported at the moment"
#endif

namespace sngl::fs
{
	class MemoryMappedFile : public IFile
	{
	public:
		MemoryMappedFile(const std::string& path);
		~MemoryMappedFile() override;

		FileCapabilitiesFlags getCapabilities() const override;
		size_t getSize() const override { return m_size; }
		size_t read(void* dst, size_t size, size_t offset) override;
		size_t write(const void* buffer, size_t size, size_t offset) override;

	private:
		#ifdef SNGL_BUILD_TYPE_WINDOWS
		HANDLE m_fileHandle;
		HANDLE m_fileMapping;
		#endif

		void cleanup();

		size_t m_size;
		void* m_data;
	};
}

#endif