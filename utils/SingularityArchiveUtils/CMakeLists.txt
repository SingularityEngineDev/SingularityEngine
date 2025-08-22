add_library(SingularityArchiveUtils "src/V1Archive.h" "src/V1Archive.cpp" "src/BaseArchiveHeader.h" "src/ArchiveFactory.cpp"  "include/SingularityArchiveUtils/definitions.h")
target_include_directories(SingularityArchiveUtils PUBLIC include)
target_link_libraries(SingularityArchiveUtils PRIVATE xxhash UUIDv4)

target_compile_definitions(SingularityArchiveUtils PRIVATE SNGL_ARCHIVE_UTILS_EXPORT_SYMBOLS)

set_target_properties(SingularityArchiveUtils PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)