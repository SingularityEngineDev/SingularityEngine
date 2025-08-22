#include <SingularityArchiveUtils/IArchive.h>
#include "BaseArchiveHeader.h"
#include <vector>
#include <string>
#include <optional>
#include <xxhash.h>

namespace sngl::archive_utils
{
	struct SNGL_ARCHIVE_DATA_ALIGNMENT V1Header : public BaseArchiveHeader
	{
		V1Header() : BaseArchiveHeader(1), hashTableEntries(0)
		{}
		
		uint64_t hashTableEntries;
	};

	struct SNGL_ARCHIVE_DATA_ALIGNMENT V1HashtableSlot
	{
		struct
		{
			uint64_t hi;
			uint64_t lo;
		} hash;
		uint64_t hash_lo;
		uint64_t offset;
		uint64_t size;
	};

	struct SFileEntry
	{
		std::optional<std::string> fullpath; // only for file reading purposes, optional
		std::string vpath; // virtual path inside
		uint64_t size;
		uint64_t offset;
	};

	class V1Archive final : public IArchive
	{
	public:
		V1Archive() = default;

		bool addDirectory(const fs::path& path) override;
		bool addFile(const fs::path& path) override;
		void write() override;

	private:
		static constexpr inline uint64_t foldHash(uint64_t hi, uint64_t lo)
		{
			return hi ^ lo;
		}

		V1Header header;
		std::vector<SFileEntry> m_files;
	};
}