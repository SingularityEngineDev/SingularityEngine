set(SNGL_CORE_SOURCES
	"sngl/core/CEngine.cpp"
	"sngl/core/CWindow.h" 
	"sngl/core/CWindow.cpp" 
	"sngl/core/CEventQueue.h"
	"sngl/core/Events/WindowEvents.h" 
	"sngl/core/CEventDispatcher.h" 
	"sngl/core/CEventDispatcher.cpp" 
	"sngl/core/CSpdlogLogger.h" 
	"sngl/core/CSpdlogLogger.cpp"
	
 "sngl/core/IInternalRenderer.h" "sngl/core/D3D11Renderer/D3D11Renderer.h" "sngl/core/D3D11Renderer/D3D11Renderer.cpp" "sngl/core/RendererFactory.h" "sngl/core/RendererFactory.cpp")

add_library(SingularityEngine SHARED ${SNGL_CORE_SOURCES} "sngl/pch.cpp")

target_link_libraries(SingularityEngine 
	PRIVATE SDL3::SDL3 spdlog::spdlog SingularityAssetFormat
)
target_include_directories(SingularityEngine PUBLIC "${SNGL_ROOT_PATH}/include")

if (MSVC)
	if (${SNGL_DYNAMIC_RUNTIME} AND MSVC)
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>Dll")
	else()
		set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
	endif()
endif()

if (${SNGL_WINDOWS_BUILD})
	target_compile_definitions(SingularityEngine PRIVATE SNGL_WINDOWS_BUILD)
	target_link_libraries(SingularityEngine PRIVATE dxgi.lib d3d11.lib d3d12.lib dxguid.lib d3dcompiler.lib)
endif()

target_compile_definitions(SingularityEngine 
	PRIVATE SNGL_EXPORT
	PUBLIC "$<$<CONFIG:Debug>:SNGL_DEBUG>"
)

target_precompile_headers(SingularityEngine
	PUBLIC "${SNGL_ROOT_PATH}/include/sngl/pch.h"
	PRIVATE "sngl/core/pch.h"
)