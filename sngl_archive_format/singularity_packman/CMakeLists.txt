add_executable(SingularityPackman main.cpp "con_utils.h" "con_uitls.cpp")
target_link_libraries(SingularityPackman 
	PRIVATE SingularityAssetFormat argparse::argparse spdlog::spdlog
)