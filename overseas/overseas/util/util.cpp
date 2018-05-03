/*
 *
 *
 *
 */

#include "includes.h"
#include "text.h"
#include "util.h"

void quit(int code, std::string reason)
{
#ifdef CAKED
    if(!reason.empty() && code == EXIT_FAILURE)
        Text::print(reason, "error");
#endif
    exit(code);
}

void Util::checkCSGO()
{
    if(!Util::doesProcessExist("csgo_osx64"))
    {
        quit(EXIT_FAILURE, "CS:GO is not running!");
    }
    else
    {
        Text::print("CS:GO has been found. Proceeding.");
        
    }
}

bool Util::doesFileExist(const std::string& file)
{
    std::ifstream f(file.c_str());
    return f.good();
}

bool Util::doesProcessExist(std::string name)
{
    int procCnt = proc_listpids(PROC_ALL_PIDS, 0, NULL, 0);
    pid_t pids[1024];
    memset(pids, 0, sizeof pids);
    proc_listpids(PROC_ALL_PIDS, 0, pids, sizeof(pids));
    
    for (int i = 0; i < procCnt; i++)
    {
        if (!pids[i])
            continue;
        
        char curPath[PROC_PIDPATHINFO_MAXSIZE];
        char curName[PROC_PIDPATHINFO_MAXSIZE];
        
        memset(curPath, 0, sizeof curPath);
        proc_pidpath(pids[i], curPath, sizeof curPath);
        size_t len = strlen(curPath);
        if(len)
        {
            size_t pos = len;
            while (pos && curPath[pos] != '/')
                --pos;
            
            strcpy(curName, curPath + pos + 1);
            if (!strcmp(curName, name.c_str()))
                return pids[i] > 0;
            
        }
    }
    
    return false;
}

std::string Util::execute(const char* cmd, bool remove)
{
    // Execute a shell command and save the output as a string
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe)
    {
        return "error";
    }
    
    while (!feof(pipe.get()))
    {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
        {
            result += buffer.data();
        }
    }
    
    // Remove the last character of the string, only use when the last char
    // is a new line
    if(remove)
        result.pop_back();
    
    return result;
}

std::vector<std::string> Util::explode(const std::string& str, char split)
{
    std::vector<std::string> result;
    std::istringstream iss(str);
    
    // Split a string at the given character
    // like in php
    for (std::string token; getline(iss, token, split); )
        result.push_back(move(token));
    
    return result;
}






