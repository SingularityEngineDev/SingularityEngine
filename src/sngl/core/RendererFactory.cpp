#include "RendererFactory.h"

#include "D3D11Renderer/D3D11Renderer.h"

using RendererFactory = sngl::core::RendererFactory;
using IInternalRenderer = sngl::core::IInternalRenderer;

std::unique_ptr<IInternalRenderer> RendererFactory::CreateRecommendedRenderer(IEngine* engine)
{
#ifdef SNGL_WINDOWS_BUILD
	return CreateRenderer(engine, RendererAPI::D3D11);
#else
	#error "Cross-platform renderers are not implemented yet"
#endif
}

std::unique_ptr<IInternalRenderer> RendererFactory::CreateRenderer(IEngine* engine, RendererAPI api)
{
	switch (api)
	{
	case RendererAPI::D3D11:
		return std::make_unique<d3d11::D3D11Renderer>(engine);
	default:
		return nullptr;
	}
}