#include "MyTask.h"
#include "Common.h"

#define MYTASK_TASKDELAY msToTicks(1000)
#define MYTASK_TASKPRIORITY tskIDLE_PRIORITY+1
#define MYTASK_STACKSIZE configMINIMAL_STACK_SIZE

/** Prototype private functions
*/
static void mytaskTask(void *pvParameters);


/** Variables
*/
static xTaskHandle mytaskTaskHandle;

void mytaskInit(void)
{
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
