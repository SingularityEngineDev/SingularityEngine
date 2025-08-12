set(SNGL_CORE_SOURCES
	"sngl/core/CEngine.cpp"
	"sngl/core/CWindow.h" 
	"sngl/core/CWindow.cpp" 
	"sngl/core/CEventQueue.h" 
	"sngl/core/CEventQueue.cpp"
)

add_library(SingularityEngine SHARED ${SNGL_CORE_SOURCES})

target_link_libraries(SingularityEngine 
	PRIVATE SDL3::SDL3
)
target_include_directories(SingularityEngine PUBLIC "${SNGL_ROOT_PATH}/include")

if (${SNGL_WINDOWS_BUILD})
	target_compile_definitions(SingularityEngine PRIVATE SNGL_WINDOWS_BUILD)
endif()

target_compile_definitions(SingularityEngine PRIVATE SNGL_EXPORT)