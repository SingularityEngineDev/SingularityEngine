#ifndef _SNGL_CORE_CEVENTQUEUE_H_INCLUDED_
#define _SNGL_CORE_CEVENTQUEUE_H_INCLUDED_

#include <sngl/core/Event.h>
#include <deque>

namespace sngl::core
{
   class CEventQueue
   {
   public:
      inline void push(const Event& e)
      {
         m_events.emplace_back(e);
      }

      inline bool poll(Event& e)
      {
         if (m_events.empty())
            return false;

         e = m_events.front();
         m_events.pop_front();
         return true;
      }

      void pollWindowEvents();

      inline void clear()
      {
         m_events.clear();
      }
      
   private:
      std::deque<Event> m_events;
   };
}

#endif