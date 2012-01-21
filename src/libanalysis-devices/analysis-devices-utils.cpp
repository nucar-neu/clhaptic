#include <stdio.h>
#include <CL/cl.h>
#include "analysis-devices-utils.h"
#include "eventtypes.h"
#include <cmath>
#include <iostream>
#include <ctime>






//-------------------------------------------------------
//          Synchronization functions
//-------------------------------------------------------

/*!
    Wait till all pending commands in queue are finished
*/
void ad_sync(cl_command_queue commandQueue)
{
    clFinish(commandQueue);
}

