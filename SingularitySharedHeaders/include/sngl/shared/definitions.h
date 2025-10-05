#ifndef _SNGL_SHARED_DEFINITIONS_H_INCLUDED_
#define _SNGL_SHARED_DEFINITIONS_H_INCLUDED_

#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	#ifdef SNGL_EXPORT
		#define SNGL_API __declspec(dllexport)
	#else
		#define SNGL_API __declspec(dllimport)
	#endif
#else
	#define SNGL_API
#endif

#ifdef _MSC_VER
	#define SNGL_BEGIN_PACK __pragma(pack(push, 1))
	#define SNGL_END_PACK __pragma(pack(pop))
	#define SNGL_PACK
#elif defined(__GNUC__) || defined(__clang__)
	#define SNGL_BEGIN_PACK
	#define SNGL_END_PACK
	#define SNGL_PACK __attribute__((packed))
#else
	#error "Unsupported compiler, please define packing macros"
#endif

#endif