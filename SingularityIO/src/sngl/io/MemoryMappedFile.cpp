#include <sngl/io/MemoryMappedFile.h>
#include <sngl/shared/WindowsHeaders.h>

using namespace sngl::io;

MemoryMappedFile::MemoryMappedFile(const std::string_view path)
	: OsFile(path)
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	m_mappingHandle = CreateFileMapping(getFileHandle(), nullptr, PAGE_READONLY, 0, 0, path.data());
	if (!VALID_HANDLE(m_mappingHandle))
	{
		throw std::runtime_error(fmt::format("Failed to create mapping object for {}.", path.data()));
	}
	
	m_data = MapViewOfFile(m_mappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!m_data)
	{
		CloseHandle(m_mappingHandle);
		throw std::runtime_error(fmt::format("Failed to map {} for process address space.", path.data()));
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