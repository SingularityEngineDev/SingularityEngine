add_subdirectory(googletest EXCLUDE_FROM_ALL)

# SDL options
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(SDL EXCLUDE_FROM_ALL)

add_subdirectory(spdlog EXCLUDE_FROM_ALL)
add_subdirectory(argparse EXCLUDE_FROM_ALL)
add_subdirectory(lz4/build/cmake EXCLUDE_FROM_ALL)
add_subdirectory(xxHash/build/cmake EXCLUDE_FROM_ALL)
add_subdirectory(fmt EXCLUDE_FROM_ALL)