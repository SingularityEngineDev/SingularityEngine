#include <sngl/core/ILogger.h>

namespace sngl::core
{
   class CSpdlogLogger final : public ILogger
   {
   public:
      CSpdlogLogger(const std::string& loggerName);
      ~CSpdlogLogger();

   protected:
      void logImpl(ELogLevel level, const char* fmt, va_list args) override;

   private:
      static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_conSink;

      std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_fileSink;
      std::unique_ptr<spdlog::logger> m_logger;
   };
}