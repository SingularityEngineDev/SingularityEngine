set(SNGL_CORE_SOURCES
	"src/sngl/core/CEngine.cpp"
	"src/sngl/core/CWindow.h" 
	"src/sngl/core/CWindow.cpp" 
	"src/sngl/core/CEventQueue.h"
	"src/sngl/core/Events/WindowEvents.h" 
	"src/sngl/core/CEventDispatcher.h" 
	"src/sngl/core/CEventDispatcher.cpp" 
	"src/sngl/core/CSpdlogLogger.h" 
	"src/sngl/core/CSpdlogLogger.cpp"
	"src/sngl/core/IInternalRenderer.h" 
	"src/sngl/core/D3D11Renderer/D3D11Renderer.h" 
	"src/sngl/core/D3D11Renderer/D3D11Renderer.cpp" 
	"src/sngl/core/RendererFactory.h" 
	"src/sngl/core/RendererFactory.cpp"
)

singularity_addsubmodule(SingularityEngine_Core ${SNGL_CORE_SOURCES} "src/sngl/pch.cpp")
target_link_libraries(SingularityEngine_Core
	PRIVATE SDL3::SDL3 spdlog::spdlog_header_only
)

target_include_directories(SingularityEngine_Core
	PUBLIC include
	PRIVATE src
)

if (${SNGL_WINDOWS_BUILD})
	target_compile_definitions(SingularityEngine_Core PRIVATE SNGL_WINDOWS_BUILD)
	target_link_libraries(SingularityEngine_Core PRIVATE dxgi.lib d3d11.lib d3d12.lib dxguid.lib d3dcompiler.lib)
endif()

target_precompile_headers(SingularityEngine_Core
	PUBLIC "include/sngl/pch.h"
	PRIVATE "src/sngl/pch.h"
)