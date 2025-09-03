#include <sngl/fs/MemoryMappedFile.h>
#include <stdexcept>

using MemoryMappedFile = sngl::fs::MemoryMappedFile;

MemoryMappedFile::MemoryMappedFile(const std::string& path)
	: m_size(0), m_data(nullptr)
{
#ifdef SNGL_BUILD_TYPE_WINDOWS
	m_fileHandle = CreateFile(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
	if (m_fileHandle == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Failed to open a file");

	LARGE_INTEGER fileSize;
	if (!GetFileSizeEx(m_fileHandle, &fileSize))
	{
		cleanup();
		throw std::runtime_error("Failed to get file size");
	}
	m_size = static_cast<size_t>(fileSize.QuadPart);

	m_fileMapping = CreateFileMapping(m_fileHandle, nullptr, PAGE_READONLY, 0, 0, nullptr);
	if (!m_fileMapping)
	{
		cleanup();
		throw std::runtime_error("Failed to create file mapping");
	}

	m_data = MapViewOfFile(m_fileMapping, FILE_MAP_READ, 0, 0, 0);
	if (!m_data)
	{
		cleanup();
		throw std::runtime_error("Failed to map file data");
	}
#endif
}

MemoryMappedFile::~MemoryMappedFile()
{
	cleanup();
}

void MemoryMappedFile::cleanup()
{
#ifdef SNGL_BUILD_TYPE_WINDOWS
	if (m_data)
		UnmapViewOfFile(m_data);
	if (m_fileMapping)
		CloseHandle(m_fileMapping);
	if (m_fileHandle == INVALID_HANDLE_VALUE)
		CloseHandle(m_fileHandle);
#endif
}

MemoryMappedFile::FileCapabilitiesFlags MemoryMappedFile::getCapabilities() const
{
	return READ | MAPPED;
}

size_t MemoryMappedFile::read(void* dst, size_t size, size_t offset)
{
	return 0;
}

size_t MemoryMappedFile::write(const void* src, size_t size, size_t offset)
{
	return 0;
}