#ifndef _SNGL_CORE_CEVENTDISPATCHER_H_INCLUDED_
#define _SNGL_CORE_CEVENTDISPATCHER_H_INCLUDED_

#include <sngl/core/IEventDispatcher.h>

#include <vector>
#include <unordered_map>

namespace sngl::core
{
   class CEventDispatcher : public IEventDispatcher
   {
   private:
      using EventCategory = IEvent::EventCategory;

   public:
      void dispatch(const IEvent& e);
      void subscribe(IEvent::EventCategory category, EventCallback cb) override;

   private:
      std::unordered_map<EventCategory, std::vector<EventCallback>> m_listeners;
   };
}

#endif