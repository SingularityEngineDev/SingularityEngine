#include "con_utils.h"

#ifdef SNGL_BUILD_TYPE_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <Windows.h>

	ConSize GetConsoleSize()
	{
		CONSOLE_SCREEN_BUFFER_INFO csbi;
		if (!GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
			return ConSize{ UINT32_MAX, UINT32_MAX };

		return ConSize
		{
			.w = static_cast<uint32_t>(csbi.srWindow.Right - csbi.srWindow.Left + 1),
			.h = static_cast<uint32_t>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)
		};
	}
#elif defined(SNGL_BUILD_TYPE_UNIX)
	#include <sys/ioctl.h>
	#include <unistd.h>

	ConSize GetConsoleSize()
	{
		winsize w{};
		if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &W) == 0)
			return ConSize{ .w = static_cast<uint32_t>(w.ws_col), .h = static_cast<uint32_t>(w.ws_row) };
		else
			return ConSize{ UINT32_MAX, UINT32_MAX };
	}
#else
	#error "Platform not implemented"
#endif