#include <SDL3/SDL.h>

#include <string>
#include <span>
#include <unordered_map>

#include <sngl/core/IEngine.hpp>

namespace sngl::core
{
   class CWindow
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

   private:
      const SDisplay& getPrimaryDisplay();

      const std::string m_title;
      std::unordered_map<SDL_DisplayID, SDisplay> m_displays;

      SDL_Window* m_handle;
   };
}