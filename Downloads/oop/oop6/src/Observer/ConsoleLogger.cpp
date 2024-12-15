#include "Observer/ConsoleLogger.h"
#include <iostream>

void ConsoleLogger::Update(const std::string& message) {
    std::cout << message << std::endl;
}
