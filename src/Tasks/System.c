/*!
    \addtogroup tasks Tasks
    \{
    \addtogroup system System Task Module
    \{

    \file System.c
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

#include "System.h"
#include "Common.h"

#ifndef configUSE_IDLE_HOOK
#error "configUSE_IDLE_HOOK" is not defined.
#endif

#define SYSTEM_TASKDELAY msToTicks(1000)
#define SYSTEM_TASKPRIORITY tskIDLE_PRIORITY+1
#define SYSTEM_STACKSIZE configMINIMAL_STACK_SIZE


/** Prototype private functions
*/
static void systemTask(void *pvParameters);


/** Variables
*/
static xQueueHandle systemQueue;
static xTaskHandle systemTaskHandle;

static uint32_t idleCounter;
static bool stackOverflowed;
static bool mallocFailed;
static bool asserted;


void systemInit(void)
{
    stackOverflowed = false;
    mallocFailed = false;
    asserted = false;
}

void systemStart(void)
{
    xTaskCreate(systemTask, (signed char*)"system", SYSTEM_STACKSIZE, NULL, SYSTEM_TASKPRIORITY, &systemTaskHandle);
}

static void systemTask(void *pvParameters)
{
    // Initialize task

    // Task loop
    for(;;) {

        if(mallocFailed || stackOverflowed || asserted) {
            //TODO: Critical alarm!
            //TODO: System reset!
        }

        if(xQueueReceive(systemQueue, NULL, SYSTEM_TASKDELAY) == pdTRUE) {
        }
    }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
    asserted = true;
}
#endif

#ifdef configUSE_IDLE_HOOK
void vApplicationIdleHook(void)
{
    ++idleCounter;
}
#endif

void vApplicationMallocFailedHook(void)
{
    mallocFailed = true;
}

#if (configCHECK_FOR_STACK_OVERFLOW != 0)
void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
    stackOverflowed = true;
}
#endif

TASKCB(TASKCB_INITTASKS,  systemInit)
TASKCB(TASKCB_STARTTASKS, systemStart)

//! \}
//! \}
