#include "V1Archive.h"
#include <xxhash.h>
#include <fstream>
#include <cassert>

using namespace sngl::archive_utils;

struct V1Archive::WriteContext
{
	inline WriteContext(const fs::path& archivePath, const uint64_t fileCount, const uint64_t htSize)
		: archiveFile(archivePath.generic_string(), std::ios::binary | std::ios::trunc),
		slots(htSize),
		hashtableOffset(sizeof(V1Header)), 
		dataOffset(hashtableOffset + (sizeof(V1HashtableSlot) * htSize))
	{
		V1Header h{ htSize, fileCount };
		archiveFile.write(reinterpret_cast<const char*>(&h), sizeof(V1Header));
	}

	std::ofstream archiveFile;
	std::vector<V1HashtableSlot> slots;

	const uint64_t hashtableOffset;
	const uint64_t dataOffset;
};

bool V1Archive::addFile(const fs::path& path, bool shouldCompress)
{
	if (fs::is_directory(path))
		return false;

	m_files.emplace_back(path.generic_string(), path.filename().generic_string(), shouldCompress);
	return true;
}

bool V1Archive::addFile(const fs::path& base, const fs::path& relative, bool shouldCompress)
{
	auto combined = base / relative;
	if (fs::is_directory(combined))
		return false;

	m_files.emplace_back(combined.generic_string(), relative.generic_string(), shouldCompress);
	return true;
}

bool V1Archive::write(const fs::path& outPath)
{
	WriteContext ctx(outPath, m_files.size(), getTableSize());

	size_t currentDataOffset = ctx.dataOffset;
	for (const auto& entry : m_files)
	{
		if (not entry.fullpath.has_value())
			continue;

		auto filenameHash = XXH3_128bits(entry.vpath.data(), sizeof(entry.vpath.size()));

		auto h1 = filenameHash.low64 & (ctx.slots.size() - 1);
		auto h2 = (filenameHash.high64 & (ctx.slots.size() - 1)) | 1;

		const std::string& entryPath = entry.fullpath.value();

		V1FileMetadata md{};
		md.dataOffset = currentDataOffset;
		md.size = fs::file_size(entryPath);
		currentDataOffset += md.size;
		md.flags = 0;
		assert(entry.vpath.size() <= sizeof(md.path));
		std::memcpy(md.path, entry.vpath.data(), entry.vpath.size());

		cuckooInsertion(ctx.slots, h1, h2, std::move(md));
	}

	// write hashtable
	ctx.archiveFile.write(reinterpret_cast<const char*>(ctx.slots.data()), sizeof(V1HashtableSlot) * ctx.slots.size());

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

bool V1Archive::cuckooInsertion(std::vector<V1HashtableSlot>& table, uint64_t h1, uint64_t h2, V1FileMetadata fileMetadata)
{
	constexpr size_t MAX_KICKS = 100;

	uint64_t keyHash = h1 ^ h2;
	uint64_t idx = h1;
	uint64_t curKey = keyHash;

	for (size_t kick = 0; kick < MAX_KICKS; kick++)
	{
		if (not table[idx].isOccupied)
		{
			table[idx] = { curKey, std::move(fileMetadata) };
			return true;
		}

		V1HashtableSlot evictedSlot = std::move(table[idx]);
		table[idx] = { curKey, std::move(fileMetadata) };

		uint64_t newLo = evictedSlot.key;
		uint64_t newHi = evictedSlot.key >> 32;

		idx = (idx == (newLo & (table.size() - 1))) 
			? (newHi & (table.size() - 1)) | 1 
			: (newLo & (table.size() - 1));

		curKey = evictedSlot.key;
		fileMetadata = std::move(evictedSlot.value);
	}

	return false;
}