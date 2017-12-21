#ifndef HEADER_H
#define HEADER_H

#include <stdlib.h>
#include <limits.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <chrono>
#include <thread>
#include <ctime>
#include "Logger.h"

using namespace std;

// list commands options
const string commands[][2] = {
    {"-help", "Show all commands"},
    {"1", "Bulk add patients into the system (from a file)"},
    {"2", "Add a patient to the system"},
    {"3", "“Treat” a patient in triaged order"},
    {"4", "Print out a patient’s info as a report"},
    {"5", "Print out a report of “treated” patients"},
    {"6", "Know the next patient to be “treated”"},
    {"7", "Print out a report of all the patients in triage"},
    {"8", "Treat all patients"},
    {"9", "Print out all patients by doctor"},
    {"exit", "Terminate program"}
};

// prompt symbol
const string promptSymbol = "$>";

#endif /* HEADER_H */

