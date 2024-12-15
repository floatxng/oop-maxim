#include "Observer/FileLogger.h"
#include <stdexcept>
#include <filesystem>
#include <iostream>

FileLogger::FileLogger(const std::string& filename) {
    std::filesystem::path fullPath = std::filesystem::current_path() / filename;
    std::cout << fullPath;

    std::filesystem::path logDir = fullPath.parent_path();
    if (!std::filesystem::exists(logDir)) {
        std::filesystem::create_directories(logDir);
    }
    
    logFile.open(fullPath, std::ios::app);
    if (!logFile.is_open()) {
        throw std::runtime_error("Не удалось открыть файл логов: " + fullPath.string());
    }
}

FileLogger::~FileLogger() {
    if (logFile.is_open()) {
        logFile.close();
    }
}

void FileLogger::Update(const std::string& message) {
    if (logFile.is_open()) {
        logFile << message << std::endl;
    }
}
