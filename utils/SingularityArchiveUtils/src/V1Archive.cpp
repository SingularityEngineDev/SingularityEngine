#include "V1Archive.h"

using namespace sngl::archive_utils;

bool V1Archive::addFile(const fs::path& path)
{
	if (fs::is_directory(path))
		return false;

	SFileEntry entry{};
	entry.fullpath = path.generic_string();
	entry.vpath = path.filename().generic_string();
	
	// TODO: set offset and size

	m_files.emplace_back(std::move(entry));
	return true;
}

bool V1Archive::write(const fs::path& outPath)
{
	return true;
}

uint64_t V1Archive::getTableSize()
{
	constexpr float BASE_LOAD_FACTOR = 0.9f;
	uint64_t size = static_cast<uint64_t>(
		std::ceil(static_cast<float>(m_files.size()) / BASE_LOAD_FACTOR)
	);

	return nextPoT(size);
}