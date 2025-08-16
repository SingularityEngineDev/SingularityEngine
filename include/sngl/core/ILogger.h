#ifndef _SNGL_CORE_ILOGGER_H_INCLUDED_
#define _SNGL_CORE_ILOGGER_H_INCLUDED_

namespace sngl::core
{
   class ILogger
   {
   public:
      enum ELogLevel { ELL_TRACE, ELL_DEBUG, ELL_INFO, ELL_WARN, ELL_ERROR, ELL_CRITICAL };

      virtual ~ILogger() = default;

      inline void log(ELogLevel level, const char* fmt, ...)
      {
         va_list args;
         va_start(args, fmt);
         logImpl(level, fmt, args);
         va_end(args);
      }

   protected:
      virtual void logImpl(ELogLevel level, const char* fmt, va_list args) = 0;
   };
}

#endif