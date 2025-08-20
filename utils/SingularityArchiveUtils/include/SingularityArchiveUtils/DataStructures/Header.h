// Copyright 2025 YasInvolved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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