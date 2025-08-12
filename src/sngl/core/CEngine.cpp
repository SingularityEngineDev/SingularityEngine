#include <sngl/core/IEngine.hpp>
#include <sngl/core/IApplication.hpp>

#include "CWindow.h"
#include "CEventQueue.h"
#include "CEventDispatcher.h"
#include "Events/WindowCloseEvent.h"

using namespace sngl::core;

class CEngine final : public IEngine
{
private:
   IApplication* m_currentApplication;
   CWindow* m_window;
   CEventQueue m_queue;
   CEventDispatcher m_eventDispatcher;
   bool m_running = true;

public:
   CEngine()
   {

   }

   ~CEngine() override
   {

   }

   bool runApp(IApplication* app) override
   {
      m_currentApplication = app;
      init();

      while (m_running)
      {
         update();
         render();
      }
      
      // cleanup
      m_currentApplication = nullptr;
      delete m_window;
      return true;
   }

   IEventDispatcher& getEventDispatcher() override
   {
      return m_eventDispatcher;
   }

   IWindow& getWindow() override
   {
      return *m_window;
   }

private:
   inline void init()
   {
      m_window = new CWindow("Singularity Engine");
      m_eventDispatcher.subscribe(IEvent::EC_CORE, [this](const IEvent& e) { coreEventCallback(e); });
      m_currentApplication->onInit(this);
   }

   inline void update()
   {
      m_window->pushWindowEvents(&m_queue);
      
      std::unique_ptr<IEvent> e;
      while (m_queue.pop(e))
         m_eventDispatcher.dispatch(*e);

      m_currentApplication->onUpdate();
   }

   inline void render()
   {
      m_currentApplication->onRender();
   }

   inline void exit() override
   {
      m_running = false;
      m_currentApplication->onExit();
   }

   void coreEventCallback(const IEvent& event)
   {
      // abusing C++ constexpr and C strings, see src/sngl/core/Events/WindowCloseEvent.h
      // clever trick to compare the pointers instead of strings that improves performance significantly
      // I think I don't need to explain how it works, do I?
      // O(1) vs O(string length)
      if (event.getName() == events::WINDOWCLOSE_EVENT_NAME)
         exit();
   }
};

IEngine* sngl::core::CreateEngine()
{
   return new CEngine();
}