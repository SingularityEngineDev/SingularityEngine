#ifndef _SNGL_SHARED_SNGLPAK_STRUCTS_H_INCLUDED_
#define _SNGL_SHARED_SNGLPAK_STRUCTS_H_INCLUDED_

#include <sngl/shared/definitions.h>

namespace sngl::shared::sngl_pak
{
	constexpr char MAGIC_VALUE[] = { 'S', 'N', 'G', 'L' };

	SNGL_BEGIN_PACK
	struct TocEntry
	{
		inline TocEntry(const std::string& _path, size_t _fileSize, size_t _blockIndex)
			: blockIndex(_blockIndex), fileSize(_fileSize)
		{
			assert(_path.size() < sizeof(path));
			memset(path, 0, sizeof(path));
			memcpy(path, _path.data(), _path.size());
		}

		char path[256];
		size_t blockIndex;
		size_t fileSize;
	} SNGL_PACK;
	SNGL_END_PACK

	SNGL_BEGIN_PACK
	struct BlockInfo
	{
		inline BlockInfo(size_t _blockIndex, size_t _uncompressedSize, size_t _compressedSize)
			: blockIndex(_blockIndex), uncompressedBlockSize(_uncompressedSize), compressedBlockSize(_compressedSize)
		{ }

		size_t blockIndex;
		size_t uncompressedBlockSize;
		size_t compressedBlockSize;
		// TODO: checksum
	} SNGL_PACK;
	SNGL_END_PACK
}

#endif