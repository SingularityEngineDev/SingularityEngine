cmake_minimum_required(VERSION 3.21)

project(SingularityEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_POSITION_INDEPENDENT_CODE True)

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo;MinSizeRel" CACHE STRING "" FORCE)
if (NOT CMAKE_CONFIGURATION_TYPES)
	set(SNGL_DEFAULT_BUILD_TYPE "Debug")

	if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
		message(STATUS "Build type set to '${SNGL_DEFAULT_BUILD_TYPE}' because none was specified")
		set(CMAKE_BUILD_TYPE "${SNGL_DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the build type" FORCE)
		set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "RelWithDebInfo" "MinSizeRel")
	endif()
endif()

option(SNGL_DYNAMIC_RUNTIME "Use dynamic runtime" OFF)

get_filename_component(SNGL_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)

if (WIN32)
	add_compile_definitions(SNGL_BUILD_PLATFORM_WINDOWS)
else(UNIX)
	add_compile_definitions(SNGL_BUILD_PLATFORM_UNIX)
endif()

include(cmake/CompilerCapabilities.cmake)
SNGL_CHECK_AVX2_SUPPORT()

# Global compile definitions
add_compile_definitions("$<$<CONFIG:Debug>:SNGL_DEBUG>")

add_subdirectory(3rdparty)
add_subdirectory(SingularitySharedHeaders)

include(cmake/BuildsystemUtilities.cmake)
add_subdirectory(Tools)
add_subdirectory(SingularityIO)
add_subdirectory(SingularityCore)

add_library(SingularityEngine INTERFACE)
target_link_libraries(SingularityEngine INTERFACE SingularityEngine_Core SingularityEngine_IO)

add_subdirectory(examples)