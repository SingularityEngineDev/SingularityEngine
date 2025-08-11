namespace sngl::core
{
   class IEngine;

   class IApplication
   {
   public:
      IApplication() = default;
      virtual ~IApplication() = default;

      virtual bool run(IEngine* engine) = 0;
   }; // IApplication
} // sngl::core