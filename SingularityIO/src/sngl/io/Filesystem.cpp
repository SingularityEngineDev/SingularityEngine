#include <sngl/io/IFilesystem.h>

using namespace sngl::io;

namespace sngl::io
{
	class Filesystem : public IFilesystem
	{
	public:
		bool mountArchive(const std::string_view path) override
		{
			return true;
		}

		static Filesystem* GetInstance()
		{
			if (!s_instance)
				s_instance = std::make_unique<Filesystem>();

			return s_instance.get();
		}

	private:
		static std::unique_ptr<Filesystem> s_instance;
	};

	IFilesystem* IFilesystem::Get()
	{
		return Filesystem::GetInstance();
	}
} // namespace sngl::io