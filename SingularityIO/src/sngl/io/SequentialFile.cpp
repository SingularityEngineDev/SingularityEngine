#include <sngl/io/SequentialFile.h>

using namespace sngl::io;

SequentialFile::SequentialFile(const std::string_view path)
	: m_path(path)
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	m_fileHandle = CreateFile(m_path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!VALID_HANDLE(m_fileHandle))
		throw std::runtime_error(fmt::format("Failed to open {}", m_path));

	{
		DWORD fileSizeHigh;
		DWORD fileSizeLow = GetFileSize(m_fileHandle, &fileSizeHigh);
		m_fileSize = (static_cast<size_t>(fileSizeHigh) << 32) | fileSizeLow;
	}
#endif
}

size_t SequentialFile::readSync(void* dest, size_t requestedSize) const
{
	if (m_currentReadOffset + requestedSize > m_fileSize)
		requestedSize = m_fileSize - m_currentReadOffset;

	size_t bytesRead = 0;
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	size_t chunks = requestedSize / ULONG_MAX;
	DWORD remaining = requestedSize % ULONG_MAX;
	
	auto read = [this, dest](DWORD size) -> DWORD
		{
			DWORD rfBytesRead;
			if (!ReadFile(m_fileHandle, static_cast<uint8_t*>(dest) + m_currentReadOffset, size, &rfBytesRead, nullptr))
				throw std::runtime_error(fmt::format("Failed to read {}.", m_path));

			m_currentReadOffset += rfBytesRead;
			return rfBytesRead;
		};
	
	for (size_t i = chunks; i > 0; i--)
		bytesRead += read(ULONG_MAX);

	if (remaining > 0)
		bytesRead =+ read(remaining);
#else
	#error Currently not implemented for platforms other than Windows. Please use ofstream api.
#endif

	return bytesRead;
}

SequentialFile::~SequentialFile()
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	if (m_fileHandle)
		CloseHandle(m_fileHandle);
#endif
}