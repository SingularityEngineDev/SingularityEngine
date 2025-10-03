#include <sngl/io/MemoryMappedFile.h>

using namespace sngl::io;

MemoryMappedFile::MemoryMappedFile(const std::string_view path)
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	m_fileHandle = CreateFile(path.data(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (!VALID_HANDLE(m_fileHandle))
		throw std::runtime_error(fmt::format("Failed to open {}.", path.data()));

	{
		DWORD sizeHigh;
		DWORD sizeLow = GetFileSize(m_fileHandle, &sizeHigh);
		m_fileSize = (static_cast<size_t>(sizeHigh) << 32) | static_cast<size_t>(sizeLow);
	}

	m_mappingHandle = CreateFileMapping(m_fileHandle, nullptr, PAGE_READONLY, 0, 0, path.data());
	if (!VALID_HANDLE(m_mappingHandle))
	{
		CloseHandle(m_fileHandle);
		throw std::runtime_error(fmt::format("Failed to create mapping object for {}.", path.data()));
	}
	
	m_data = MapViewOfFile(m_mappingHandle, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (!m_data)
	{
		CloseHandle(m_mappingHandle);
		CloseHandle(m_fileHandle);
		throw std::runtime_error(fmt::format("Failed to map {} for process address space.", path.data()));
	}
#else
	#error Memory mapped IO has not been implemented for platforms other than Windows yet. 
#endif
}

MemoryMappedFile::~MemoryMappedFile()
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	if (m_data)
		UnmapViewOfFile(m_data);

	if (VALID_HANDLE(m_mappingHandle))
		CloseHandle(m_mappingHandle);

	if (VALID_HANDLE(m_fileHandle))
		CloseHandle(m_fileHandle);
#else
	#error Memory mapped IO has not been implemented for platforms other than Windows yet. 
#endif
}