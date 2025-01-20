// C++ program to implement a basic logging system.
// 
// Adapted from https://www.geeksforgeeks.org/logging-system-in-cpp/ using ChatGPT 3.5
// F.L.S. January 2025

#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstdarg> 
using namespace std;

// Enum to represent log levels
enum LogLevel { DEBUG, INFO, WARNING, ERROR, CRITICAL };

class Logger {
public:
    // Constructor: Opens the log file in append mode
    Logger(const string& filename)
    {
        logFile.open(filename, ios::app);
        if (!logFile.is_open()) {
            cerr << "Error opening log file." << endl;
        }
    }

    // Destructor: Closes the log file
    ~Logger() { logFile.close(); }

    // Logs a message with a given log level
    void log(LogLevel level, const char* format, ...)
    {
        // Get current timestamp
        time_t now = time(0);
        tm* timeinfo = localtime(&now);
        char timestamp[20];
        strftime(timestamp, sizeof(timestamp),
                 "%Y-%m-%d %H:%M:%S", timeinfo);

        // Start processing the variadic arguments
        va_list args;
        va_start(args, format);

        // Create log entry stream
        std::ostringstream logEntry;

        // Add timestamp and log level to the log entry
        logEntry << "[" << timestamp << "] "
                 << levelToString(level) << ": ";

        // Format the message and append to logEntry
        char buffer[1024];  // Temporary buffer for formatted message
        vsnprintf(buffer, sizeof(buffer), format, args);  // Format the message
        logEntry << buffer;

        // End variadic argument processing
        va_end(args);

        // Output to console
        cout << logEntry.str();

        // Output to log file
        if (logFile.is_open()) {
            logFile << logEntry.str();
            logFile.flush(); // Ensure immediate write to file
        }
    }

private:
    ofstream logFile; // File stream for the log file

    // Converts log level to a string for output
    string levelToString(LogLevel level)
    {
        switch (level) {
        case DEBUG:
            return "DEBUG";
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        case CRITICAL:
            return "CRITICAL";
        default:
            return "UNKNOWN";
        }
    }
};