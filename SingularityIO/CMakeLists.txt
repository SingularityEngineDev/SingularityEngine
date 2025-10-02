set(SNGL_IO_SOURCES	
	"src/sngl/io/IFile.cpp"
)

singularity_addsubmodule(SingularityEngine_IO ${SNGL_IO_SOURCES} "src/sngl/pch.cpp")
target_include_directories(SingularityEngine_IO 
	PUBLIC include
	PRIVATE src
)

target_precompile_headers(SingularityEngine_IO
	PRIVATE "src/sngl/pch.h"
	PUBLIC	"include/sngl/pch.h"
)