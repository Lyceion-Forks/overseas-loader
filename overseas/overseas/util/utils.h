//
//  utils.h
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "includes.h"

class CUtils
{
public:
    static std::string exec(const char* cmd, bool remove);
    static bool isProcessActive(std::string process);
    std::vector<std::string> explode(const std::string& str, char delim);
    
};

