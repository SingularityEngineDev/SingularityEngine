set(SNGL_IO_SOURCES	
	"src/sngl/io/IFile.cpp"
	"src/sngl/io/MemoryMappedFile.cpp"
	"src/sngl/io/SequentialFile.cpp"
	"src/sngl/io/OsFile.cpp"
)

singularity_addsubmodule(SingularityEngine_IO ${SNGL_IO_SOURCES} "src/sngl/pch.cpp")
target_link_libraries(SingularityEngine_IO 
	PRIVATE fmt::fmt
)

target_include_directories(SingularityEngine_IO 
	PUBLIC include
	PRIVATE src
)

target_precompile_headers(SingularityEngine_IO
	PRIVATE "src/sngl/pch.h"
	PUBLIC	"include/sngl/pch.h"
)