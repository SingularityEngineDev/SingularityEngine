#include "CWindow.h"

using CWindow = sngl::core::CWindow;

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

const CWindow::SDisplay& CWindow::getPrimaryDisplay()
{
   return m_displays[SDL_GetPrimaryDisplay()];
}