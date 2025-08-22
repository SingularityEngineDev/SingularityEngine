#ifdef SNGL_BUILD_TYPE_WINDOWS
	#ifdef SNGL_ARCHIVE_UTILS_EXPORT_SYMBOLS
		#define SNGL_ARCHIVE_UTILS_API __declspec(dllexport)
	#else
		#define SNGL_ARCHIVE_UTILS_API __declspec(dllimport)
	#endif
#else
	#define SNGL_ARCHIVE_UTILS_API
#endif