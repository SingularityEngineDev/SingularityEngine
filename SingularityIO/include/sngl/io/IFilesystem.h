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

		SNGL_API static IFilesystem* Get();

		virtual bool mountArchive(const std::string_view path) = 0;
	};
}

#endif