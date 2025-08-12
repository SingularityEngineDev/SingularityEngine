#ifndef _SNGL_CORE_EVENT_H_INCLUDED_
#define _SNGL_CORE_EVENT_H_INCLUDED_

namespace sngl::core
{
   enum class EngineEventType
   {
      None,
      WindowClose,
      WindowResize,
      KeyDown,
      KeyUp,
      MouseMove,
      MouseButtonDown,
      MouseButtonUp
   };

   struct Event
   {
      EngineEventType type;
      union
      {
         struct { int width, height; } windowResize;
         struct { int keyCode; } key;
         struct { int x, y; } mouseMove;
      };
   };
}

#endif