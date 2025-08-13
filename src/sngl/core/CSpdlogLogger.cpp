#include "CSpdlogLogger.h"

#define BASE_FORMATTING "[%n] [%d.%m.%Y %T] [%=8l] %v"
#define COLOR_FORMATTING "%^" BASE_FORMATTING "%$"

using console_sink_t = spdlog::sinks::stdout_color_sink_mt;
using file_sink_t = spdlog::sinks::basic_file_sink_mt;
using CSpdlogLogger = sngl::core::CSpdlogLogger;

std::shared_ptr<console_sink_t> CSpdlogLogger::s_conSink = nullptr;

CSpdlogLogger::CSpdlogLogger(const std::string& loggerName)
{
   if (!s_conSink)
   {
      s_conSink = std::make_shared<console_sink_t>();
#ifdef SNGL_DEBUG
      s_conSink->set_level(spdlog::level::trace);
#else
      s_conSink->set_level(spdlog::level::warn);
#endif
      s_conSink->set_pattern(COLOR_FORMATTING);
   }

   m_fileSink = std::make_shared<file_sink_t>(fmt::format("log/{}.log", loggerName), true);
   m_fileSink->set_level(spdlog::level::trace);
   m_fileSink->set_pattern(BASE_FORMATTING);

   spdlog::sinks_init_list sinks{ m_fileSink, s_conSink };
   m_logger = std::make_unique<spdlog::logger>(loggerName, sinks);
}

CSpdlogLogger::~CSpdlogLogger()
{}

void CSpdlogLogger::logImpl(ELogLevel level, const char* fmt, va_list args)
{
   va_list args_copy;
   va_copy(args_copy, args);

   int len = std::vsnprintf(nullptr, 0, fmt, args_copy);
   va_end(args_copy);

   std::vector<char> buffer(len + 1);
   std::vsnprintf(buffer.data(), buffer.size(), fmt, args);

   std::string msg(buffer.data(), len);
   switch (level)
   {
   case ELL_TRACE:
      m_logger->trace(msg);
      break;
   case ELL_DEBUG:
      m_logger->debug(msg);
      break;
   case ELL_INFO:
      m_logger->info(msg);
      break;
   case ELL_WARN:
      m_logger->warn(msg);
      break;
   case ELL_ERROR:
      m_logger->error(msg);
      break;
   case ELL_CRITICAL:
      m_logger->critical(msg);
      break;
   default:
      break;
   }
}