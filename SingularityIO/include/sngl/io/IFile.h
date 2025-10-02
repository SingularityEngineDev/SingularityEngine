#ifndef _SNGL_IO_IFILE_H_INCLUDED_
#define _SNGL_IO_IFILE_H_INCLUDED_

namespace sngl::io
{
	class IFile
	{
	public:
		virtual ~IFile() = default;

		static std::unique_ptr<IFile> Open(const std::string_view path);
	};
}

#endif