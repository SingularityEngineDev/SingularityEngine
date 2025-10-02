# Wrapper around add_library that adds necessary compile definitions and links shared headers
macro(singularity_addsubmodule SNGL_ADDSBMD_TARGET_NAME)
	add_library(${SNGL_ADDSBMD_TARGET_NAME} SHARED ${ARGN})
	target_link_libraries(${SNGL_ADDSBMD_TARGET_NAME} PUBLIC SingularityEngine_SharedHeaders)
	target_compile_definitions(${SNGL_ADDSBMD_TARGET_NAME} PRIVATE SNGL_EXPORT)
	
	if (MSVC)
		set_property(TARGET ${SNGL_ADDSBMD_TARGET_NAME} PROPERTY
			MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
		)
	endif()
endmacro()