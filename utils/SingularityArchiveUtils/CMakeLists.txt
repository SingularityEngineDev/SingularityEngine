add_library(SingularityArchiveUtils "src/V1Archive.h" "src/V1Archive.cpp" "src/BaseArchiveHeader.h" "src/ArchiveFactory.cpp"  "include/SingularityArchiveUtils/definitions.h")
target_include_directories(SingularityArchiveUtils PUBLIC include)
target_link_libraries(SingularityArchiveUtils PRIVATE xxhash UUIDv4 SingularityMathUtils)

target_compile_definitions(SingularityArchiveUtils PRIVATE SNGL_ARCHIVE_UTILS_EXPORT_SYMBOLS)

set_target_properties(SingularityArchiveUtils PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO
)

include(CheckCXXCompilerFlag)

if (MSVC)
	check_cxx_compiler_flag("/arch:AVX2" COMPILER_SUPPORTS_AVX2)

	if (NOT COMPILER_SUPPORTS_AVX)
		message(FATAL_ERROR "Compiler doesn't support AVX2 instruction set, which is required'")
	else()
		message(STATUS "Compiler supports AVX2")
	endif()

	target_compile_options(SingularityArchiveUtils PRIVATE /O2 /arch:AVX2)
else()
	check_cxx_compiler_flag("-mavx2" COMPILER_SUPPORTS_AVX2)

	if (NOT COMPILER_SUPPORTS_AVX)
		message(FATAL_ERROR "Compiler doesn't support AVX2 instruction set, which is required'")
	else()
		message(STATUS "Compiler supports AVX2")
	endif()

	target_compile_options(SingularityArchiveUtils PRIVATE -O3 -mavx2)
endif()