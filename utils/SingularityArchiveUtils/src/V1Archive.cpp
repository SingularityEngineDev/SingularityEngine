#include "V1Archive.h"
#include <xxhash.h>
#include <fstream>

using namespace sngl::archive_utils;

bool V1Archive::addFile(const fs::path& path, bool shouldCompress)
{
	if (fs::is_directory(path))
		return false;

	SInternalFileEntry entry{};
	entry.fullpath = path.generic_string();
	entry.vpath = path.filename().generic_string();
	entry.shouldBeCompressed = shouldCompress;

	m_files.emplace_back(std::move(entry));
	return true;
}

bool V1Archive::write(const fs::path& outPath)
{
	uint64_t htSize = getTableSize();
	std::vector<V1HashtableSlot> slots(htSize);

	for (const auto& entry : m_files)
	{
		auto filenameHash = XXH3_128bits(entry.vpath.data(), sizeof(entry.vpath.size()));

		auto h1 = filenameHash.low64 & (htSize - 1);
		auto h2 = (filenameHash.high64 & (htSize - 1)) | 1;
		cuckooInsertion(slots, h1, h2);
	}

	std::ofstream archive(outPath.generic_string(), std::ios::binary | std::ios::trunc);
	
	{
		V1Header header = { htSize, m_files.size() };
		archive.write(reinterpret_cast<const char*>(&header), sizeof(V1Header));
	}

	archive.write(reinterpret_cast<const char*>(slots.data()), sizeof(V1HashtableSlot) * slots.size());

	return true;
}

uint64_t V1Archive::getTableSize()
{
	constexpr float BASE_LOAD_FACTOR = 0.9f;
	uint64_t size = static_cast<uint64_t>(
		std::ceilf(static_cast<float>(m_files.size()) / BASE_LOAD_FACTOR)
	);

	return math_utils::nextPoT(size);
}

bool V1Archive::cuckooInsertion(std::vector<V1HashtableSlot>& table, uint64_t h1, uint64_t h2)
{
	constexpr size_t MAX_KICKS = 100;

	uint64_t keyHash = h1 ^ h2;
	uint64_t idx = h1;
	uint64_t curKey = keyHash;
	uint64_t curVal = 0; // TODO: set it

	for (size_t kick = 0; kick < MAX_KICKS; kick++)
	{
		if (not table[idx].isOccupied)
		{
			table[idx] = { curKey, curVal, true };
			return true;
		}

		V1HashtableSlot evictedSlot = std::move(table[idx]);
		table[idx] = { curKey, curVal, true };

		uint64_t newLo = evictedSlot.key;
		uint64_t newHi = evictedSlot.key >> 32;

		idx = (idx == (newLo & (table.size() - 1))) 
			? (newHi & (table.size() - 1)) | 1 
			: (newLo & (table.size() - 1));

		curKey = evictedSlot.key;
		curVal = evictedSlot.value;
	}

	return false;
}