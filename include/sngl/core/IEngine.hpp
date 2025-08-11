#ifndef _SNGL_CORE_IENGINE_H_INCLUDED_
#define _SNGL_CORE_IENGINE_H_INCLUDED_

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
      virtual void exit() = 0;
   };

   SNGL_API IEngine* CreateEngine();
}

#endif