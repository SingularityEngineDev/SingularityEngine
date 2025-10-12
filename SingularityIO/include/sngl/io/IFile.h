#ifndef _SNGL_IO_IFILE_H_INCLUDED_
#define _SNGL_IO_IFILE_H_INCLUDED_

#include <sngl/shared/definitions.h>
#include <sngl/pch.h>

namespace sngl::io
{
	class IFile
	{
	public:
		enum class IoType { IT_MAPPED, IT_SEQUENTIAL, IT_AUTO };

		virtual ~IFile() = default;

		virtual size_t getSize() const = 0;
		virtual size_t readSync(void* dest, size_t requestedSize) const = 0;
		virtual IoType getIoType() const = 0;

		SNGL_API static IFile* Open(const std::string_view path, IoType type);
		SNGL_API static size_t GetSize(const std::string_view path);
	};
}

#endif