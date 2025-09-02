add_library(SingularityArchiveUtils "src/V1Archive.h" "src/V1Archive.cpp" "src/BaseArchiveHeader.h" "src/ArchiveFactory.cpp"  "include/SingularityArchiveUtils/definitions.h")
target_include_directories(SingularityArchiveUtils PUBLIC include)
target_link_libraries(SingularityArchiveUtils PRIVATE xxhash UUIDv4 SingularityMathUtils)

message(STATUS "${SNGL_COMPILER_CAPABILITIES_AVX2_INSTRUCTION_SET_COMPILE_ARGS}")
target_compile_definitions(SingularityArchiveUtils PRIVATE SNGL_ARCHIVE_UTILS_EXPORT_SYMBOLS)
target_compile_options(SingularityArchiveUtils PRIVATE "${SNGL_COMPILER_CAPABILITIES_AVX2_INSTRUCTION_SET_COMPILE_ARGS}")

set_target_properties(SingularityArchiveUtils PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)