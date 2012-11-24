#include "Common.h"

#include "System.h"


int main(void)
{
    // FreeRTOS assumes 4 preemption- and 0 subpriority-bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);


    // Initialize tasks
    systemInit();


    // Start tasks
    systemStart();


    // Create init task and start the scheduler
    vTaskStartScheduler();
}

