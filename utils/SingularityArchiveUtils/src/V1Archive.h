#include <SingularityArchiveUtils/IArchive.h>
#include <SingularityMathUtils.h>
#include "BaseArchiveHeader.h"
#include <vector>
#include <string>
#include <optional>
#include <type_traits>

#define SNGL_ARCHIVE_UTILS_V1_ARCHIVE_FILE_DATA_ALIGNMENT 16 * 1024

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

	struct SNGL_ARCHIVE_DATA_ALIGNMENT V1FileMetadata
	{
		char path[128];
		uint64_t dataOffset;
		uint64_t size;
		uint8_t flags;
	};

	static_assert(std::is_trivially_copyable_v<V1FileMetadata>, "V1FileMetadata is not trivially copyable");

	struct SNGL_ARCHIVE_DATA_ALIGNMENT V1HashtableSlot
	{
		inline V1HashtableSlot(uint64_t _key, V1FileMetadata&& _value)
			: key(_key), value(std::move(_value)), isOccupied(true)
		{ }

		inline V1HashtableSlot() : key(0), isOccupied(false) {}

		uint64_t key;
		V1FileMetadata value;
		bool isOccupied;
	};

	struct SInternalFileEntry
	{
		std::optional<std::string> fullpath; // only for file writing purposes, optional
		std::string vpath; // virtual path inside
		bool shouldBeCompressed;
	};

	class V1Archive final : public IArchive
	{
	public:
		V1Archive() = default;

		bool addFile(const fs::path& path, bool shouldCompress) override;
		bool addFile(const fs::path& base, const fs::path& relative, bool shouldCompress) override;
		bool write(const fs::path& outPath) override;

	private:
		struct WriteContext;

		uint64_t getTableSize();
		inline uint64_t alignFileSize(uint64_t fileSize)
		{
			constexpr uint64_t DATA_ALIGNMENT_CONSTANT = SNGL_ARCHIVE_UTILS_V1_ARCHIVE_FILE_DATA_ALIGNMENT - 1;
			return (fileSize + DATA_ALIGNMENT_CONSTANT) & ~(DATA_ALIGNMENT_CONSTANT);
		}

		bool cuckooInsertion(std::vector<V1HashtableSlot>& table, uint64_t idx1, uint64_t idx2, V1FileMetadata fileMetadata);

		std::vector<SInternalFileEntry> m_files;
	};
}