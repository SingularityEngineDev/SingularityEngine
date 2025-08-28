#ifndef _SNGL_ARCHIVE_UTILS_IARCHIVE_H_INCLUDED_
#define _SNGL_ARCHIVE_UTILS_IARCHIVE_H_INCLUDED_

#include <filesystem>
#include <string>

namespace sngl::archive_utils
{
	namespace fs = std::filesystem;

	class IArchive
	{
	public:
		virtual ~IArchive() = default;

		virtual bool addFile(const fs::path& path, bool shouldCompress) = 0;
		virtual bool addFile(const fs::path& base, const fs::path& relative, bool shouldCompress) = 0;
		virtual bool write(const fs::path& outPath) = 0;
	};
}

#endif