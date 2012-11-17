#include "uart.h"

#include <stm32f4xx.h>

#include <FreeRTOS.h>
#include <task.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define vTaskDelayMS(x) vTaskDelay((x/portTICK_RATE_MS))
#define vTaskDelayUntilMS(x,y) vTaskDelayUntil(x,(y/portTICK_RATE_MS))


struct task_param {
    char *name;
    int   interval;
};

static void fpu_task(void *pvParameters)
{
    struct task_param *p = pvParameters;

    for(;;) {
        vTaskDelayMS(p->interval);
    }
}

static void init_task(void *pvParameters)
{
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    GPIO_Init(GPIOD, &(GPIO_InitTypeDef) {
        .GPIO_Pin   = 0xF000,
        .GPIO_Mode  = GPIO_Mode_OUT,
        .GPIO_OType = GPIO_OType_PP,
        .GPIO_PuPd  = GPIO_PuPd_NOPULL,
        .GPIO_Speed = GPIO_Speed_50MHz,
    });

    uart_init(115200);
    printf("\n\n\nSTM32F407 FreeRTOS Test\n");

    vTaskDelayMS(10);

    xTaskHandle tasks[5];

    for (int i=0; i<5; i++) {
        printf("Starting FPU task %d...\n", i);

        vTaskDelayMS(10);

        struct task_param *p;
        p = malloc(sizeof(struct task_param));
        p->name = malloc(configMAX_TASK_NAME_LEN);
        p->interval = 1000;
        sprintf(p->name, "FPU_%d", i);

        xTaskCreate(fpu_task, (int8_t*)p->name, configMINIMAL_STACK_SIZE * 2, p, tskIDLE_PRIORITY, &(tasks[i]));
    }

    for(;;) {
        vTaskDelayMS(1000);

        printf("INIT: stack = %lu\n", uxTaskGetStackHighWaterMark(NULL));

        for(int j=0; j<5; j++) {
            printf("ID_%d: stack = %d\n", j, uxTaskGetStackHighWaterMark(tasks[j]));
        }
    }
}


int main(void)
{
    // FreeRTOS assumes 4 preemption- and 0 subpriority-bits
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    // Create init task and start the scheduler
    xTaskCreate(init_task, (signed char*)"init", configMINIMAL_STACK_SIZE * 2, NULL, tskIDLE_PRIORITY, NULL);
    vTaskStartScheduler();
}


#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t* file, uint32_t line)
{
  printf("assert_failed(%s, %ld);\n", file, line);
  while(1);
}
#endif

#if (configCHECK_FOR_STACK_OVERFLOW != 0)
void vApplicationStackOverflowHook(xTaskHandle *pxTask, signed char *pcTaskName)
{
    printf("\nOVERFLOW ERROR: %s\n", pcTaskName);
}
#endif
