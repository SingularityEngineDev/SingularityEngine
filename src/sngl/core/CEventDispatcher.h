// Copyright 2025 YasInvolved
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
// http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _SNGL_CORE_CEVENTDISPATCHER_H_INCLUDED_
#define _SNGL_CORE_CEVENTDISPATCHER_H_INCLUDED_

#include <sngl/core/IEventDispatcher.h>

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