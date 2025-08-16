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

#ifndef _SNGL_CORE_IEVENT_H_INCLUDED_
#define _SNGL_CORE_IEVENT_H_INCLUDED_

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