#include <Singularity.h>

class HelloApp final : public sngl::core::IApplication
{
private:
    using Logger_t = sngl::core::ILogger;
    using Event_t = sngl::core::IEvent;

    std::unique_ptr<Logger_t> m_gameLogger;

public:
   void onInit(sngl::core::IEngine* engine) override
   {
      IApplication::onInit(engine);
      m_engine->getWindow().setTitle("Hello App");
      m_gameLogger = m_engine->createLogger("HelloApp");
      m_gameLogger->log(Logger_t::ELL_INFO, "Game logger created!");

      //if (m_filesystem->mountArchive("some_path"))
      //    m_gameLogger->log(Logger_t::ELL_INFO, "Archive mounted successfully!");
      //else
      //    m_gameLogger->log(Logger_t::ELL_ERROR, "Failed to mount an archive");

      // some event system demo
      m_engine->getEventDispatcher().subscribe(sngl::core::IEvent::EC_CORE, [this](const Event_t& event) { onCoreEvent(event); });
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

   void onCoreEvent(const sngl::core::IEvent& event)
   {
       m_gameLogger->log(Logger_t::ELL_INFO, "Event caputured: %s", event.getName());
   }
};

SNGL_INVOKE_MAIN(HelloApp);