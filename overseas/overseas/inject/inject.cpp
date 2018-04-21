/*      inject.cpp
 *
 *
 *
 */
#include "includes.h"

#include "inject.h"

#include "util.h"
#include "login.h"
#include "util_connect.h"
#include "text.h"
#include "osxinj/injector.h"

std::string Inject::download_path = "/aksdninej";

void Inject::createDirectories()
{
    // Continue to attempt to create
    // the download path while it doesn't
    // exist.
    while(!Util::doesFileExist(download_path))
    {
        // Create folder with 755 perms,
        // a sort of anti-skid
        mkdir(download_path.c_str(), 755);
        usleep(200);
    }
}

void Inject::downloadLibraries()
{
    // Download the file
    Connect::downloadFile("https://domain.com/moonlight/loader/download.php?username=" +
                          Login::username + "&token=" + Login::token, download_path + "/f.zip");
    
    // Sleep while the file does
    // not exist
    do {
        sleep(1);
    } while (!Util::doesFileExist(download_path + "/f.zip"));
}

void Inject::cleanUp()
{
    // Delete the folder containing everything
    systemCMD(std::string("rm -R " + download_path).c_str());
}

void Inject::inject(std::string dylib)
{
    createDirectories();
    
    downloadLibraries();
    
    // Unzip the f.zip file with silent
    // and overide params
    systemCMD(std::string("unzip -o -q " + download_path + "/f.zip -d " + download_path).c_str());
    
    // Create osxinj object
    Injector inj;
    
    // Inject the dylib into the process
    inj.inject(inj.getProcessByName("csgo_osx64"), std::string(download_path + "/" + dylib).c_str());
    
    cleanUp();
}

