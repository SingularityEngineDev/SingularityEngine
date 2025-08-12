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

#include <SDL3/SDL.h>

#include <sngl/core/IWindow.h>

#include <string>
#include <span>
#include <unordered_map>
#include <memory>


namespace sngl::core
{
   struct IEvent;
   class CEventQueue;

   class CWindow : public IWindow
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
      CWindow(const std::string& title);
      ~CWindow();

      void pushWindowEvents(CEventQueue* eventQueue);

      void setTitle(const std::string_view title) override;
      const std::string_view getTitle() const override;

   private:
      const SDisplay& getPrimaryDisplay();
      std::unique_ptr<IEvent> translateToSnglEvent(const SDL_Event& e);

      std::string m_title;
      std::unordered_map<SDL_DisplayID, SDisplay> m_displays;

      SDL_Window* m_handle;
   };
}