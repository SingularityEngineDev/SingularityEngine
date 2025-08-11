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
      return app->run(this);
   }
};

IEngine* sngl::core::CreateEngine()
{
   return new CEngine(); // TODO: Smart pointer in this method?
}