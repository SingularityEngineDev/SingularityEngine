set(SNGL_CORE_SOURCES
	
 "sngl/core/CEngine.cpp")

add_library(SingularityEngine SHARED ${SNGL_CORE_SOURCES})

target_include_directories(SingularityEngine PUBLIC "${SNGL_ROOT_PATH}/include")

if (${SNGL_WINDOWS_BUILD})
	target_compile_definitions(SingularityEngine PRIVATE SNGL_WINDOWS_BUILD)
endif()

target_compile_definitions(SingularityEngine PRIVATE SNGL_EXPORT)