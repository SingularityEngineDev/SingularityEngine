#ifndef _SNGL_IO_FILESYSTEM_H_INCLUDED_
#define _SNGL_IO_FILESYSTEM_H_INCLUDED_

#include <sngl/shared/definitions.h>

namespace sngl::io
{
	class IFilesystem
	{
	public:
		IFilesystem() = default;
		virtual ~IFilesystem() = default;

		virtual bool mountArchive(const std::string_view path) = 0;

		SNGL_API static IFilesystem* create();
	};
}

#endif