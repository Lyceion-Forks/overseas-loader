/*      overseas loader
 *
 *  Orginally coded by levaa    @ https://github.com/gLevaa
 *  Improved by pwned           @ https://github.com/pwnedboi
 *
 */

#include "includes.h"

#include "text.h"
#include "util.h"
#include "login.h"
#include "inject.h"
#include "security.h"
#include "util_connect.h"

int main(int argc, const char * argv[])
{

    // Make sure the loader was run as root
    if(geteuid() > 0)
    {
        Text::print("Please run as root");
        Text::print(std::string("sudo ./" ) + __progname);
        quit(EXIT_FAILURE);
    }
    
    // Create threads
    std::thread securityThread(CSecurity::securityThread);
    
    // Print ASCII art
    Text::printLogo();
    
    // Get the users info then check it on the server
    Login::getUserAndPass();
    Text::divider();
    Login::checkData();
    
    sleep(1);
    
    // Display session token and info to the user
    Text::divider();
    Text::print("Your session expires in two minutes.");
    Text::print("Session token: " + Login::token);
    
    Text::divider();
    Text::print("Checking for CSGO...");
    
    sleep(1);
    
    // Check if CS:GO is running, if not then exit
    Util::checkCSGO();
    
    // Inject the dylib into CS:GO
    Inject::inject("libBarbossa.dylib");
    
    // Display to user all went well
    Text::divider();
    Text::print("Successfully injected. Thank you for using our cheat");
    Text::divider();
        
    quit(EXIT_SUCCESS);
}
