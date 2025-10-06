#ifndef _SNGL_CORE_VULKANRENDERER_VULKANRENDERER_H_INCLUDED_
#define _SNGL_CORE_VULKANRENDERER_VULKANRENDERER_H_INCLUDED_

#include "../IInternalRenderer.h"

#include <sngl/core/IEngine.h>

namespace sngl::core::vulkan
{
	class VulkanRenderer final : public IInternalRenderer
	{
	private:
		IEngine* m_engine;
	public:
		inline VulkanRenderer(IEngine* engine) : m_engine(engine) {}
		~VulkanRenderer() = default;

		inline bool initialize() override { return true; }
		inline void beginFrame() override {}
		inline void endFrame() override {}
		inline void onResize(const uint32_t width, const uint32_t height) override {}
	};
}

#endif