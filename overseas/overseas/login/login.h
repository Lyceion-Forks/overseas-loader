//
//  login.hpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "includes.h"

class CLogin
{
public:
    void checkData();
    std::string sendRequest(std::string url, std::string data);
    void downloadFile(std::string url, std::string dir);
    void inject(std::string dylibName);

    struct Data
    {
        static std::string error;
        
        static std::string username;
        static std::string password;
        static std::string hwid;
        static std::string token;
        
        struct Correct
        {
            static bool inputs;
            static bool hwid;
            static bool hwidSet;
        }correct;
        
    }data;
};
