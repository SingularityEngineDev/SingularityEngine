#include <sngl/io/SequentialFile.h>
#include <sngl/shared/WindowsHeaders.h>
	
using namespace sngl::io;

size_t SequentialFile::readSync(void* dest, size_t requestedSize) const
{
	size_t fileSize = getSize();
	filehandle_t fileHandle = getFileHandle();
	if (m_currentReadOffset + requestedSize > fileSize)
		requestedSize = fileSize - m_currentReadOffset;

	size_t bytesRead = 0;
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	size_t chunks = requestedSize / ULONG_MAX;
	DWORD remaining = requestedSize % ULONG_MAX;
	
	auto read = [this, dest, fileHandle](DWORD size) -> DWORD
		{
			DWORD rfBytesRead;
			if (!ReadFile(fileHandle, static_cast<uint8_t*>(dest) + m_currentReadOffset, size, &rfBytesRead, nullptr))
				throw std::runtime_error(fmt::format("Failed to read {}.", getPath()));

			m_currentReadOffset += rfBytesRead;
			return rfBytesRead;
		};
	
	for (size_t i = chunks; i > 0; i--)
		bytesRead += read(ULONG_MAX);

	if (remaining > 0)
		bytesRead =+ read(remaining);
#elif SNGL_BUILD_PLATFORM_UNIX
	// do something
#else
	#error Currently not implemented for platforms other than Windows and unix. Please use ofstream api.
#endif

	return bytesRead;
}