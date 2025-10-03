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

macro(singularity_addexec SNGL_ADDEXEC_TARGET_NAME)
	add_executable(${SNGL_ADDEXEC_TARGET_NAME} ${ARGN})
	target_link_libraries(${SNGL_ADDEXEC_TARGET_NAME} PRIVATE SingularityEngine)
	
	if (MSVC)
		set_property(TARGET ${SNGL_ADDEXEC_TARGET_NAME} PROPERTY
			MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>DLL"
		)
	endif()

	set(SNGL_SUBMODULES_COPY_CMDS)
	foreach(SNGL_SUBMODULE ${SNGL_REGISTERED_SUBMODULES})
		list(APPEND SNGL_SUBMODULES_COPY_CMDS
			COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${SNGL_SUBMODULE}> $<TARGET_FILE_DIR:${SNGL_ADDEXEC_TARGET_NAME}>
		)
	endforeach()

	add_custom_target("${SNGL_ADDEXEC_TARGET_NAME}_copy_dependencies"
		${SNGL_SUBMODULES_COPY_CMDS}
		COMMENT "Copying all singularity submodules"
	)

	add_dependencies(${SNGL_ADDEXEC_TARGET_NAME} "${SNGL_ADDEXEC_TARGET_NAME}_copy_dependencies")
endmacro()