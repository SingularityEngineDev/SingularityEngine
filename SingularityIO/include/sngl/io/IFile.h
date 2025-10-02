#ifndef _SNGL_IO_IFILE_H_INCLUDED_
#define _SNGL_IO_IFILE_H_INCLUDED_

#include <sngl/shared/definitions.h>

namespace sngl::io
{
	class IFile
	{
	public:
		virtual ~IFile() = default;

		SNGL_API static std::unique_ptr<IFile> Open(const std::string_view path);
	};
}

#endif