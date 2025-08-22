#ifndef _SNGL_ARCHIVE_UTILS_BASEARCHIVEHEADER_H_INCLUDED_
#define _SNGL_ARCHIVE_UTILS_BASEARCHIVEHEADER_H_INCLUDED_

#include <stdint.h>
#include <cstring>

#define SNGL_ARCHIVE_UTILS_MAGIC_STRING { 'S', 'N', 'G', 'L' }
#define SNGL_ARCHIVE_DATA_ALIGNMENT alignas(16)

namespace sngl::archive_utils
{
	struct SNGL_ARCHIVE_DATA_ALIGNMENT BaseArchiveHeader
	{
		static constexpr char MAGIC_STRING[] = SNGL_ARCHIVE_UTILS_MAGIC_STRING;

		inline BaseArchiveHeader(uint8_t _revision) : revision(_revision)
		{
			std::memcpy(magic, MAGIC_STRING, 4);
		}

		char magic[4];	
		uint8_t revision;

		inline bool isMagicValid() const { return std::strncmp(magic, MAGIC_STRING, sizeof(MAGIC_STRING)); }
	};
}

#endif