add_executable(SingularityPackman main.cpp)
target_link_libraries(SingularityPackman 
	PRIVATE SingularityAssetFormat argparse::argparse spdlog::spdlog
)