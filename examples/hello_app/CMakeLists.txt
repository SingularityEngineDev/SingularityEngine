add_executable(hello_app "main.cpp")
target_link_libraries(hello_app SingularityEngine)

add_custom_command(TARGET hello_app POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SingularityEngine_Core> $<TARGET_FILE_DIR:hello_app>
)