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
#include <iostream>
#include <filesystem>
#include <fstream>
#include <array>

#include <sngl_asset_format/header.h>
#include <sngl_asset_format/file_entry.h>

#include <argparse/argparse.hpp>

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>

#define BASE_FORMATTING "[%n] [%d.%m.%Y %T] [%=8l] %v"
#define COLOR_FORMATTING "%^" BASE_FORMATTING "%$"

namespace fs = std::filesystem;

static std::shared_ptr<spdlog::sinks::basic_file_sink_mt> s_fileSink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("SingularityPackman.log", false);
static std::shared_ptr<spdlog::sinks::stdout_color_sink_mt> s_consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

static std::unique_ptr<spdlog::logger> s_logger = nullptr;

static bool s_skipPrompts = false;

inline bool prompt(const std::string_view question)
{
	static constexpr const char* CHOICE_STRING = "Choice (type yes or no): ";

	if (s_skipPrompts)
		return true;

	std::string choice;

	std::cout << question << "\n" << CHOICE_STRING;
	std::cin >> choice;

	while (true)
	{
		if (choice == "yes")
			return true;
		else if (choice == "no")
			return false;
		else
			std::cout << "Invalid choice.\n" << CHOICE_STRING;
	}
}

int pack(const std::string& archivePath, const std::vector<std::string>& paths)
{
	using Header = sngl::asset_format::Header;
	using HeaderVersion = sngl::asset_format::HeaderVersion;
	using FileEntry = sngl::asset_format::FileEntry;

	if (fs::exists(archivePath))
	{
		if (!prompt("Archive already exists. Overwrite?"))
			return 0;
	}

	// preinitialize header
	Header header =
	{
		.magic = SNGL_ASSET_FORMAT_MAGIC_VALUE,
		.version = { 1, 0, 0 },
	};

	struct SEntry
	{
		std::string realFilePath;
		FileEntry entry;
	};

	std::vector<SEntry> parsedEntries;
	uint64_t currentOffset = 0;

	for (const auto& path : paths)
	{
		if (not fs::exists(path))
		{
			s_logger->critical("Cannot pack an asset. {} doesn't exist.", path);
			return -1;
		}

		if (not fs::is_directory(path))
		{
			SEntry e{};
			e.realFilePath = path;
			std::strncpy(e.entry.virtualPath, path.data(), path.size());
			e.entry.size = fs::file_size(path);
			e.entry.offset = currentOffset;
			currentOffset += e.entry.size;
			parsedEntries.emplace_back(std::move(e));
		}

		for (const auto& dirEntry : fs::recursive_directory_iterator(path))
		{
			if (dirEntry.is_directory())
				continue;

			auto relative = fs::relative(dirEntry.path(), path).generic_string();
			s_logger->info("Processing {}", relative);

			SEntry e{};
			e.realFilePath = dirEntry.path().generic_string();
			std::strncpy(e.entry.virtualPath, relative.data(), relative.size());
			e.entry.size = dirEntry.file_size();
			e.entry.offset = currentOffset;
			currentOffset += e.entry.size;
			parsedEntries.emplace_back(std::move(e));
		}
	}

	header.fileEntryCount = parsedEntries.size();
	std::ofstream archive(archivePath, std::ios::binary | std::ios::trunc);

	archive.write(reinterpret_cast<const char*>(&header), sizeof(Header));

	// TODO: don't loop twice, it's redundant
	for (const auto& entry : parsedEntries)
	{
		archive.write(reinterpret_cast<const char*>(&entry.entry), sizeof(FileEntry));
	}

	static constexpr size_t BUFFER_SIZE = (1 << 11);
	std::array<char, BUFFER_SIZE> buffer;

	for (const auto& entry : parsedEntries)
	{
		std::ifstream file(entry.realFilePath, std::ios::binary);
		size_t filesize = entry.entry.size;

		while (filesize > 0)
		{
			// TODO: writing this at 4.00 AM, there must be a way to optimize this :D
			size_t toRead = BUFFER_SIZE;
			if (filesize < BUFFER_SIZE)
				toRead = filesize;

			file.read(buffer.data(), toRead);
			archive.write(buffer.data(), toRead);
			filesize -= toRead;
		}
	}

	return 0;
}

int main(int argc, char** argv)
{
	s_fileSink->set_level(spdlog::level::info);
	s_fileSink->set_pattern(BASE_FORMATTING);

	s_consoleSink->set_level(spdlog::level::info);
	s_consoleSink->set_pattern(COLOR_FORMATTING);

	s_logger = std::make_unique<spdlog::logger>("Singularity-Packman", spdlog::sinks_init_list{ s_fileSink, s_consoleSink });

	argparse::ArgumentParser parser("SingularityPackman", "1.0", argparse::default_arguments::help, true);
	parser.add_argument("-y")
		.help("Answers \"yes\" to every prompt")
		.flag();

	// PACK SUBCOMMAND
	argparse::ArgumentParser pack_subcommand("pack");
	pack_subcommand.add_description("Pack a singularity archive");

	pack_subcommand.add_argument("archive_path")
		.required()
		.nargs(1)
		.help("A path to the archive");

	pack_subcommand.add_argument("paths_to_files_or_directories")
		.required()
		.nargs(argparse::nargs_pattern::at_least_one)
		.help("List of paths to assets or directories of assets that the archive should include");

	parser.add_subparser(pack_subcommand);
	// END PACK SUBCOMMAND

	try
	{
		parser.parse_args(argc, argv);
	}
	catch (const std::exception& e)
	{
		s_logger->critical("Packman failed to parse arguments.");
		std::cout << e.what();

		return -1;
	}

	if (parser.get<bool>("-y"))
		s_skipPrompts = true;

	if (parser.is_subcommand_used(pack_subcommand))
	{
		const auto archivePath = pack_subcommand.get<std::string>("archive_path");
		const auto files = pack_subcommand.get<std::vector<std::string>>("paths_to_files_or_directories");
		return pack(archivePath, files);
	}

	return 0;
}