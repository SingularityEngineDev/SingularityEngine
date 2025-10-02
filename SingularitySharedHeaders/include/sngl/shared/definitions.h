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

#endif