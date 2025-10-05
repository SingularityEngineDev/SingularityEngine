add_executable(SingularityAssetWriter "main.cpp" "pch.h" "pch.cpp")
set_target_properties(SingularityAssetWriter PROPERTIES
	CXX_STANDARD 20
	CXX_STANDARD_REQUIRED True
)

target_link_libraries(SingularityAssetWriter 
	PRIVATE SingularityEngine_SharedHeaders SingularityEngine_IO argparse::argparse fmt::fmt-header-only lz4_static
)

target_precompile_headers(SingularityAssetWriter 
	PRIVATE pch.h
)

singularity_copyenginedependencies(SingularityAssetWriter SingularityEngine_IO)