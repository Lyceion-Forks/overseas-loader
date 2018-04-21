//
//  text.cpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//
#include "includes.h"

#include "text.h"
#include "login.h"

void Text::printLogo()
{
    std::cout << "------------------------------"   << std::endl;
    std::cout << "   ___________   __________ "     << std::endl;
    std::cout << "  / ____/ ___/_ / ____/ __ \\"    << std::endl;
    std::cout << " / /    \\__ \(_)  / __/ / / /"   << std::endl;
    std::cout << "/ /___ ___/ / / /_/ / /_/ / "     << std::endl;
    std::cout << "\\____//____(_)\\____/\\____/  "  << std::endl;
    std::cout << "------------------------------"   << std::endl;
    Text::print("Loader made by levaa. https://github.com/gLevaa/overseas-loader/");
    std::cout << "------------------------------"   << std::endl;
}


void Text::divider()
{
    std::cout << "------------------------------" << std::endl;
}
