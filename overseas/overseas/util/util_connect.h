/*
 *  util_connect.h
 */
#pragma once

#include <curl/curl.h>

namespace Connect
{
    extern std::string server; // unused
    
    std::string sendGet(std::string url, std::string data);
    
    bool downloadFile(std::string url, std::string outPath);
}
