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

#ifndef _SNGL_ASSET_FORMAT_HEADER_H_INCLUDED_
#define _SNGL_ASSET_FORMAT_HEADER_H_INCLUDED_

#include <stdint.h>

#define SNGL_ASSET_FORMAT_MAGIC_VALUE { 'S', 'N', 'G', 'L' }

namespace sngl::asset_format
{
	struct HeaderVersion
	{
		uint8_t major;
		uint8_t minor;
		uint8_t patch;
		uint8_t reserved; // unused field
	};

	constexpr const char HEADER_MAGIC_VALUE[4] = SNGL_ASSET_FORMAT_MAGIC_VALUE;

	struct Header
	{
		char magic[4]; // magic should always be SNGL
		HeaderVersion version;
		uint64_t fileEntryCount; // the next struct after this one is the file table, which contains offsets of all files and their sizes
		// no need to pad it, size is 2*8
	};

	// static asserts to ensure that everything stays compatible with all compilers and platforms
	static_assert(sizeof(Header) == 16, "Header has unexpected size");
	static_assert(sizeof(HeaderVersion) == 4, "HeaderVersion has unexpected size");
}

#endif