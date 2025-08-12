#include <Singularity.h>
#include <iostream>

class HelloApp final : public sngl::core::IApplication
{
public:
   HelloApp()
   {

   }

   ~HelloApp() override
   {

   }

   void onInit(sngl::core::IEngine* engine) override
   {
      IApplication::onInit(engine);
      m_engine->getWindow().setTitle("Hello App");
   }

   void onUpdate() override
   {
   }

   void onRender() override
   {
   }

   void onExit() override
   {
      std::cout << "Exiting\n";
   }
};

SNGL_INVOKE_MAIN(HelloApp);