/*
 *  text.h
 */
#pragma once

namespace Text
{
    void printLogo();
    void divider();
    
    template<class T>
    void print(T body, std::string prefix = "loader")
    {
        std::cout << "[" + prefix + "] " << body << std::endl;
    }
}
