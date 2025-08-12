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