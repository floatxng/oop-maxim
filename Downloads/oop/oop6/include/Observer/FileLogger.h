#pragma once
#include "IObserver.h"
#include <fstream>
#include <string>

class FileLogger : public IObserver {
    std::ofstream logFile;
public:
    FileLogger(const std::string& filename);
    ~FileLogger();
    void Update(const std::string& message) override;
};
