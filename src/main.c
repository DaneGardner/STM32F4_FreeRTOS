#include "Common.h"

#define INIT_TASKPRIORITY (configMAX_PRIORITIES - 1)
#define INIT_STACKSIZE (configMINIMAL_STACK_SIZE * 2)

static void init_task(void *pvParameters);

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

static void init_task(void *pvParameters)
{
    //TODO: Initialize hardware

    taskCallbackAll();

    // Delete this task (it's done)
	vTaskDelete(NULL);
}
