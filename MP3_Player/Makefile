PROJECT = awesomesauce
BUILD_DIR = bin

SHARED_DIR = ../my-common-code
FREERTOS_INCLUDE_DIR = ../FreeRTOS/include
FREERTOS_CONFIG_DIR = ../FreeRTOS/config
CFILES = main.c
CFILES += ../FreeRTOS/list.c
CFILES += ../FreeRTOS/queue.c
CFILES += ../FreeRTOS/tasks.c
CFILES += ../FreeRTOS/portable/GCC/ARM_CM7/r0p1/port.c
CFILES += ../FreeRTOS/portable/MemMang/heap_1.c

# TODO - you will need to edit these two lines!
DEVICE=stm32f746ngh6
OOCD_FILE = board/stm32f7discovery.cfg

# You shouldn't have to edit anything below here.
VPATH += $(SHARED_DIR)
INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
VPATH += $(FREERTOS_INCLUDE_DIR)
INCLUDES += $(patsubst %,-I%, . $(FREERTOS_INCLUDE_DIR))
VPATH += $(FREERTOS_CONFIG_DIR)
INCLUDES += $(patsubst %,-I%, . $FREERTOS_CONFIG_DIR)
OPENCM3_DIR=../libopencm3

include $(OPENCM3_DIR)/mk/genlink-config.mk
include ../rules.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
