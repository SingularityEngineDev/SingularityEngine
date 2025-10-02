set(SNGL_IO_SOURCES
		
)

add_library(SingularityEngine_IO SHARED ${SNGL_IO_SOURCES} "src/sngl/pch.cpp")

target_include_directories(SingularityEngine_IO 
	PUBLIC include
	PRIVATE src
)

target_precompile_headers(SingularityEngine_IO
	PRIVATE "src/sngl/pch.h"
	PUBLIC	"include/sngl/pch.h"
)