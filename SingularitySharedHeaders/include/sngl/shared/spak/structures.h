#ifndef _SNGL_SHARED_SPAK_STRUCTURES_H_INCLUDED_
#define _SNGL_SHARED_SPAK_STRUCTURES_H_INCLUDED_

namespace sngl::shared::spak
{
	struct alignas(8) ArchiveHeader
	{
		static constexpr uint64_t DEFAULT_BLOCKSIZE = (1 << 14);
		static constexpr uint32_t MAGIC_VALUE = 0x4B415053;
		static constexpr uint16_t CURRENT_VERSION = 0x0010;

		ArchiveHeader()
			: magic(MAGIC_VALUE),
			version(CURRENT_VERSION),
			blockSize(DEFAULT_BLOCKSIZE),
			filetableOffset(sizeof(ArchiveHeader))
		{
		}

		uint32_t magic;
		uint16_t version;
		uint16_t reserved;
		uint64_t blockSize;
		uint64_t filecount;
		uint64_t filetableOffset;
		uint64_t dataOffset;
	};

	struct alignas(8) FileEntry
	{
		char path[256];
		uint64_t blockCount;
		uint64_t startBlockOffset;
		uint64_t startBlockDataOffset;
	};

	static_assert(sizeof(ArchiveHeader) == 40);
	static_assert(sizeof(FileEntry) == 280);
}

#endif