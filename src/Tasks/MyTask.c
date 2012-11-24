#include "MyTask.h"
#include "Common.h"

#define MYTASK_TASKDELAY msToTicks(10000)
#define MYTASK_TASKPRIORITY tskIDLE_PRIORITY
#define MYTASK_STACKSIZE configMINIMAL_STACK_SIZE

#define MYTASK_QUEUESIZE 20

/** Prototype private functions
*/
static void mytaskTask(void *pvParameters);


/** Variables
*/
static xTaskHandle mytaskTaskHandle;
static xQueueHandle mytaskQueue;


void mytaskInit(void)
{
	mytaskQueue = xQueueCreate(MYTASK_QUEUESIZE, sizeof(uint32_t));

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

TASKCB(TASKCB_INITTASKS+5,  mytaskInit)
TASKCB(TASKCB_STARTTASKS+5, mytaskStart)
