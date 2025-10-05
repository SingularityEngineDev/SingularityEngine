# Wrapper around add_library that adds necessary compile definitions and links shared headers
set(SNGL_REGISTERED_SUBMODULES "" CACHE INTERNAL "")

macro(singularity_addsubmodule SNGL_ADDSBMD_TARGET_NAME)
	add_library(${SNGL_ADDSBMD_TARGET_NAME} SHARED ${ARGN})
	target_link_libraries(${SNGL_ADDSBMD_TARGET_NAME} PUBLIC SingularityEngine_SharedHeaders)
	target_compile_definitions(${SNGL_ADDSBMD_TARGET_NAME} PRIVATE SNGL_EXPORT)
	
	if (MSVC)
		set_property(TARGET ${SNGL_ADDSBMD_TARGET_NAME} PROPERTY
			MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
		)
	endif()

	list(APPEND SNGL_REGISTERED_SUBMODULES ${SNGL_ADDSBMD_TARGET_NAME})
	set(SNGL_REGISTERED_SUBMODULES "${SNGL_REGISTERED_SUBMODULES}" CACHE INTERNAL "")
endmacro()

function(singularity_copyenginedependencies TARGET_NAME)
	set(COPY_DEPENDENCIES_TARET_NAME "${TARGET_NAME}_copy_dependencies")
	
	set(SNGL_SUBMODULES_COPY_CMDS)
	foreach(SNGL_SUBMODULE ${ARGN})
		list(APPEND SNGL_SUBMODULES_COPY_CMDS
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${SNGL_SUBMODULE}> $<TARGET_FILE_DIR:${TARGET_NAME}>
		)
	endforeach()

	add_custom_target(${COPY_DEPENDENCIES_TARET_NAME} 
		${SNGL_SUBMODULES_COPY_CMDS}
		COMMENT "Copying all engine dependencies"
	)

	add_dependencies(${TARGET_NAME} ${COPY_DEPENDENCIES_TARET_NAME})
endfunction()

macro(singularity_addexec SNGL_ADDEXEC_TARGET_NAME)
	add_executable(${SNGL_ADDEXEC_TARGET_NAME} ${ARGN})
	target_link_libraries(${SNGL_ADDEXEC_TARGET_NAME} PRIVATE SingularityEngine)
	
	if (MSVC)
		set_property(TARGET ${SNGL_ADDEXEC_TARGET_NAME} PROPERTY
			MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
		)
	endif()

	singularity_copyenginedependencies(${SNGL_ADDEXEC_TARGET_NAME} ${SNGL_REGISTERED_SUBMODULES})
endmacro()