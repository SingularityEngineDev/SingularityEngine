#include <sngl/io/MemoryMappedFile.h>
#include <sngl/shared/WindowsHeaders.h>
#include <sngl/shared/UnixHeaders.h>

using namespace sngl::io;

MemoryMappedFile::MemoryMappedFile(const std::string_view path)
	: BaseFile(path)
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	m_mappingHandle = CreateFileMapping(getFileHandle(), nullptr, PAGE_READONLY, 0, 0, nullptr);
	if (!VALID_HANDLE(m_mappingHandle))
	{
		throw std::runtime_error(fmt::format("Failed to create mapping object for {}. Code: {}", path.data(), GetLastError()));
	}
	
	m_data = MapViewOfFile(m_mappingHandle, FILE_MAP_READ, 0, 0, getSize());
	if (!m_data)
	{
		CloseHandle(m_mappingHandle);
		throw std::runtime_error(fmt::format("Failed to map {} for process address space. Code: {}", path.data(), GetLastError()));
	}
#elif defined(SNGL_BUILD_PLATFORM_UNIX)
	auto fd = getFileHandle();
	m_data = mmap64(0, getSize(), PROT_READ, MAP_SHARED, fd, 0);
	if (!m_data)
		throw std::runtime_error(fmt::format("Failed to map {} for process address space", path.data()));
#endif
}

size_t MemoryMappedFile::readSync(void* dest, size_t requestedSize) const
{
	size_t fileSize = getSize();
	if (m_currentReadOffset >= fileSize) return 0;
	if (requestedSize + m_currentReadOffset > fileSize)
		requestedSize = fileSize - m_currentReadOffset;

	memcpy(dest, static_cast<const uint8_t*>(m_data) + m_currentReadOffset, requestedSize);
	m_currentReadOffset += requestedSize;
	return requestedSize;
}

MemoryMappedFile::~MemoryMappedFile()
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	if (m_data)
		UnmapViewOfFile(m_data);

	if (VALID_HANDLE(m_mappingHandle))
		CloseHandle(m_mappingHandle);
#elif SNGL_BUILD_PLATFORM_UNIX
	if (munmap(m_data, getSize()) != 0)
		std::abort();
#endif
}