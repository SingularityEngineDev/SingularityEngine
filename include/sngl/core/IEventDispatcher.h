#ifndef _SNGL_CORE_IEVENTDISPATCHER_H_INCLUDED_
#define _SNGL_CORE_IEVENTDISPATCHER_H_INCLUDED_

#include <sngl/core/IEvent.h>
#include <functional>

namespace sngl::core
{
   class IEventDispatcher
   {
   public:
      using EventCallback = std::function<void(const IEvent&)>;

      virtual ~IEventDispatcher() = default;
      virtual void subscribe(IEvent::EventCategory category, EventCallback cb) = 0;
   };
}

#endif