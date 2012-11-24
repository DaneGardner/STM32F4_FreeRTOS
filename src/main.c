#include "Common.h"

#include "TaskAbstraction.h"
#include "System.h"


static void init_task(void *pvParameters);


int main(void)
{
    // FreeRTOS assumes 4 preemption- and 0 subpriority-bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    // Start the initialization task
    xTaskCreate(init_task, (signed char*)"init", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY, NULL);

    // Create init task and start the scheduler
    vTaskStartScheduler();
}

static void init_task(void *pvParameters)
{
    //TODO: Initialize hardware

    // Initialize and start all tasks
    TASK_INITIALISE_ALL
    TASK_START_ALL

    // Delete this task (it's done)
	vTaskDelete(NULL);
}
