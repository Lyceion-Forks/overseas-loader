/*
 *  util.h
 */
#pragma once

namespace Util
{
    void checkCSGO();
    
    bool doesFileExist(const std::string& file);
    bool doesProcessExist(std::string proc);
    
    std::string execute(const char* cmd, bool remove = false);
    std::vector<std::string> explode(const std::string& str, char split);
}

void quit(int code, std::string reason = "");

inline void systemCMD(const char* cmd)
{
    pclose(popen(cmd, "w"));
}
