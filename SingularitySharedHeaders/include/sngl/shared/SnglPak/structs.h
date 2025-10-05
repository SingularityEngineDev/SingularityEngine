#ifndef _SNGL_SHARED_SNGLPAK_STRUCTS_H_INCLUDED_
#define _SNGL_SHARED_SNGLPAK_STRUCTS_H_INCLUDED_

#include <sngl/shared/definitions.h>

namespace sngl::shared::sngl_pak
{
	SNGL_BEGIN_PACK
	struct TocEntry
	{
		inline TocEntry(const std::string& filename, size_t _fileSize, size_t _blockIndex)
			: filenameLength(filename.size()), fileSize(_fileSize), blockIndex(_blockIndex)
		{ }

		size_t blockIndex;
		size_t fileSize;
		size_t filenameLength;
	} SNGL_PACK;
	SNGL_END_PACK
}

#endif