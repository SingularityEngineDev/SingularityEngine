#include <SingularityArchiveUtils/IArchive.h>
#include <SingularityMathUtils.h>
#include "BaseArchiveHeader.h"
#include <vector>
#include <string>
#include <optional>

namespace sngl::archive_utils
{
	struct SNGL_ARCHIVE_DATA_ALIGNMENT V1Header : public BaseArchiveHeader
	{
		inline V1Header(uint64_t htEntries, uint64_t _numFiles) 
			: BaseArchiveHeader(1), 
			hashTableEntries(htEntries), 
			numFiles(_numFiles)
		{}
		
		uint64_t hashTableEntries;
		uint64_t numFiles;
	};

	struct SNGL_ARCHIVE_DATA_ALIGNMENT V1HashtableSlot
	{
		inline V1HashtableSlot(uint64_t _key, uint64_t _value)
			: key(_key), value(_value), isOccupied(true)
		{ }

		inline V1HashtableSlot() {}

		uint64_t key;
		uint64_t value;
		bool isOccupied;
	};

	struct SInternalFileEntry
	{
		std::optional<std::string> fullpath; // only for file reading purposes, optional
		std::string vpath; // virtual path inside
		bool shouldBeCompressed;
	};

	class V1Archive final : public IArchive
	{
	public:
		V1Archive() = default;

		bool addFile(const fs::path& path, bool shouldCompress) override;
		bool write(const fs::path& outPath) override;

	private:
		uint64_t getTableSize();
		bool cuckooInsertion(std::vector<V1HashtableSlot>& table, uint64_t idx1, uint64_t idx2);

		std::vector<SInternalFileEntry> m_files;
	};
}