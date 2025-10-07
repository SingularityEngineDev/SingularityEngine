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

#include <sngl/core/IWindow.h>
#include <sngl/shared/WindowsHeaders.h>
#include <sngl/shared/UnixHeaders.h>

namespace sngl::core
{
   struct IEvent;
   class CEventQueue;

   class CWindow final : public IWindow
   {
   private:
      struct SDisplay
      {
         SDisplay() {}
         SDisplay(SDL_DisplayID id);

         std::string_view name;
         float contentScale;
         uint32_t width;
         uint32_t height;
         float pixelDensity;
         float refreshRate;
      };

   public:
        union OSHandle_t
        {
            void* win32Value;
            uint32_t x11Value;
            void* waylandValue;
            void* cocoaValue;
        };

      CWindow(const std::string& title);
      ~CWindow();

      void pushWindowEvents(CEventQueue* eventQueue);

      void setTitle(const std::string_view title) override;
      const std::string_view getTitle() const override;

      void setSize(const uint32_t width, const uint32_t height) override;
      uint32_t getWidth() const override { return m_width; }
      uint32_t getHeight() const override { return m_height; }

      enum E_WINDOWDRIVER : uint8_t 
      {
          E_WINDOWDRIVER_WINDOWS, 
          E_WINDOWDRIVER_X11, 
          E_WINDOWDRIVER_WAYLAND,
          E_WINDOWDRIVER_COCOA, 
          E_WINDOWDRIVER_UNSET = 0xff // for internal use only
      };

      E_WINDOWDRIVER getWindowDriver() const;
      OSHandle_t getNativeHandle() const;

   private:
      const SDisplay& getPrimaryDisplay();
      std::unique_ptr<IEvent> translateToSnglEvent(const SDL_Event& e);

      std::string m_title;
      std::unordered_map<SDL_DisplayID, SDisplay> m_displays;

      uint32_t m_width, m_height;

      SDL_Window* m_handle;
      mutable E_WINDOWDRIVER m_cachedWindowDriverValue =
#ifdef SNGL_BUILD_PLATFORM_WINDOWS
          E_WINDOWDRIVER_WINDOWS;
#elif defined(SNGL_BUILD_PLATFORM_UNIX)
          E_WINDOWDRIVER_UNSET;
#endif
   };
}