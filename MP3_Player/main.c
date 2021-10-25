#include "main.h"

// Include files for libopencm3
#include "../libopencm3/include/libopencm3/cm3/systick.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"

// Include files for FreeRTOS
#include "../FreeRTOS/include/FreeRTOS.h"
#include "../FreeRTOS/include/task.h"


void blink(void * parameters)
{
	configASSERT(parameters == NULL);

	for(;;) {
		gpio_toggle(GPIOI, GPIO1);
		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOI);
	gpio_mode_setup(GPIOI, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
}

int main(void)
{
	gpio_setup();

	const struct rcc_clock_scale clock_config = { 0, 										// plln
																								0, 										// pllp
																								0, 										// pllq
																								1, 										// flash_waitstates
																								RCC_CFGR_HPRE_NODIV, 	// hpre
																								RCC_CFGR_PPRE_NODIV, 	// ppre1
																								RCC_CFGR_PPRE_NODIV, 	// ppre2
																								PWR_SCALE1, 					// vos_scale
																								0, 										// overdrive
																								16000000, 										// ahb_frequency
																								16000000, 										// apb1_frequency
																								16000000  										// apb2_frequency
	};

	rcc_clock_setup_hse(&clock_config, 25000000);

	systick_interrupt_enable();

	configASSERT(pdMS_TO_TICKS(1000) == (TickType_t) 1000);

	BaseType_t returned;
	TaskHandle_t blink_task = NULL;

	returned = xTaskCreate(blink, 																					// pxTaskCode
												(const char *const) NULL, 												// pcName
												(const uint16_t) configMINIMAL_STACK_SIZE,  			// usStackDepth
												(void *const) NULL, 															// pvParameters
												6,                                                // uxPriority
												&blink_task); 																		// pxCreatedTask

	configASSERT(returned != errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY);

	vTaskStartScheduler();

	for(;;);
}
