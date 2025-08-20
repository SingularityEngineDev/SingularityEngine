#ifndef _SNGL_ARCHIVE_UTILS_DATASTRUCTURES_HEADER_H_INCLUDED_
#define _SNGL_ARCHIVE_UTILS_DATASTRUCTURES_HEADER_H_INCLUDED_

#include <stdint.h>

namespace sngl::archive_utils::datastructures
{
	struct alignas(16) Header
	{
		char magic[4];
		uint32_t version;
		uint64_t numOfEntries;
		uint8_t flags;

		enum HeaderFlags { };

		inline bool hasFlags(HeaderFlags _flags) const
		{
			return (flags & _flags) > 0;
		}
	};

	static_assert(sizeof(Header) == 32, "Header structure has invalid size");
	static_assert(alignof(Header) == 16, "Header structure has invalid alignment");
}

#endif