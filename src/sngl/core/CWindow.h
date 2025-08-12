#include <SDL3/SDL.h>

#include <sngl/core/IEngine.hpp>
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