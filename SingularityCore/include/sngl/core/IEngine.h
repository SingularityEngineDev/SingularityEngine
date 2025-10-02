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

#ifndef _SNGL_CORE_IENGINE_H_INCLUDED_
#define _SNGL_CORE_IENGINE_H_INCLUDED_

#include <sngl/shared/definitions.h>

namespace sngl::core
{
   class IApplication;
   class IEventDispatcher;
   class IWindow;
   class ILogger;

   class IEngine
   {
   public:
      IEngine() = default;
      virtual ~IEngine() = default;

      virtual bool runApp(IApplication* app) = 0;
      virtual void exit() = 0;

      virtual IEventDispatcher& getEventDispatcher() = 0;
      virtual IWindow& getWindow() = 0;

      virtual std::unique_ptr<ILogger> createLogger(const std::string& name) = 0;
   };

   SNGL_API IEngine* CreateEngine();
}

#endif