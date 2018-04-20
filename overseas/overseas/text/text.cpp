//
//  text.cpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "text.h"
#include "login.h"

void CText::printASCII()
{
    std::cout << "------------------------------" << std::endl;
    std::cout << "   ___________   __________ " << std::endl;
    std::cout << "  / ____/ ___/_ / ____/ __ \\" << std::endl;
    std::cout << " / /    \\__ \(_)  / __/ / / /" << std::endl;
    std::cout << "/ /___ ___/ / / /_/ / /_/ / " << std::endl;
    std::cout << "\\____//____(_)\\____/\\____/  " << std::endl;
    std::cout << "------------------------------" << std::endl;
}

void CText::print(std::string message, int c)
{
    if(c == 1)
    {
        std::cout << "[loader] " + message + " Loader made by levaa. https://github.com/gLevaa/overseas-loader/" << std::endl;
    }
    else
    {
        std::cout << "[loader] " + message << std::endl;
    }
}

void CText::askInputs()
{
    std::cout << "[loader] enter your username: ";
    std::cin >> CLogin::Data::username;
    
    std::cout << "[loader] enter your password: ";
    std::cin >> CLogin::Data::password;

}

void CText::divider()
{
    std::cout << "------------------------------" << std::endl;
}
