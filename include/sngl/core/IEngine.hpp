#include <sngl/core/IApplication.hpp>
#include <sngl/definitions.h>

namespace sngl::core
{
   class IEngine
   {
   public:
      IEngine() = default;
      virtual ~IEngine() = default;

      virtual bool runApp(IApplication* app) = 0;
   };

   SNGL_API IEngine* CreateEngine();
}