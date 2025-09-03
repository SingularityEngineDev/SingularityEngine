#ifdef SNGL_BUILD_TYPE_WINDOWS
	#ifdef SNGL_EXPORT_SYMBOLS
		#define SNGL_API __declspec(dllexport)
	#else
		#define SNGL_API __declspec(dllimport)
	#endif
#else
	#define SNGL_API
#endif

#define BIT(x) (1 << x)