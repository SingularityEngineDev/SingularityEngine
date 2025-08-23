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
#include <filesystem>

#define PACKMAN_BASE_FORMATTING "[%n] [%d.%m.%Y %T] [%=8l] %v"
#define PACKMAN_COLOR_FORMATTING "%^" PACKMAN_BASE_FORMATTING "%$"

namespace fs = std::filesystem;

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

	int pack(const fs::path& archivePath, const std::vector<std::string>& filesToInclude)
	{
		m_logger->info("Creating {}", archivePath.generic_string());
		auto archive = sngl::archive_utils::ArchiveFactory::createArchive();

		auto addFileAndHandleError= [this, &archive](const fs::path& file)
			{
				auto str = file.generic_string();
				m_logger->info("Including: {}", str);
				if (!archive->addFile(file, false))
					m_logger->error("Failed to include {}", str);
			};

		for (const auto& fileToInclude : filesToInclude)
		{
			if (fs::is_directory(fileToInclude))
				for (const auto& entry : fs::recursive_directory_iterator(fileToInclude))
				{
					if (entry.is_directory())
						continue;

					addFileAndHandleError(fs::relative(entry.path(), fileToInclude));
				}
			else
				addFileAndHandleError(fileToInclude);
		}

		archive->write(archivePath);

		return 0;
	}

private:
	static constexpr const char* PROGRAM_BASE_FORMATTING = PACKMAN_BASE_FORMATTING;
	static constexpr const char* PROGRAM_COLOR_FORMATTING = PACKMAN_COLOR_FORMATTING;

	[[maybe_unused]] const bool m_skipPrompts;
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

	pack_command.add_argument("archive")
		.required()
		.nargs(1)
		.help("Path to the archive to be created (or overwritten)");

	pack_command.add_argument("files_to_include")
		.required()
		.nargs(argparse::nargs_pattern::at_least_one)
		.help("Files that should be included in the archive");
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
		fs::path archive = pack_command.get<std::string>("archive");
		std::vector<std::string> files = pack_command.get<std::vector<std::string>>("files_to_include");
		return program.pack(archive, files);
	}

	return 0;
}