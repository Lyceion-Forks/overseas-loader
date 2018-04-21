/*
 *  login.h
 */
#pragma once

namespace Login
{
    extern std::string username, password, hwid, token;    
    
    void getUserAndPass();
    void handleFailedResponse(int code);
    void handleSuccessfulResponse(int code);
    void checkData();
    void inject();    
}
