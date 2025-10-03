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

		virtual size_t getSize() const = 0;
		virtual size_t readSync(void* dest, size_t requestedSize) const = 0;

		enum class IoType { IT_MAPPED, IT_SEQUENTIAL };
		SNGL_API static std::unique_ptr<IFile> Open(const std::string_view path, IoType type);
	};
}

#endif