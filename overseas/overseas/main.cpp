//
//  main.cpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "includes.h"
#include "security.h"
#include "text.h"
#include "login.h"
#include "utils.h"

int main(int argc, const char * argv[])
{
    // Create threads
    std::thread securityThread(CSecurity::securityThread);
    
    CText* text;
    CLogin* login;
    CUtils* utils;
    
    
    // Print text and ask inputs
    text->printASCII();
    text->askInputs();

    text->divider();
    
    text->print("Checking data...");
    login->checkData();
    
    sleep(1);
    
    if(login->data.correct.inputs && (login->data.correct.hwid || login->data.correct.hwidSet))
    {
        text->print("Successful login!");
        
        if(login->data.correct.hwidSet)
        {
            text->print("We see this is your first login! Welcome to our cheat. Your HWID has been set.");
        }
        
        text->divider();
        
        text->print("Your session expires in two minutes.");
        text->print("Session token: " + login->data.token);
        
        text->divider();
        
        text->print("Checking for CSGO...");
        
        sleep(1);
        
        if(utils->isProcessActive("csgo_osx64"))
        {
            text->print("CSGO found. Proceeding...");
            
            text->divider();
            
            
            login->downloadFile("https://domain.com/moonlight/loader/download.php?username=" + CLogin::Data::username +
                                "&token=" + CLogin::Data::token, "f.zip");
            
            login->inject("libBarbossa.dylib");
            
            sleep(1);
            
            text->print("Successfully injected. Thank you for using our cheat.", 1);
            
            text->divider();
            
            exit(EXIT_SUCCESS);

        }
        else
        {
            sleep(1);
            
            text->print("Could not find CSGO. Please open it before running.", 1);
            
            text->divider();
            
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if(login->data.error == "inchwid")
        {
            text->print("Incorrect HWID.");
        }
        else if(login->data.error == "incuop")
        {
            text->print("Incorrect username or password.");
        }
    }
    
}
