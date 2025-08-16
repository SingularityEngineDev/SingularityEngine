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

#define WIN32_LEAN_AND_MEAN
#include "D3D11Renderer.h"
#include <Windows.h>

using D3D11Renderer = sngl::core::d3d11::D3D11Renderer;

void D3D11Renderer::initialize()
{
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