//
//  utils.cpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "utils.h"

std::string CUtils::exec(const char* cmd, bool remove)
{
    // Execute a shell command and save the output as a string
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        
    }
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
        {
            result += buffer.data();
        }
    }
    
    // Remove the last character of the string, only use when the last char
    // is a new line
    if(remove)
        result.pop_back();
        
        return result;
}

bool CUtils::isProcessActive(std::string process)
{
    std::string oProcess = process;
    
    std::string cmd = "ps -ax | grep " + process;
    process = CUtils::exec(cmd.c_str(), false);
    
    if(process.length() > 100 && process.find(oProcess) != std::string::npos)
    {
        return true;
    }

    
    return false;
}

std::vector<std::string> CUtils::explode(const std::string& str, char delim)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    
    // Split a string at the given character
    // like in php
    for (std::string token; getline(iss, token, delim); )
    {
        result.push_back(move(token));
    }
    
    return result;
}
