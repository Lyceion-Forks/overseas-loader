//
//  security.cpp
//  overseas
//
//  Copyright © 2018 levaa. All rights reserved.
//  By using/viewing this software you agree to our MIT license.
//

#include "security.h"
#include "utils.h"

bool shouldExit = false;

void CSecurity::securityThread()
{
    while(!shouldExit)
    {
        if(CSecurity::isBeingDebugged())
           shouldExit = true;
        
        if(CSecurity::fiddlerIsActive())
            shouldExit = true;
        
        sleep(2);
    }
    
    exit(EXIT_FAILURE);
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
    if(CUtils::isProcessActive("Fiddler"))
        return true;
    
    return false;
}

