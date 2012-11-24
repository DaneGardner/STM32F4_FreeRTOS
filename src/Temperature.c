#include "Temperature.h"
#include "Common.h"

#define TEMPERATURE_TASKDELAY msToTicks(1000)
#define TEMPERATURE_TASKPRIORITY tskIDLE_PRIORITY
#define TEMPERATURE_STACKSIZE configMINIMAL_STACK_SIZE


/** Structs
*/
struct temperatureData {
    uint32_t id;
    uint32_t value;
    float temperature;
};
struct temperatureDevice {
    uint32_t id;
};


/** Prototype private functions
*/
static void temperatureTask(void *pvParameters);


/** Variables
*/
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

TASK_CALLBACK(temperatureInit,temperatureStart)
