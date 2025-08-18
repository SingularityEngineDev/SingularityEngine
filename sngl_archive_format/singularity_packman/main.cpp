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

#include <stdexcept>

#include <sngl_asset_format/header.h>
#include <sngl_asset_format/file_entry.h>

#include <argparse/argparse.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#define BASE_FORMATTING "[%n] [%d.%m.%Y %T] [%=8l] %v"
#define COLOR_FORMATTING "%^" BASE_FORMATTING "%$"

static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> s_fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("SingularityPackman.log", false);
static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

static std::unique_ptr<spdlog::logger> s_logger = nullptr;

int main(int argc, char** argv)
{
	s_fileSink->set_level(spdlog::level::info);
	s_fileSink->set_pattern(BASE_FORMATTING);

	s_consoleSink->set_level(spdlog::level::info);
	s_consoleSink->set_pattern(COLOR_FORMATTING);

	s_logger = std::make_unique<spdlog::logger>("Singularity-Packman", spdlog::sinks_init_list{ s_fileSink, s_consoleSink });

	argparse::ArgumentParser parser("SingularityPackman");
	argparse::ArgumentParser pack_subcommand("pack");
	pack_subcommand.add_description("Pack a singularity archive");
	pack_subcommand.add_argument("paths_to_files_or_directories")
		.required()
		.nargs(argparse::nargs_pattern::at_least_one)
		.help("List of paths to assets or directories of assets that the archive should include");

	parser.add_subparser(pack_subcommand);

	try
	{
		parser.parse_args(argc, argv);
	}
	catch (const std::exception& e)
	{
		s_logger->critical("Packman failed to parse arguments:\n{}", e.what());
		return -1;
	}
	
	return 0;
}