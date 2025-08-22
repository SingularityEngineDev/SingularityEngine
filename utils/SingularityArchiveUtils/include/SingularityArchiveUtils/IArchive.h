#ifndef _SNGL_ARCHIVE_UTILS_IARCHIVE_H_INCLUDED_
#define _SNGL_ARCHIVE_UTILS_IARCHIVE_H_INCLUDED_

#include <filesystem>

namespace sngl::archive_utils
{
	namespace fs = std::filesystem;

	class IArchive
	{
	public:
		virtual ~IArchive() = default;

		virtual bool addDirectory(const fs::path& path) = 0;
		virtual bool addFile(const fs::path& path) = 0;
		virtual void write() = 0;
	};
}

#endif