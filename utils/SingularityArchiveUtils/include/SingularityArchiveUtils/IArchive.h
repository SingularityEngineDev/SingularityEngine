#ifndef _SNGL_ARCHIVE_UTILS_IARCHIVE_H_INCLUDED_
#define _SNGL_ARCHIVE_UTILS_IARCHIVE_H_INCLUDED_

namespace sngl::archive_utils
{
	class IArchive
	{
	public:
		virtual ~IArchive() = default;

		virtual bool addFile() = 0;
		virtual void write() = 0;
	};
}

#endif