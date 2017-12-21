
#ifndef PROJECT1_LOGGER_H
#define PROJECT1_LOGGER_H
//
// Created by administrator on 02/02/2017.
//

#include <iostream>
#include <string>

using namespace std;

class Logger{

private:
    // Private Constructor
    Logger();;
    // Stop the compiler generating methods of copy the object
    Logger(Logger const& copy);  // Not Implemented
    
    virtual ~Logger();
    
    Logger& operator=(Logger const& copy){};
    // Not Implemented
    
    ofstream loggerfile;
    string filename;

public:
    static Logger& getInstance();
    //prints the contents to cout
    void log(string output);
    string getFileName();
};

#endif //PROJECT1_LOGGER_H
