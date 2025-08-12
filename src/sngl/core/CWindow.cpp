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

#include "CWindow.h"
#include "CEventQueue.h"

#include "Events/WindowCloseEvent.h"

using CWindow = sngl::core::CWindow;
using CEventQueue = sngl::core::CEventQueue;
using IEvent = sngl::core::IEvent;

static constexpr uint32_t DEFAULT_WINDOW_CREATION_FLAGS =
SDL_WINDOW_RESIZABLE
#ifdef SNGL_VULKAN_ENABLED
| SDL_WINDOW_VULKAN
#endif
| SDL_WINDOW_HIGH_PIXEL_DENSITY;

CWindow::SDisplay::SDisplay(SDL_DisplayID id)
{
   name = SDL_GetDisplayName(id);
   contentScale = SDL_GetDisplayContentScale(id);
   auto* displayMode = SDL_GetCurrentDisplayMode(id);

   width = displayMode->w;
   height = displayMode->h;
   pixelDensity = displayMode->pixel_density;
   refreshRate = displayMode->refresh_rate;
}

CWindow::CWindow(const std::string& title)
   : m_title(title)
{
   SDL_Init(SDL_INIT_VIDEO);
   
   {
      int displayCount;
      auto* displays = SDL_GetDisplays(&displayCount);
      m_displays.reserve(displayCount);

      if (!displays) {}
         // TODO: throw error

      // get them to span for ez iteration
      auto rawDisplays = std::span<SDL_DisplayID>(displays, displays + displayCount);

      for (const auto& display : rawDisplays)
         m_displays.emplace(display, SDisplay(display));

      SDL_free(displays);
   }

   const auto& primaryDisplay = getPrimaryDisplay();
   m_handle = SDL_CreateWindow(title.c_str(), primaryDisplay.width, primaryDisplay.height, DEFAULT_WINDOW_CREATION_FLAGS);
}

CWindow::~CWindow()
{

}

void CWindow::pushWindowEvents(CEventQueue* eventQueue)
{
   SDL_Event e;
   while (SDL_PollEvent(&e))
   {
      auto snglEvent = translateToSnglEvent(e);
      if (!snglEvent)
         continue;
      eventQueue->push(std::move(snglEvent));
   }
}

void CWindow::setTitle(const std::string_view title)
{
   m_title = title;
   SDL_SetWindowTitle(m_handle, m_title.c_str());
}

const std::string_view CWindow::getTitle() const
{
   return m_title;
}

const CWindow::SDisplay& CWindow::getPrimaryDisplay()
{
   return m_displays[SDL_GetPrimaryDisplay()];
}

std::unique_ptr<IEvent> CWindow::translateToSnglEvent(const SDL_Event& e)
{
   switch (e.type)
   {
   case SDL_EVENT_QUIT:
      return std::make_unique<events::WindowCloseEvent>();
   default:
      return nullptr;
   }
}