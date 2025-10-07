#include <sngl/io/BaseFile.h>
#include <sngl/shared/WindowsHeaders.h>
#include <sngl/shared/UnixHeaders.h>

using namespace sngl::io;

BaseFile::BaseFile(const std::string_view path)
	: m_path(path)
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	m_fileHandle = CreateFile(m_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!VALID_HANDLE(m_fileHandle))
		throw std::runtime_error(fmt::format("Failed to open: {}", m_path));

	{
		DWORD fileSizeHigh;
		DWORD fileSizeLow = GetFileSize(m_fileHandle, &fileSizeHigh);
		m_fileSize = (static_cast<size_t>(fileSizeHigh) << 32) | fileSizeLow;
	}
#elif SNGL_BUILD_PLATFORM_UNIX
	m_fileHandle = open64(m_path.c_str(), O_RDWR, 0666);
	if (m_fileHandle == -1)
		throw std::runtime_error(fmt::format("Failed to open: {}", m_path));
	
	struct stat64 stat;
	if (fstat64(m_fileHandle, &stat) != 0)
		throw std::runtime_error(fmt::format("Failed to read size of {}", m_path));
	m_fileSize = stat.st_size;
#endif
}

BaseFile::~BaseFile()
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	if (m_fileHandle)
		CloseHandle(m_fileHandle);
#elif defined(SNGL_BUILD_PLATFORM_UNIX)
	if (m_fileHandle)
		if (close(m_fileHandle) != 0)
			std::abort();
#endif
}