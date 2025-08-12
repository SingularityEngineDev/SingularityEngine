#ifndef _SNGL_CORE_EVENTS_WINDOWCLOSEEVENT_H_INCLUDED_
#define _SNGL_CORE_EVENTS_WINDOWCLOSEEVENT_H_INCLUDED_

#include <sngl/core/IEvent.h>

namespace sngl::core::events
{
   constexpr const char* WINDOWCLOSE_EVENT_NAME = "WindowCloseEvent";

   struct WindowCloseEvent final : public IEvent
   {
      EventCategory getCategory() const override { return EventCategory::EC_CORE; }
      inline const char* getName() const override { return WINDOWCLOSE_EVENT_NAME; }
   };
}

#endif