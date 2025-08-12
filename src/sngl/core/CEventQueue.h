#ifndef _SNGL_CORE_CEVENTQUEUE_H_INCLUDED_
#define _SNGL_CORE_CEVENTQUEUE_H_INCLUDED_

#include <sngl/core/IEvent.h>
#include <deque>
#include <memory>

namespace sngl::core
{
   class CEventQueue
   {
   private:
      using EventPtr = std::unique_ptr<IEvent>;

   public:
      inline void push(std::unique_ptr<IEvent> e)
      {
         m_events.emplace_back(std::move(e));
      }

      inline bool pop(std::unique_ptr<IEvent>& e) 
      {
         if (m_events.empty()) return false;
         e = std::move(m_events.front());
         m_events.pop_front();
         return true;
      }

      inline void clear()
      {
         m_events.clear();
      }
      
   private:
      std::deque<EventPtr> m_events;
   };
}

#endif