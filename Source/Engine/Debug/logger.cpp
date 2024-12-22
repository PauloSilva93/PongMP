#include "logger.hpp"
#include <string>
#include <cstdarg>
#include <iostream>

namespace Debug {

    // Initialize Variable Static
    std::vector<LogMessage> Logger::messages = std::vector<LogMessage>();

    // Log Functions
    void Logger::Log(const char* file, int line, ELogLevel level, const char* tag, const char* format, ...){

        LogMessage msg;

        std::string fileStr = file;
        fileStr = fileStr.substr(fileStr.find_last_of("/\\")+1);    
        char* fileChar = new char[fileStr.length()+1];
        std::copy(fileStr.begin(), fileStr.end(), fileChar);
        fileChar[fileStr.size()] = '\0';
        msg.file = fileChar;

        switch(level){
            case ELogLevel::DEBUG:   msg.levelText = "DEBUG  ";   break;
            case ELogLevel::VERBOSE: msg.levelText = "VERBOSE"; break;
            case ELogLevel::SUCCESS: msg.levelText = "SUCCESS"; break;
            case ELogLevel::WARNING: msg.levelText = "WARNING"; break;
            case ELogLevel::ERROR:   msg.levelText = "ERROR  ";   break;
            case ELogLevel::ASSERT:  msg.levelText = "ASSERT ";  break;
            default: msg.levelText = "UNDEFINED"; break;
        };

        msg.lineNumber = line;
        msg.timestamp = std::time(nullptr);
        msg.level = level;
        msg.tag = tag;

        va_list args;
        va_start(args, format);
        vsnprintf(msg.message, 256, format, args);
        va_end(args);

        messages.push_back(msg);
    #ifdef LOG_ON_IOSTREAM
        LogIOStream(msg);
    #endif

        if(messages.size() > 100){

            char textTime[32];
            std::time_t timestamp = std::time(nullptr);
            std::tm timePtr; 
            localtime_s(&timePtr, &timestamp);
            std::strftime(textTime, sizeof(textTime), "%Y-%m-%d %H-%M-%S", &timePtr);

            std::string path = "./Logs/Log data - " + std::string(textTime) + ".log";
            Logger::ToFile(path.c_str());

            messages.clear();

        }

    };

    void Logger::ToFile(const char* path){

        std::string buffer;

        // Loop throught all messages
        // --------------------------
        for (int i = 0; i < messages.size(); i++){

            LogMessage msg = messages[i];

            std::tm ptm;
            localtime_s(&ptm, &msg.timestamp);
            char timeBuffer[32];
            std::strftime(timeBuffer, sizeof(timeBuffer), "%Y-%m-%d  %H:%M:%S", &ptm);

            buffer += timeBuffer + std::string("  ");
            buffer += msg.file + std::string(":") + std::to_string(msg.lineNumber) + std::string("\t\t");
            
            switch(msg.level){
                case ELogLevel::DEBUG:      buffer += "DEBUG   | ";      break;
                case ELogLevel::VERBOSE:    buffer += "VERBOSE | ";      break;
                case ELogLevel::SUCCESS:    buffer += "SUCCESS | ";      break;
                case ELogLevel::WARNING:    buffer += "WARNING | ";      break;
                case ELogLevel::ERROR:      buffer += "ERROR   | ";      break;
                case ELogLevel::ASSERT:     buffer += "ASSERT  | ";      break;
                default: break;
            };

            buffer += msg.tag + std::string(": ");
            buffer += msg.message;
            buffer += "\n";

        }

        // LEVEL | [TAG]: Message
        // - YYYY-MM-DD   HH:MM:SS   FILE:LINE

        // Write All Messages inside a file
        // --------------------------------
        //File::Physical file;
        //file.Create(path, reinterpret_cast<TypeDef::byte*>(&buffer[0]));

    };
    
    void Logger::TagToFile(const char* tag){

        // Loop throught all messages by tag
        // ---------------------------------
        std::vector<LogMessage> tagMessage;
        for (int i = 0; i < messages.size(); i++){

            LogMessage msg = messages[i];
            if (std::strcmp(msg.tag, tag) == 0){
                tagMessage.push_back(msg);
            };

        };

        // Set File Tag Name
        // -----------------
        std::string path(tag);
        path = "./Logs/" + path + ".log";

        // Loop throught all messages
        // --------------------------
        std::string buffer;
        for (int i = 0; i < tagMessage.size(); i++){

            LogMessage msg = tagMessage[i];

            std::tm ptm;
            localtime_s(&ptm, &msg.timestamp);
            char timeBuffer[32];
            std::strftime(timeBuffer, 32, "%Y-%m-%d  %H:%M:%S", &ptm);

            buffer += timeBuffer + std::string("  ");
            buffer += msg.file + std::string(":") + std::to_string(msg.lineNumber) + std::string("\t\t");
            
            switch(msg.level){
                case ELogLevel::DEBUG:      buffer += "DEBUG   | ";      break;
                case ELogLevel::VERBOSE:    buffer += "VERBOSE | ";      break;
                case ELogLevel::SUCCESS:    buffer += "SUCCESS | ";      break;
                case ELogLevel::WARNING:    buffer += "WARNING | ";      break;
                case ELogLevel::ERROR:      buffer += "ERROR   | ";      break;
                case ELogLevel::ASSERT:     buffer += "ASSERT  | ";      break;
                default: break;
            };

            buffer += msg.tag + std::string(": ");
            buffer += msg.message;
            buffer += "\n";

        }

        // LEVEL | [TAG]: Message
        // - YYYY-MM-DD   HH:MM:SS   FILE:LINE

        // Write All Messages inside a file
        // --------------------------------
        //File::Physical file;
        //file.Create(path, reinterpret_cast<TypeDef::byte*>(&buffer[0]));

    };

    void Logger::LogIOStream(LogMessage& msg) {

        // LEVEL | [TAG]: Message
        // - YYYY-MM-DD   HH:MM:SS   FILE:LINE

        std::string textColor = "";
        std::string textLevel = "";

        switch(msg.level){
            case ELogLevel::DEBUG:   textColor = "\033[1;37m"; textLevel = "DEBUG  "; break;
            case ELogLevel::VERBOSE: textColor = "\033[1;90m"; textLevel = "VERBOSE"; break;
            case ELogLevel::SUCCESS: textColor = "\033[1;32m"; textLevel = "SUCCESS"; break;
            case ELogLevel::WARNING: textColor = "\033[1;33m"; textLevel = "WARNING"; break;
            case ELogLevel::ERROR:   textColor = "\033[1;31m"; textLevel = "ERROR  "; break;
            case ELogLevel::ASSERT:  textColor = "\033[1;35m"; textLevel = "ASSERT "; break;
        }

        char textTime[96];
        std::tm timePtr;
        localtime_s(&timePtr, &msg.timestamp);
        std::strftime(textTime, sizeof(textTime), "%Y-%m-%d  %H:%M:%S", &timePtr);

        std::cout << textColor << textTime << "    "
                    << msg.file << ":" << msg.lineNumber << "    " 
                    << textLevel << " | " 
                    << "[" << msg.tag << "]: " << msg.message
                    << "\033[0m" << std::endl;


    };

};