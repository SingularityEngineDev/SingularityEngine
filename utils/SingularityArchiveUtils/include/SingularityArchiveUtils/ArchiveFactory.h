#ifndef _SNGL_ARCHIVE_UTILS_ARCHIVEFACTORY_H_INCLUDED_
#define _SNGL_ARCHIVE_UTILS_ARCHIVEFACTORY_H_INCLUDED_

#include <memory>

namespace sngl::archive_utils
{
	class IArchive;

	class ArchiveFactory
	{
		struct success_t
		{
			bool success;
			std::unique_ptr<IArchive> archive;
		};

		enum ArchiveRev : uint8_t { REV_NEWEST, REV_ONE };

		static std::unique_ptr<IArchive> createArchive(ArchiveRev rev = REV_NEWEST);
		static success_t openArchive();
	};
}

#endif