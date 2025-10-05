add_executable(SingularityAssetWriter "main.cpp" "pch.h" "pch.cpp")
target_link_libraries(SingularityAssetWriter 
	PRIVATE SingularityEngine_SharedHeaders argparse::argparse
)

target_precompile_headers(SingularityAssetWriter 
	PRIVATE pch.h
)