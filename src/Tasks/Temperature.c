/*!
    \addtogroup tasks Tasks
    \{
    \addtogroup temperature Temperature Task Module
    \{

    \file Temperature.c
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


#include "Temperature.h"
#include "Common.h"

#define TEMPERATURE_TASKDELAY msToTicks(1000)
#define TEMPERATURE_TASKPRIORITY tskIDLE_PRIORITY
#define TEMPERATURE_STACKSIZE configMINIMAL_STACK_SIZE


/* Structs
*/
struct temperatureData {
    uint32_t id;
    uint32_t value;
    float temperature;
};
struct temperatureDevice {
    uint32_t id;
};


static void temperatureTask(void *pvParameters);

static xTaskHandle temperatureTaskHandle;


void temperatureInit(void)
{
    //TODO: Task should read only one sensor, multiple sensors mean multiple tasks
    //TODO: Initialize for specific termperature sensor
}

void temperatureStart(void)
{
    xTaskCreate(temperatureTask, (signed char*)"temperature", TEMPERATURE_STACKSIZE, NULL, TEMPERATURE_TASKPRIORITY, &temperatureTaskHandle);
}

static void temperatureTask(void *pvParameters)
{
    // Initialize task

    // Task loop
    for(;;) {
        vTaskDelay(TEMPERATURE_TASKDELAY);

        //TODO: Read temperature; send to readings queue

    }
}

TASKCB(TASKCB_INITTASKS+1,  temperatureInit)
TASKCB(TASKCB_STARTTASKS+1, temperatureStart)

//! \}
//! \}
