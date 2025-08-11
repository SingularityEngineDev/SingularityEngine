#include <sngl/core/IEngine.hpp>

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
      while (m_running)
      {
         app->onUpdate();
         app->onRender();
      }
      app->onExit();
   }

private:
   bool m_running = true;
};

IEngine* sngl::core::CreateEngine()
{
   return new CEngine();
}