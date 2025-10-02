#ifndef _SNGL_IO_IFILE_H_INCLUDED_
#define _SNGL_IO_IFILE_H_INCLUDED_

#include <sngl/shared/definitions.h>
#include <sngl/pch.h>

namespace sngl::io
{
	class IFile
	{
	public:
		virtual ~IFile() = default;

		// virtual const void* getData(size_t offset = 0) const;

		enum class IoType { IT_MAPPED, IT_SEQUENTIAL };
		SNGL_API static std::unique_ptr<IFile> Open(const std::string_view path, IoType type);
	};
}

#endif