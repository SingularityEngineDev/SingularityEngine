add_subdirectory(googletest)

# SDL options
set(SDL_SHARED OFF CACHE BOOL "" FORCE)
set(SDL_STATIC ON CACHE BOOL "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
add_subdirectory(SDL)

add_subdirectory(spdlog)
add_subdirectory(argparse)
add_subdirectory(lz4/build/cmake)
add_subdirectory(xxHash/build/cmake)
add_subdirectory(fmt)