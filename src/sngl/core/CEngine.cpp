#include <sngl/core/IEngine.hpp>

#include "CWindow.h"

using namespace sngl::core;

class CEngine final : public IEngine
{
public:
   CEngine()
   {

   }

   ~CEngine() override
   {

   }

   bool runApp(IApplication* app) override
   {
      app->onInit(this);
      m_window = new CWindow("Singularity Engine");

      while (m_running)
      {
         update(app);
         app->onRender();
      }
      app->onExit();

      return true;
   }

   void update(IApplication* app)
   {
      m_window->handleEvents(this);
      app->onUpdate();
   }

   void render()
   {

   }

   void exit() override
   {
      m_running = false;
   }

private:
   CWindow* m_window;
   bool m_running = true;
};

IEngine* sngl::core::CreateEngine()
{
   return new CEngine();
}