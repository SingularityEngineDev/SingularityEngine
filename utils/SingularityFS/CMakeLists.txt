add_library(SingularityFS SHARED src/sngl/fs/MemoryMappedFile.cpp    "src/sngl/fs/MemoryMappedFile.h"   "include/sngl/fs/IFile.h"   "src/sngl/fs/IFile.cpp")
target_include_directories(SingularityFS 
	PUBLIC include
	PRIVATE src
)

target_compile_definitions(SingularityFS PRIVATE SNGL_EXPORT_SYMBOLS)