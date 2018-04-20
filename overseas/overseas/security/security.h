//
//  security.h
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "includes.h"

class CSecurity
{
public:
    static void securityThread();
    
    static bool isBeingDebugged();
    static bool fiddlerIsActive();

};



