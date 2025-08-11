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

   bool run(sngl::core::IEngine* engine) override
   {
      std::cout << "Hello from app\n";
      return true;
   }
};

SNGL_INVOKE_MAIN(HelloApp);