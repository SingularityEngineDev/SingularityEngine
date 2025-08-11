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