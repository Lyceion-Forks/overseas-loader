/*
 *
 *
 *
 */
#include "includes.h"

#include "login.h"
#include "text.h"
#include "util.h"
#include "util_connect.h"

namespace Login
{
    std::string username, password, hwid, token;
}

void Login::getUserAndPass()
{
    // Used to check if it's the first time
    // we've taken an input
    bool first = true;
    
    while(Login::username.empty() || Login::password.empty())
    {
        // If it's been blank multiple times
        if(!first)
        {
            Text::print("Please do not leave any field empty");
        }
        
        std::cout << "[loader] enter your username: ";
        std::cin  >> Login::username;
        
        std::cout << "[loader] enter your password: ";
        std::cin  >> Login::password;
        
        // Set first attempt to false since
        // the loop has already run once
        if(first)
            first = false;
    }
    
    // Save original return into oResult
    std::string oResult = Util::execute("ioreg -rd1 -c IOPlatformExpertDevice | awk '/IOPlatformUUID/ { split($0, line, \"\\\"\"); printf(\"\\n%s\\n\\n\", line[4]); }'");
    
    // Edit the string to remove whitespace
    // in oResult (original result)
    Login::hwid = oResult.substr(1, oResult.length() - 3);
}

void Login::handleFailedResponse(int code)
{
    // Switch through each error status code
    switch (code)
    {
        case 202:
            Text::print("User does not exist", "error");
            break;
            
        case 203:
            Text::print("Incorrect password", "error");
            break;
            
        case 204:
            Text::print("Your HWID does not match", "error");
            break;
            
        default:
            Text::print("An unknown error has occured! Please try again later", "error");
            break;
    }
}

void Login::handleSuccessfulResponse(int code)
{
    // Switch through each success status code
    switch (code)
    {
        case 205:
            Text::print("We see this is your first login, your HWID is set.");
            break;
            
        case 206:
            Text::print("Welcome back, " + Login::username);
            break;
            
        default:
            Text::print("An unknown error has occured! Please try again later", "error");
            break;
    }
}

void Login::checkData()
{
    Text::print("Checking data...");
    
    // Ask the server if user is allowed
    // to use the cheat and save result
    std::string res = Connect::sendGet("https://domain.com/moonlight/loader/checks.php",
                                        "username=" + Login::username + "&password=" + Login::password + "&hwid=" + Login::hwid);
    
    int statusCode  = -1;
    
    // Check if the length is longer than
    // the usual status code meaning it
    // also returned a token
    if(res.length() > 3)
    {
        // Is a token response
        // Explode the result into the token
        // status code
        std::vector<std::string> data = Util::explode(res, ':');
        
        // Only using a try catch just incase something is
        // wrong with the response and its not a number
        try
        {
            statusCode = stoi(data[0]);
        }
        catch(std::invalid_argument& e)
        {
            quit(EXIT_FAILURE, "An unknown error has occured! Please try again later");
        }
        
        // Handle the response
        Login::handleSuccessfulResponse(statusCode);
        
        // Save the token
        Login::token = data[1];
    }
    else
    {
        // Is a non token response meaning
        // something went wrong
        
        std::string data = res;
        
        // Only using a try catch just incase something is
        // wrong with the response and its not a number
        try
        {
            statusCode = stoi(data);
        }
        catch(std::invalid_argument& e)
        {
            quit(EXIT_FAILURE, "An unknown error has occured! Please try again later");
        }
        
        // Handle the status code
        Login::handleFailedResponse(statusCode);
        
        // Quit the program as something went
        // wrong
        quit(EXIT_FAILURE, "An unknown error has occured! Please try  again later");
    }
}
