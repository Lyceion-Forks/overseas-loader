//
//  login.cpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "login.h"
#include "utils.h"
#include <curl/curl.h>

std::string tempHwid = CUtils::exec("ioreg -rd1 -c IOPlatformExpertDevice | awk '/IOPlatformUUID/ { split($0, line, \"\\\"\"); printf(\"\\n%s\\n\\n\", line[4]); }'", false);

std::string CLogin::Data::username = "";
std::string CLogin::Data::password = "";
std::string CLogin::Data::hwid = tempHwid.substr(1, tempHwid.length() - 3);
std::string CLogin::Data::token = "";
std::string CLogin::Data::error = "";

bool CLogin::Data::Correct::hwid = false;
bool CLogin::Data::Correct::hwidSet = false;
bool CLogin::Data::Correct::inputs = false;

void CLogin::checkData()
{

    std::string toCheck = CLogin::sendRequest("https://domain.com/moonlight/loader/checks.php",
                                "username=" + CLogin::Data::username +
                                "&password=" + CLogin::Data::password +
                                "&hwid=" + CLogin::Data::hwid);
    
    if(toCheck == "2oia92n" || toCheck == "kja8y2na1")
    {
        // user doesnt exist
        CLogin::Data::error = "incuop";
    }
    else if(toCheck == "92i1msu71h")
    {
        // incorrect hwid
        CLogin::Data::error = "inchwid";
    }
    else
    {
        // Inputs are correct, check hwid
        
        CLogin::Data::Correct::inputs = true;
        
        CUtils* utils;
        
        std::vector<std::string> explodedData = utils->explode(toCheck, ':');
        
        toCheck = explodedData[0];
        CLogin::Data::token = explodedData[1];
        
        if(toCheck == "iakh817b1")
        {
            // first login + set hwid
            CLogin::Data::Correct::hwidSet = true;
        }
        else if(toCheck == "sij28nak")
        {
            // correct hwid
            CLogin::Data::Correct::hwid = true;
        }
    }
}


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

std::string CLogin::sendRequest(std::string url, std::string data)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;
    std::string fullRequest = url + "?" + data;
    
    curl = curl_easy_init();
    
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, fullRequest.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    
    return readBuffer;
}

void CLogin::downloadFile(std::string url, std::string name)
{
    std::string cmd = "mkdir ~/Applications/askdjaj2o/";
    CUtils::exec(cmd.c_str(), false);
    
    cmd = "chflags hidden ~/Applications/askdjaj2o/";
    CUtils::exec(cmd.c_str(), false);
    
    cmd = "cd ~/Applications/askdjaj2o/ && curl --silent -L -o '" + name + "' '" + url+ "'";
    CUtils::exec(cmd.c_str(), false);
    
    cmd = "cd ~/Applications/askdjaj2o/ && unzip f.zip";
    CUtils::exec(cmd.c_str(), false);
    
    cmd = "cd ~/Applications/askdjaj2o/ && chmod +x osxinj";
    CUtils::exec(cmd.c_str(), false);
    
    cmd = "rm -r ~/Applications/askdjaj2o/";
    CUtils::exec(cmd.c_str(), false);
}

void CLogin::inject(std::string dylibName)
{
    std::string cmd = "cd ~/Applications/askdjaj2o/ && sudo ./osxinj csgo_osx64 "
                        + dylibName;
    
    CUtils::exec(cmd.c_str(), false);
}

