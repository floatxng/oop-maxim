#include "Observer/ConsoleLogger.h"
#include <iostream>

std::mutex ConsoleLogger::consoleMutex;

void ConsoleLogger::Update(const std::string& message) {
    std::lock_guard<std::mutex> guard(consoleMutex);
    std::cout << message << std::endl;
}
