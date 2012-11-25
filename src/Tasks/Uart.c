/*!
    \addtogroup tasks Tasks
    \{
    \addtogroup uart UART Task Module
    \{

    \file Uart.c
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

#include "Uart.h"
#include "Common.h"

#define UART_TASKDELAY msToTicks(10000)
#define UART_TASKPRIORITY tskIDLE_PRIORITY
#define UART_STACKSIZE configMINIMAL_STACK_SIZE

#define UART_QUEUESIZE 20

/** Prototype private functions
*/
static void uartTask(void *pvParameters);


/** Variables
*/
USART_InitTypeDef uartConfig;

static xTaskHandle uartTaskHandle;
static xQueueHandle uartQueue;

/*! Initializes the UART hardware and interupts, and prepares the task for starting
 */
void uartInit(void)
{
	uartQueue = xQueueCreate(UART_QUEUESIZE, sizeof(uint32_t));

    uartConfig.USART_BaudRate = 115200;
    uartConfig.USART_WordLength = USART_WordLength_8b;
    uartConfig.USART_StopBits = USART_StopBits_1;
    uartConfig.USART_Parity = USART_Parity_No;
    uartConfig.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    uartConfig.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

    STM_EVAL_COMInit(COM1, &uartConfig);
}

/*! Starts the UART handler task
 */
void uartStart(void)
{
    xTaskCreate(uartTask, (signed char*)"uart", UART_STACKSIZE, NULL, UART_TASKPRIORITY, &uartTaskHandle);
}

/*! Is the UART handler task
 */
static void uartTask(void *pvParameters)
{
    // Initialize task
    uint8_t ch;

    // Task loop
    for(;;) {

        if(xQueueReceive(uartQueue, &ch, UART_TASKDELAY) == pdTRUE) {
            USART_SendData(EVAL_COM1, ch);
        }

    }
}

/*! Register the init and start functions to be run at application initialization time
 */
TASKCB(TASKCB_INITTASKS+1,  uartInit)
TASKCB(TASKCB_STARTTASKS+1, uartStart)

//! \}
//! \}
