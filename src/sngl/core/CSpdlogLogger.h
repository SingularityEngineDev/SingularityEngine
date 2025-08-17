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
      static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> s_sharedFileSink;

      std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_fileSink;
      std::unique_ptr<spdlog::logger> m_logger;
   };
}