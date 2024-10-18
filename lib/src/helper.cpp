#ifndef HELPER_H
#define HELPER_H

#include <spdlog/spdlog.h>

#include <fstream>
#include <iostream>

#include "helper.hpp"

void setLogLevel() {
  const char* logLevel = std::getenv("LOG_LEVEL");

  // Set the log level based on the environment variable
  if (logLevel) {
    if (std::string(logLevel) == "debug") {
      spdlog::set_level(spdlog::level::debug);
    } else if (std::string(logLevel) == "info") {
      spdlog::set_level(spdlog::level::info);
    } else if (std::string(logLevel) == "warn") {
      spdlog::set_level(spdlog::level::warn);
    } else if (std::string(logLevel) == "error") {
      spdlog::set_level(spdlog::level::err);
    } else if (std::string(logLevel) == "critical") {
      spdlog::set_level(spdlog::level::critical);
    } else {
      spdlog::set_level(spdlog::level::off);  // Default to off if invalid
    }
  } else {
    spdlog::set_level(spdlog::level::info);  // Default log level
  }
}

std::expected<std::string, std::string> loadFile(
    const std::filesystem::path& filePath) {
  std::ifstream file(filePath);

  spdlog::debug("Reading file: {}", filePath.string());
  if (!file) {
    return std::unexpected("Error: failed to open file: " + filePath.string());
  }

  std::stringstream buffer;
  buffer << file.rdbuf();
  spdlog::debug("Read file content:\n{}", buffer.str());
  file.close();
  return buffer.str();
}

std::expected<void, std::string> writeFile(
    const std::filesystem::path& filePath, std::string content) {
  std::ofstream file(filePath);

  if (!file) {
    return std::unexpected("Error: failed to open file: " + filePath.string());
  }

  file << content;
  file.close();
  return {};
}

#endif  // HELPER_H
