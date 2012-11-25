/*!
    \addtogroup core Core
    \{
    \addtogroup common Common Module
    \{

    \file Common.h
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

#ifndef COMMON_H_
#define COMMON_H_

//! Converts milliseconds to FreeRTOS ticks
#define msToTicks(x) (x/portTICK_RATE_MS)
//! Delays for milliseconds instead of FreeRTOS ticks
#define vTaskDelayMS(x) vTaskDelay(msToTicks(x))
//! Delays for milliseconds instead of FreeRTOS ticks
#define vTaskDelayUntilMS(x,y) vTaskDelayUntil(x,msToTicks(y))


#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <math.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/time.h>

#include <stm32f4xx.h>

#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include "TaskAbstraction.h"


#endif

//! \}
//! \}
