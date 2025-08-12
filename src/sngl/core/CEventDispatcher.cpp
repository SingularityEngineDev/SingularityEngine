#include "CEventDispatcher.h"

using CEventDispatcher = sngl::core::CEventDispatcher;

void CEventDispatcher::dispatch(const IEvent& e)
{
   for (auto& [cat, cbs] : m_listeners)
   {
      if (IEvent::hasCategory(e.getCategory(), cat))
         for (auto& cb : cbs)
            cb(e);
   }
}

void CEventDispatcher::subscribe(IEvent::EventCategory category, EventCallback cb)
{
   m_listeners[category].emplace_back(cb);
}