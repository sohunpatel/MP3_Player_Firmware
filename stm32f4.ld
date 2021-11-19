
/* Linker script for ST STM32F4DISCOVERY (STM32F407VG, 1024K flash, 128K RAM). */

/* Define memory regions. */
MEMORY
{
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
	ram (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
}

/* Include the common ld script. */
INCLUDE /home/sohun/Projects/MP3-Player/Firmware/libopencm3/lib/cortex-m-generic.ld