#ifndef _SNGL_CORE_RENDERERFACTORY_H_INCLUDED_
#define _SNGL_CORE_RENDERERFACTORY_H_INCLUDED_

#include "IInternalRenderer.h"
#include <sngl/core/IEngine.h>

namespace sngl::core
{
	class RendererFactory
	{
	public:
		enum class RendererAPI { D3D11 };

		static std::unique_ptr<IInternalRenderer> CreateRecommendedRenderer(IEngine* engine);
		static std::unique_ptr<IInternalRenderer> CreateRenderer(IEngine* engine, RendererAPI api);
	};
}

#endif