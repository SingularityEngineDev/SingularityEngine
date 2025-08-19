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

#ifndef _SNGL_ASSET_FORMAT_FILE_ENTRY_H_INCLUDED_
#define _SNGL_ASSET_FORMAT_FILE_ENTRY_H_INCLUDED_

#include <stdint.h>

#define BIT(x) (1 << x)

namespace sngl::asset_format
{
	constexpr const uint64_t MAX_PATH_LENGTH = 128;

	enum FileEntryFlags : uint8_t 
	{ 
		LZ4_COMPRESSED = BIT(0)
	};

	struct FileEntry
	{
		char virtualPath[MAX_PATH_LENGTH];
		uint64_t offset;
		uint64_t size;
		uint8_t flags;
		uint8_t reserved[7];

		inline bool isEnabled(FileEntryFlags _flags) const
		{
			return (static_cast<uint8_t>(_flags) & static_cast<uint8_t>(flags)) > 0;
		}
	};

	static_assert(sizeof(FileEntry) == 152, "FileEntry has unexpected size");
}

#endif