STM32F4-Discovery FreeRTOS
==========================

Code pilfered from Thomas Kindler's FreeRTOS demo <https://github.com/thomask77/STM32F4_demo>.

I've abstracted out the CMSIS and Standard Peripheral Driver libraries, as well as the FreeRTOS project, in order to make it easier to keep it updated.  I've also converted the build system to work with the Yagarto tool chain.


Compiling
---------

The project is known to work with Yagarto [13.10.2012].

  $ ./bootstrap.sh    # To pull the submodules from GitHub
  $ make all


Running
-------

At the moment, there's just a bunch of tasks incrementing floating point variables. USART1 is running at 115200 baud 8N1 on PB6 (TXD) and PB7 (RXD). Use a TTL-Level RS232-cable.  Works great with a BusPirate!
