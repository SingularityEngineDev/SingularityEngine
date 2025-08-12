#ifndef _SNGL_CORE_EVENT_H_INCLUDED_
#define _SNGL_CORE_EVENT_H_INCLUDED_

#include <stdint.h>

namespace sngl::core
{
   struct IEvent
   {
      enum EventCategory : uint32_t
      {
         EC_NONE = 0,
         EC_CORE = 1 << 0,
         EC_INPUT = 1 << 1,
         EC_GAME = 1 << 2
         // UI, Physics and stuff when implemented
      };

      virtual ~IEvent() = default;
      virtual EventCategory getCategory() const = 0;
      virtual const char* getName() const = 0;

      static inline bool hasCategory(IEvent::EventCategory mask, IEvent::EventCategory category)
      {
         return (static_cast<uint32_t>(mask) & static_cast<uint32_t>(category)) != 0;
      }
   };

   inline IEvent::EventCategory operator|(IEvent::EventCategory a, IEvent::EventCategory b)
   {
      return static_cast<IEvent::EventCategory>(static_cast<uint32_t>(a) | static_cast<uint32_t>(b));
   }
}

#endif