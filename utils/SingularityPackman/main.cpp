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

#include <UUIDv4.h>
#include <SingularityArchiveUtils.h>
#include <argparse/argparse.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <iostream>

#define PACKMAN_BASE_FORMATTING "[%n] [%d.%m.%Y %T] [%=8l] %v"
#define PACKMAN_COLOR_FORMATTING "%^" PACKMAN_BASE_FORMATTING "%$"

class Program
{
public:
	Program(bool skipPrompts, bool verbose) : m_skipPrompts(skipPrompts), m_verbose(verbose)
	{
		m_consoleSink->set_pattern(PROGRAM_COLOR_FORMATTING);
		if (m_verbose)
			m_consoleSink->set_level(spdlog::level::trace);
		else
			m_consoleSink->set_level(spdlog::level::warn);
		
		m_fileSink->set_pattern(PROGRAM_BASE_FORMATTING);
		m_fileSink->set_level(spdlog::level::trace);

		m_logger = std::make_unique<spdlog::logger>("Singularity-Packman", spdlog::sinks_init_list{ m_consoleSink, m_fileSink });
	}

	int pack()
	{
		m_logger->info("Creating a new archive");
		auto archive = sngl::archive_utils::ArchiveFactory::createArchive();

		return 0;
	}

private:
	static constexpr const char* PROGRAM_BASE_FORMATTING = PACKMAN_BASE_FORMATTING;
	static constexpr const char* PROGRAM_COLOR_FORMATTING = PACKMAN_COLOR_FORMATTING;

	const bool m_skipPrompts;
	const bool m_verbose;
	std::unique_ptr<spdlog::logger> m_logger = nullptr;
	std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> m_consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
	std::shared_ptr<spdlog::sinks::basic_file_sink_mt> m_fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("log/packman.log", true);
};

int main(int argc, char** argv)
{
	argparse::ArgumentParser parser("SingularityPackman");
	parser.add_argument("-y")
		.flag()
		.help("Answers yes to every prompt. Useful for automation");

	parser.add_argument("--verbose")
		.flag()
		.help("Enables verbose logging");

	// BEGIN PACK CMD
	argparse::ArgumentParser pack_command("pack");
	parser.add_subparser(pack_command);
	// END PACK CMD

	try
	{
		parser.parse_args(argc, argv);
	}
	catch (const std::runtime_error& e)
	{
		std::cout << e.what() << "\n";
	}

	Program program(parser.is_used("-y"), parser.is_used("--verbose"));
	
	if (parser.is_subcommand_used(pack_command))
	{
		return program.pack();
	}

	return 0;
}