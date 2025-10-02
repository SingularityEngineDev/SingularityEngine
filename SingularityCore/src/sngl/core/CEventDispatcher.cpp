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