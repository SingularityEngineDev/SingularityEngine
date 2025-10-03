#include <sngl/io/OsFile.h>
#include <sngl/shared/WindowsHeaders.h>
	
using namespace sngl::io;

OsFile::OsFile(const std::string_view path)
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
#endif
}

OsFile::~OsFile()
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	if (m_fileHandle)
		CloseHandle(m_fileHandle);
#endif
}