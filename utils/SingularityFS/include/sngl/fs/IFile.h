#ifndef _SNGL_FS_IFILE_H_INCLUDED_
#define _SNGL_FS_IFILE_H_INCLUDED_

#include <sngl/fs/definitions.h>
#include <stdint.h>
#include <memory>
#include <string>

namespace sngl::fs
{
	class IFile
	{
	public:
		enum FileCapabilities
		{
			READ = BIT(0),
			WRITE = BIT(1),
			MAPPED = BIT(2)
		};

		using FileCapabilitiesFlags = uint8_t;

		virtual FileCapabilitiesFlags getCapabilities() const = 0;
		virtual size_t getSize() const = 0;
		virtual size_t read(void* dst, size_t size, size_t offset) = 0;
		virtual size_t write(const void* buffer, size_t size, size_t offset) = 0;
		virtual ~IFile() {}

		static SNGL_API std::unique_ptr<IFile> OpenRO(const std::string& file, bool memoryMapped = true);
	};
}

#endif