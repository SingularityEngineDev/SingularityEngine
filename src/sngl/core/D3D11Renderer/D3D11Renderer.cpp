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

#ifdef SNGL_WINDOWS_BUILD

#include "../CWindow.h"

#define WIN32_LEAN_AND_MEAN
#include "D3D11Renderer.h"
#include <Windows.h>

using D3D11Renderer = sngl::core::d3d11::D3D11Renderer;

D3D11Renderer::D3D11Renderer(IEngine* engine) : m_engine(engine)
{
	m_logger = m_engine->createLogger("Singularity-D3D11Renderer");
}

bool D3D11Renderer::initialize()
{
	m_logger->log(ILogger::ELL_INFO, "Initializing renderer");

	UINT factoryFlags = 0;
	#ifdef SNGL_DEBUG
		factoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
	#endif

	if (FAILED(CreateDXGIFactory2(factoryFlags, IID_PPV_ARGS(&m_factory))))
		throw std::runtime_error("Failed to initialize DXGI Factory");

	ComPtr<IDXGIAdapter1> adapter;
	for (UINT i = 0; m_factory->EnumAdapters1(i, &adapter) != DXGI_ERROR_NOT_FOUND; i++)
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);
	
		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
			continue;

		break;
	}

	UINT deviceFlags = 0;
#ifdef SNGL_DEBUG
	deviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	std::array<D3D_FEATURE_LEVEL, 4> featureLevels =
	{
		{
			D3D_FEATURE_LEVEL_11_1,
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_11_0
		}
	};

	D3D_FEATURE_LEVEL featureLevel;

	if (FAILED(D3D11CreateDevice(
		adapter.Get(),
		D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		deviceFlags,
		featureLevels.data(), featureLevels.size(),
		D3D11_SDK_VERSION,
		&m_device,
		&featureLevel,
		&m_deviceContext
	)))
	{
		m_logger->log(ILogger::ELL_CRITICAL, "Failed to create D3D11 Device!");
		return false;
	}

	auto& window = reinterpret_cast<CWindow&>(m_engine->getWindow());

	DXGI_SWAP_CHAIN_DESC1 swapchainDesc = {};
	swapchainDesc.Width = window.getWidth();
	swapchainDesc.Height = window.getHeight();
	swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_SNORM;
	swapchainDesc.Stereo = FALSE;
	swapchainDesc.SampleDesc.Count = 1;
	swapchainDesc.SampleDesc.Quality = 0;
	swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapchainDesc.BufferCount = 2; // TODO: triple buffering, rendering multiple frames on fly
	swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapchainDesc.Flags = 0; // TODO: non-vsync mode, allow tearing

	if (FAILED(m_factory->CreateSwapChainForHwnd(m_device.Get(), window.getNativeWindowHandle(), &swapchainDesc, nullptr, nullptr, &m_swapchain)))
	{
		m_logger->log(ILogger::ELL_CRITICAL, "Failed to create DXGI Swapchain");
		return false;
	}

	return true;
}

void D3D11Renderer::beginFrame()
{

}

void D3D11Renderer::endFrame()
{

}

void D3D11Renderer::present()
{

}

#endif