//create by Zain Raza


#include <ctime>
#include <fstream>

#include "Logger.h"

Logger& Logger::getInstance() {
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly
    static Logger instance;
    return instance;
}

Logger::Logger() {
    filename = "logs.log";
    loggerfile.open (filename);
}

Logger::~Logger() {
    loggerfile.close();
}

string Logger::getFileName() {
    return filename;
}

void Logger::log(string output) {
    time_t timer;
    char buffer[26];
    struct tm* tm_info;

    time(&timer);
    tm_info = localtime(&timer);

    strftime(buffer, 26, "%Y-%m-%d %H:%M:%S", tm_info);

    loggerfile << buffer << " - " << output << endl;

}

