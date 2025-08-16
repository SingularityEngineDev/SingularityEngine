#ifndef _SNGL_CORE_RENDERERFACTORY_H_INCLUDED_
#define _SNGL_CORE_RENDERERFACTORY_H_INCLUDED_

#include "IInternalRenderer.h"

namespace sngl::core
{
	class RendererFactory
	{
	public:
		enum class RendererAPI { D3D11 };

		static std::unique_ptr<IInternalRenderer> CreateRecommendedRenderer();
		static std::unique_ptr<IInternalRenderer> CreateRenderer(RendererAPI api);
	};
}

#endif