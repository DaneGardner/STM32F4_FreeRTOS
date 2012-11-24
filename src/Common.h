#ifndef COMMON_H_
#define COMMON_H_


#define msToTicks(x) (x/portTICK_RATE_MS)
#define vTaskDelayMS(x) vTaskDelay(msToTicks(x))
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