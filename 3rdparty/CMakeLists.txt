# SDL options
set(SDL_SHARED OFF)
set(SDL_STATIC ON)
add_subdirectory(SDL)

add_subdirectory(spdlog)
add_subdirectory(argparse)
add_subdirectory(lz4/build/cmake)
add_subdirectory(xxHash/build/cmake)