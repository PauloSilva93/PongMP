#pragma once
#include <string>
#include <vector>

namespace Helpers {

    namespace String {

        std::vector<std::string> Split(std::string& input, char delimiter);
        
        /**
         * @brief Convert a string to an array of char 
         * @param str the string to be converted 
         * @return a pointer to char
         */
        char* StringToChar(const std::string str); 
    
    };
    

};