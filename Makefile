#
#       !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!
#
##############################################################################################
#
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#

##############################################################################################
# Start of default section
#

TRGT = arm-none-eabi-
CC   = $(TRGT)gcc
CP   = $(TRGT)objcopy
AS   = $(TRGT)gcc -x assembler-with-cpp
BIN  = $(CP) -O ihex

MCU  = cortex-m4

# List all default C defines here, like -D_DEBUG=1
DDEFS = -std=gnu99

# List all default ASM defines here, like -D_DEBUG=1
DADEFS =

# List all default directories to look for include files here
DINCDIR =

# List the default directory to look for the libraries here
DLIBDIR =

# List all default libraries here
DLIBS =

#
# End of default section
##############################################################################################

##############################################################################################
# Start of user section
#

#
# Define project name and Ram/Flash mode here
PROJECT  = STM32F4_FreeRTOS
RUN_FROM_FLASH = 1
USE_HARD_FPU   = 1

#
# Define linker script file here
#
ifeq ($(RUN_FROM_FLASH), 0)
LDSCRIPT = STM32F4xx/LD_Scripts/stm32f4xx_ram.ld
FULL_PRJ = $(PROJECT)_ram
else
LDSCRIPT = STM32F4xx/LD_Scripts/stm32f4xxxg_flash.ld
FULL_PRJ = $(PROJECT)_rom
endif

#
# Define FPU settings here
#
ifeq ($(USE_HARD_FPU), 0)
FPU = -mfloat-abi=soft -mfpu=fpv4-sp-d16
else
FPU = -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__FPU_USED=1
endif


# List all user C define here, like -D_DEBUG=1
UDEFS = -DUSE_STDPERIPH_DRIVER

# Define ASM defines here
UADEFS =

# List C source files here
SRC += src/uart.c
SRC += src/main.c
SRC += src/syscalls.c
SRC += src/CMSIS/system_stm32f4xx.c
SRC += src/CMSIS/stm32f4xx_it.c
SRC += src/FreeRTOS/ustime.c

SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/misc.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_adc.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_can.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_crc.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_aes.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_des.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_cryp_tdes.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dac.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dbgmcu.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dcmi.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_dma.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_exti.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_flash.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_fsmc.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_gpio.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_md5.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_hash_sha1.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_i2c.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_iwdg.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_pwr.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rcc.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rng.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_rtc.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_sdio.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_spi.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_syscfg.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_tim.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_usart.c
SRC += STM32F4xx/STM32F4xx_StdPeriph_Driver/src/stm32f4xx_wwdg.c

SRC += FreeRTOS/Source/tasks.c
SRC += FreeRTOS/Source/queue.c
SRC += FreeRTOS/Source/list.c
SRC += FreeRTOS/Source/croutine.c
SRC += FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c

# List ASM source files here
ASRC = src/CMSIS/startup_stm32f4xx.s

# List all user directories here
UINCDIR += src
UINCDIR += src/CMSIS
UINCDIR += src/FreeRTOS
UINCDIR += STM32F4xx/CMSIS/Include
UINCDIR += STM32F4xx/CMSIS/Device/ST/STM32F4xx/Include
UINCDIR += STM32F4xx/STM32F4xx_StdPeriph_Driver/inc
UINCDIR += FreeRTOS/Source/include

# List the user directory to look for the libraries here
ULIBDIR =

# List all user libraries here
ULIBS =

# Define optimisation level here
OPT = -O0
#OPT = -O2 -falign-functions=16 -fno-inline -fomit-frame-pointer
#OPT = -Os

#
# End of user defines
##############################################################################################


INCDIR  = $(patsubst %,-I%,$(DINCDIR) $(UINCDIR))
LIBDIR  = $(patsubst %,-L%,$(DLIBDIR) $(ULIBDIR))

ifeq ($(RUN_FROM_FLASH), 0)
DEFS    = $(DDEFS) $(UDEFS) -DRUN_FROM_FLASH=0 -DVECT_TAB_SRAM
else
DEFS    = $(DDEFS) $(UDEFS) -DRUN_FROM_FLASH=1
endif

ADEFS   = $(DADEFS) $(UADEFS)
OBJS    = $(ASRC:.s=.o) $(SRC:.c=.o)
LIBS    = $(DLIBS) $(ULIBS)
MCFLAGS = -mthumb -mcpu=$(MCU)

ASFLAGS = $(MCFLAGS) -g -gdwarf-2 -Wa,-amhls=$(<:.s=.lst) $(ADEFS)
CPFLAGS = $(MCFLAGS) $(OPT) $(FPU) -gdwarf-2 -Wall -Wstrict-prototypes -fverbose-asm -Wa,-ahlms=$(<:.c=.lst) $(DEFS)
LDFLAGS = $(MCFLAGS) -mthumb -nostartfiles -T$(LDSCRIPT) -Wl,-Map=$(FULL_PRJ).map,--cref,--no-warn-mismatch $(LIBDIR)

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d

#
# makefile rules
#

all: $(OBJS) $(FULL_PRJ).elf $(FULL_PRJ).hex


%.o : %.c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

%.o : %.s
	$(AS) -c $(ASFLAGS) $< -o $@

%elf: $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $@

%hex: %elf
	$(BIN) $< $@

clean:
	-rm -f $(OBJS)
	-rm -f $(FULL_PRJ).elf
	-rm -f $(FULL_PRJ).map
	-rm -f $(FULL_PRJ).hex
	-rm -f $(SRC:.c=.c.bak)
	-rm -f $(SRC:.c=.lst)
	-rm -f $(ASRC:.s=.s.bak)
	-rm -f $(ASRC:.s=.lst)
	-rm -fR .dep

#
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***