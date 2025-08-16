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

#include "pch.h"

#include <sngl/core/IEngine.h>
#include <sngl/core/IApplication.h>

#include "CWindow.h"
#include "CEventQueue.h"
#include "CEventDispatcher.h"
#include "CSpdlogLogger.h"
#include "RendererFactory.h"

#include "Events/WindowEvents.h"

using namespace sngl::core;

class CEngine final : public IEngine
{
private:
   IApplication* m_currentApplication;
   std::unique_ptr<CWindow> m_window;
   CEventQueue m_queue;
   CEventDispatcher m_eventDispatcher;
   bool m_running = true;

   std::unique_ptr<CSpdlogLogger> m_systemLogger;
   std::unique_ptr<IInternalRenderer> m_renderer;

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

   std::unique_ptr<ILogger> createLogger(const std::string& name) override
   {
       return std::make_unique<CSpdlogLogger>(name);
   }

private:
   inline void init()
   {
      m_systemLogger = std::make_unique<CSpdlogLogger>("Singularity-System");
#ifdef SNGL_DEBUG
      m_systemLogger->log(ILogger::ELL_INFO, "System logger created!");
#endif
      m_window = std::make_unique<CWindow>("Singularity Engine");
      m_eventDispatcher.subscribe(IEvent::EC_CORE, [this](const IEvent& e) { coreEventCallback(e); });
      m_renderer = RendererFactory::CreateRecommendedRenderer();
      m_renderer->initialize();
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
      if (event.getName() == events::WindowCloseEvent::EVENT_NAME)
         exit();
   }
};

IEngine* sngl::core::CreateEngine()
{
   return new CEngine();
}