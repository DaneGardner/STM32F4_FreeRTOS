/*!
    \file TaskAbstraction.h
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

#ifndef TASKABSTRACTION_H_
#define TASKABSTRACTION_H_

#include "Common.h"


#define TASKCB_MAXPRIORITY 256
#define TASKCB_MINPRIORITY 0
#define TASKCB_INITTASKS ((TASKCB_MAXPRIORITY - TASKCB_MINPRIORITY) / 4)
#define TASKCB_STARTTASKS ((TASKCB_MAXPRIORITY - TASKCB_MINPRIORITY) / 2)

typedef void (*functionCB_t)(void);

typedef struct {
    functionCB_t function;
    uint32_t priority;
} taskCB_t;

// Defined in the linker script
extern taskCB_t __taskCB_start__[], __taskCB_end__[];

#define __define_taskCB(pri,func) \
    static taskCB_t __taskCB_##func \
        __attribute__((__used__)) \
        __attribute__((__section__(".taskCB.init"))) = { .function = func, .priority = pri };

/*! \brief Allows functions to be registered to be automatically called when the application initializes
 */
#define TASKCB(pri,func) __define_taskCB(pri,func)

/*! \brief Callback function that compares two function callback structs for qsort.
    \sa taskCallbackAll() taskCallbackAll_ranged()
    \internal
 */
static uint32_t cbcmp(const taskCB_t *left, const taskCB_t *right)
{
    if(left->priority > right->priority) {
        return 1;
    } else if(left->priority < right->priority) {
        return -1;
    }
    return 0;
}

/*! \brief Iterates through a specified range of registered callbacks in order of priority.
    \sa taskCallbackAll()
 */
static inline void taskCallbackAll_ranged(uint32_t min, uint32_t max)
{
    if(!(__taskCB_end__ - __taskCB_start__)) {
        return;
    }

    // Create the local buffer that we can sort
    taskCB_t *taskCBs[__taskCB_end__ - __taskCB_start__];

    // Populate the buffer
    uint32_t index = 0;
    for(taskCB_t *func = __taskCB_start__; func < __taskCB_end__; ++func) {
        taskCBs[index++] = func;
    }

    // Sort the task callbacks by priority
    //HACK: This adds 1.5k to the binary!  There might be a better way to do this.
    qsort(taskCBs, sizeof(taskCBs), sizeof(taskCB_t *), (int(*)(const void*, const void*))cbcmp);

    // Execute the buffer functions in order
    for(index = 0; index < sizeof(taskCBs); ++index) {
        taskCB_t *taskCB = taskCBs[index];
        if(taskCB && taskCB->priority >= min && taskCB->priority <= max) {
            functionCB_t function = taskCB->function;
            if(function) {
                (function)();
            }
        }
    }
}

/*! \brief Iterates through all registered callbacks in order of priority.
    \sa taskCallbackAll_ranged()
 */
static inline void taskCallbackAll(void)
{
    taskCallbackAll_ranged(TASKCB_MINPRIORITY, TASKCB_MAXPRIORITY);
}


#endif // TASKABSTRACTION_H_