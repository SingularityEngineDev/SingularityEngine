#include <sngl/io/MemoryMappedFile.h>
#include <sngl/shared/WindowsHeaders.h>

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
#else
	#error Memory mapped IO has not been implemented for platforms other than Windows yet. 
#endif
}

size_t MemoryMappedFile::readSync(void* dest, size_t requestedSize) const
{
	size_t fileSize = getSize();
	if (requestedSize + m_currentReadOffset > fileSize)
		requestedSize = fileSize - m_currentReadOffset;

	std::memcpy(dest, static_cast<const uint8_t*>(m_data) + m_currentReadOffset, requestedSize);
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
#else
	#error Memory mapped IO has not been implemented for platforms other than Windows yet. 
#endif
}