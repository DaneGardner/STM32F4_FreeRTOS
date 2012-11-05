#include "stm32f4xx_it.h"
#include <stm32f4xx.h>

uint16_t capture = 0;
extern __IO uint16_t CCR1_Val;
extern __IO uint16_t CCR2_Val;
extern __IO uint16_t CCR3_Val;
extern __IO uint16_t CCR4_Val;


/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

void NMI_Handler(void)
{
  // This function handles NMI exception.
}

void HardFault_Handler(void)
{
  // Go to infinite loop when Hard Fault exception occurs
  while (1);
}

void MemManage_Handler(void)
{
  // Go to infinite loop when Memory Manage exception occurs
  while (1);
}

void BusFault_Handler(void)
{
  // Go to infinite loop when Bus Fault exception occurs
  while (1);
}

void UsageFault_Handler(void)
{
  // Go to infinite loop when Usage Fault exception occurs 
  while (1);
}

void DebugMon_Handler(void)
{
  // This function handles Debug Monitor exception.
}
