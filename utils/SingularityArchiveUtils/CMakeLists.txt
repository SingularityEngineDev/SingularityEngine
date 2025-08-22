add_library(SingularityArchiveUtils "src/V1Archive.h" "src/V1Archive.cpp" "src/BaseArchiveHeader.h" "src/ArchiveFactory.cpp" )
target_include_directories(SingularityArchiveUtils PUBLIC include)
target_link_libraries(SingularityArchiveUtils PRIVATE xxhash UUIDv4)