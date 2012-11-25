/*!
    \addtogroup tasks Tasks
    \{
    \addtogroup examples Example Tasks Module
    \{

    \file MyTask.c
    \author Dane Gardner <dane.gardner@gmail.com>
    \version 0.1.0
    \brief 

    \section LICENSE
    This file is part of the "My Project"<br />
    Copyright (C) 2012 Dane Gardner

    This library is free software; you can redistribute it and/or modify it
    under the terms of the GNU Lesser General Public License as published by the
    Free Software Foundation; either version 2.1 of the License, or (at your
    option) any later version.

    This library is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License
    for more details.
 
    You should have received a copy of the GNU Lesser General Public License
    along with this library; if not, write to the Free Software Foundation,
    Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "MyTask.h"
#include "Common.h"

#define MYTASK_TASKDELAY msToTicks(10000)
#define MYTASK_TASKPRIORITY tskIDLE_PRIORITY
#define MYTASK_STACKSIZE configMINIMAL_STACK_SIZE

#define MYTASK_QUEUESIZE 20

/** Prototype private functions
*/
static void mytaskTask(void *pvParameters);


/** Variables
*/
static xTaskHandle mytaskTaskHandle;
static xQueueHandle mytaskQueue;


void mytaskInit(void)
{
	mytaskQueue = xQueueCreate(MYTASK_QUEUESIZE, sizeof(uint32_t));

}

void mytaskStart(void)
{
    xTaskCreate(mytaskTask, (signed char*)"mytask", MYTASK_STACKSIZE, NULL, MYTASK_TASKPRIORITY, &mytaskTaskHandle);
}

static void mytaskTask(void *pvParameters)
{
    // Initialize task

    // Task loop
    for(;;) {
        vTaskDelay(MYTASK_TASKDELAY);
    }
}

TASKCB(TASKCB_INITTASKS+5,  mytaskInit)
TASKCB(TASKCB_STARTTASKS+5, mytaskStart)

//! \}
//! \}
