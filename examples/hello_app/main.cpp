#include <Singularity.hpp>
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
      std::cout << "Initializing\n";
   }

   void onUpdate() override
   {
      std::cout << "Updating\n";
   }

   void onRender() override
   {
      std::cout << "Rendering\n";
   }

   void onExit() override
   {
      std::cout << "Exiting\n";
   }
};

SNGL_INVOKE_MAIN(HelloApp);