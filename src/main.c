/*!
    \addtogroup core Core
    \{
    \addtogroup main Main Module
    \{

    \file main.c
    \author Dane Gardner <dane.gardner@gmail.com>
    \version 0.1.0
    \brief This file contains the main entry point for the application.

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

#include "Common.h"

#define INIT_TASKPRIORITY (configMAX_PRIORITIES - 1)
#define INIT_STACKSIZE (configMINIMAL_STACK_SIZE * 2)

static void init_task(void *pvParameters);

/*! Application entry point. Starts the init script and scheduler for the RTOS.
 */
int main(void)
{
    // FreeRTOS assumes 4 preemption- and 0 subpriority-bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    // Start the initialization task
    xTaskCreate(init_task, (signed char*)"init", INIT_STACKSIZE, NULL, INIT_TASKPRIORITY, NULL);

    // Create init task and start the scheduler
    vTaskStartScheduler();

    //TODO: Should never reach this code.  Blink an error LED or something to let user know something is amiss.
}

/*! Initialization task runs in it's own high-priority thread. Responsible for initializing the hardware, running 
    each registered callback function by priority, which basically starts all other threads in the application.
 */
static void init_task(void *pvParameters)
{
    //TODO: Initialize hardware

    //! \note This can be ranged for better control later. See also taskCallbackAll_ranged()
    taskCallbackAll();

    // Delete this task (it's done)
	vTaskDelete(NULL);
}

//! \}
//! \}
