#include <sngl/core/IEngine.hpp>

#include "CWindow.h"
#include "CEventQueue.h"

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
      m_queue.pollWindowEvents();

      Event e;
      while (m_queue.poll(e))
      {
         if (e.type == EngineEventType::WindowClose)
            m_running = false;
      }

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
   CEventQueue m_queue;
   bool m_running = true;
};

IEngine* sngl::core::CreateEngine()
{
   return new CEngine();
}