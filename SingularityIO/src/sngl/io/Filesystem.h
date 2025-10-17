#ifndef _SNGL_IO_FILESYSTEM_H_INCLUDE_
#define _SNGL_IO_FILESYSTEM_H_INCLUDE_

#include <sngl/io/IFilesystem.h>

namespace sngl::io
{
	class Filesystem : public IFilesystem
	{
	public:
		bool mountArchive(const std::string_view path) override;
	};
}

#endif