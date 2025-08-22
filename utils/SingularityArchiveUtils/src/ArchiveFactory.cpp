#include <SingularityArchiveUtils/ArchiveFactory.h>
#include "V1Archive.h"

using namespace sngl::archive_utils;

#define SNGL_NEWEST_ARCHIVE_FORMAT V1Archive

std::unique_ptr<IArchive> ArchiveFactory::createArchive(ArchiveFactory::ArchiveRev rev)
{
	switch (rev)
	{
	case ArchiveRev::REV_ONE:
		return std::make_unique<V1Archive>();
	case ArchiveRev::REV_NEWEST:
	default:
		return std::make_unique<SNGL_NEWEST_ARCHIVE_FORMAT>();
	}
}

ArchiveFactory::success_t ArchiveFactory::openArchive()
{
	// TODO: open, read revision and return IArchive with status
	return { true, nullptr };
}