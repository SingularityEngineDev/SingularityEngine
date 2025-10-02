// Copyright 2025 YasInvolved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _SNGL_CORE_D3D11RENDERER_D3D11RENDERER_H_INCLUDED_
#define _SNGL_CORE_D3D11RENDERER_D3D11RENDERER_H_INCLUDED_

#ifdef SNGL_WINDOWS_BUILD

#include "../IInternalRenderer.h"

#include <sngl/core/IEngine.h>
#include <sngl/core/ILogger.h>

#include <wrl/client.h>
#include <dxgi1_6.h>
#include <d3d11.h>

namespace sngl::core::d3d11
{
	class D3D11Renderer final : public IInternalRenderer
	{
	private:
		template <typename T>
		using ComPtr = Microsoft::WRL::ComPtr<T>;

		IEngine* m_engine;
		IWindow& m_window;
		std::unique_ptr<ILogger> m_logger;
		ComPtr<IDXGIFactory7> m_factory;
		ComPtr<ID3D11Device> m_device;
		ComPtr<ID3D11DeviceContext> m_context;

		ComPtr<IDXGISwapChain1> m_swapchain;

		// render targets
		// TODO: triple buffering?
		ComPtr<ID3D11RenderTargetView> m_backBufferRtv;

	public:
		D3D11Renderer(IEngine* engine);
		~D3D11Renderer() = default;

		bool initialize() override;
		void beginFrame() override;
		void endFrame() override;
		void onResize(const uint32_t width, const uint32_t height) override;

	private:
		bool getSwapchainBuffers();
	};
}

#endif

#endif