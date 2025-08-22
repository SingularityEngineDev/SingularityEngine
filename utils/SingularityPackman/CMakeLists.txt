add_executable(SingularityPackman "main.cpp")
target_link_libraries(SingularityPackman PRIVATE SingularityArchiveUtils UUIDv4 argparse::argparse spdlog::spdlog_header_only)

add_custom_command(TARGET SingularityPackman POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:SingularityArchiveUtils> $<TARGET_FILE_DIR:SingularityPackman>
)