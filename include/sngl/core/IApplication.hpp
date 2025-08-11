namespace sngl::core
{
   class IEngine;

   class IApplication
   {
   public:
      IApplication() = default;
      virtual ~IApplication() = default;

      virtual void onInit(IEngine* engine)
      {
         m_engine = engine;
      }

      virtual void onUpdate() = 0;
      virtual void onRender() = 0;
      virtual void onExit() = 0;

   protected:
      IEngine* m_engine = nullptr;
   }; // IApplication
} // sngl::core