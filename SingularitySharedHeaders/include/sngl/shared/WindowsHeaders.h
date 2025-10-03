#ifdef SNGL_BUILD_PLATFORM_WINDOWS
#	define WIN32_LEAN_AND_MEAN
#	define NO_KANJI
#	include <Windows.h>
#
#	define VALID_HANDLE(x) (((HANDLE)x != 0) && ((HANDLE)x != INVALID_HANDLE_VALUE))
#endif