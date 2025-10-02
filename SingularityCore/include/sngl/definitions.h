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

#ifndef _SNGL_DEFINITIONS_H_INCLUDED_
#define _SNGL_DEFINITIONS_H_INCLUDED_

#ifdef SNGL_WINDOWS_BUILD
   #ifdef SNGL_EXPORT
      #define SNGL_API __declspec(dllexport)
   #else
      #define SNGL_API __declspec(dllimport)
   #endif
#else
   #define SNGL_API
#endif

#define SNGL_INVOKE_MAIN(ApplicationClass) \
int main(int argc, char** argv) \
{ \
   auto* engine = sngl::core::CreateEngine(); \
   ApplicationClass* app = new ApplicationClass(); \
   bool res = engine->runApp(app); \
   delete app; \
   delete engine; \
   if (!res) \
      return -1; \
   return 0; \
}

#endif