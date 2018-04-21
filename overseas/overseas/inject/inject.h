/*
 *  inject.h
 */
#pragma once
#include <iostream>

namespace Inject
{
    extern std::string download_path;
    
    void createDirectories();
    void downloadLibraries();
    void inject(std::string dylib);
    void cleanUp();
}
