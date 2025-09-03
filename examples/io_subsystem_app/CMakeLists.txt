add_executable(io_subsystem_app main.cpp)
target_link_libraries(io_subsystem_app 
	PRIVATE SingularityFS argparse::argparse
)

add_custom_command(TARGET io_subsystem_app POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SingularityFS> $<TARGET_FILE_DIR:io_subsystem_app>
)