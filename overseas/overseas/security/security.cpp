//
//  security.cpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "includes.h"
#include "security.h"
#include "util.h"

void CSecurity::securityThread()
{
    // Continues to loop while the program
    // runs to check if it's being debugged
    // or web debugged
    
    while(true)
    {
        if(CSecurity::isBeingDebugged())
            quit(EXIT_FAILURE, "Debugger attached");
        
        if(CSecurity::fiddlerIsActive())
            quit(EXIT_FAILURE, "Fiddler is active");
        
        sleep(2);
    }
}

bool CSecurity::isBeingDebugged()
{
    mach_msg_type_number_t count = 0;
    exception_mask_t masks[EXC_TYPES_COUNT];
    mach_port_t ports[EXC_TYPES_COUNT];
    exception_behavior_t behaviors[EXC_TYPES_COUNT];
    thread_state_flavor_t flavors[EXC_TYPES_COUNT];
    
    exception_mask_t mask = EXC_MASK_ALL & ~(EXC_MASK_RESOURCE | EXC_MASK_GUARD);
    kern_return_t result = task_get_exception_ports(mach_task_self(), mask, masks, &count, ports, behaviors, flavors);
    if (result == KERN_SUCCESS)
    {
        for (mach_msg_type_number_t portIndex = 0; portIndex < count; portIndex++)
        {
            if (MACH_PORT_VALID(ports[portIndex]))
            {
                return true;
            }
        }
    }
    return false;
}

bool CSecurity::fiddlerIsActive()
{
    return Util::doesProcessExist("Fiddler");
}

