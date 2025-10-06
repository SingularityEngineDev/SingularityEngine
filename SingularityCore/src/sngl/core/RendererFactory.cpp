#include "RendererFactory.h"

#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	#include "D3D11Renderer/D3D11Renderer.h"
#endif

#include "VulkanRenderer/VulkanRenderer.h"

using RendererFactory = sngl::core::RendererFactory;
using IInternalRenderer = sngl::core::IInternalRenderer;

std::unique_ptr<IInternalRenderer> RendererFactory::CreateRecommendedRenderer(IEngine* engine)
{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	return CreateRenderer(engine, RendererAPI::D3D11);
#elif !defined(SNGL_BUILD_PLATFORM_UNIX)
	#error "Renderer is currently available only for windows and unix platforms"
#endif
	return CreateRenderer(engine, RendererAPI::Vulkan);
}

std::unique_ptr<IInternalRenderer> RendererFactory::CreateRenderer(IEngine* engine, RendererAPI api)
{
	switch (api)
	{
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
	case RendererAPI::D3D11:
		return std::make_unique<d3d11::D3D11Renderer>(engine);
#endif
	case RendererAPI::Vulkan:
	default:
		return std::make_unique<vulkan::VulkanRenderer>(engine);
	}
}