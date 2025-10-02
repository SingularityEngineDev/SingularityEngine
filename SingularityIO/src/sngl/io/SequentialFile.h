#ifndef _SNGL_IO_SEQUENTIALFILE_H_INCLUDED_
#define _SNGL_IO_SEQUENTIALFILE_H_INCLUDED_

namespace sngl::io
{
	class SequentialFile final : public IFile
	{
	public:
		SequentialFile(const std::string_view path);
		~SequentialFile() override;
	};
}

#endif