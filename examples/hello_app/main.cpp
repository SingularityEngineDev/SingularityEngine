#include <Singularity.h>

class HelloApp final : public sngl::core::IApplication
{
private:
    using Logger_t = sngl::core::ILogger;

    std::unique_ptr<Logger_t> m_gameLogger;
public:
   void onInit(sngl::core::IEngine* engine) override
   {
      IApplication::onInit(engine);
      m_engine->getWindow().setTitle("Hello App");
      m_gameLogger = m_engine->createLogger("HelloApp");
      m_gameLogger->log(Logger_t::ELL_INFO, "Game logger created!");
   }

   void onUpdate() override
   {
   }

   void onRender() override
   {
   }

   void onExit() override
   {
       m_gameLogger->log(Logger_t::ELL_INFO, "Exiting");
   }
};

SNGL_INVOKE_MAIN(HelloApp);