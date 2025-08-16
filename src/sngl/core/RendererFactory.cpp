#include "RendererFactory.h"

#include "D3D11Renderer/D3D11Renderer.h"

using RendererFactory = sngl::core::RendererFactory;
using IInternalRenderer = sngl::core::IInternalRenderer;

std::unique_ptr<IInternalRenderer> RendererFactory::CreateRecommendedRenderer()
{
#ifdef SNGL_WINDOWS_BUILD
	return CreateRenderer(RendererAPI::D3D11);
#else
	#error "Cross-platform renderers are not implemented yet"
#endif
}

std::unique_ptr<IInternalRenderer> RendererFactory::CreateRenderer(RendererAPI api)
{
	switch (api)
	{
	case RendererAPI::D3D11:
		return std::make_unique<d3d11::D3D11Renderer>();
	default:
		return nullptr;
	}
}