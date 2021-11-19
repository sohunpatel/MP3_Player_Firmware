#include "main.h"

// Include files for libopencm3
#include "../libopencm3/include/libopencm3/cm3/systick.h"
#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"


// Include files for FreeRTOS
#include "../FreeRTOS/include/FreeRTOS.h"
#include "../FreeRTOS/include/task.h"


void blink1(void * parameters)
{
	configASSERT(parameters == NULL);

	for(;;) {
		gpio_toggle(GPIOG, GPIO13);
		vTaskDelay(pdMS_TO_TICKS(290));
	}
}

void blink2(void * parameters)
{
	configASSERT(parameters == NULL);

	for(;;) {
		gpio_toggle(GPIOG, GPIO14);
		vTaskDelay(pdMS_TO_TICKS(933));
	}
}

int main(void)
{
	rcc_clock_setup_pll(&rcc_hse_8mhz_3v3[RCC_CLOCK_3V3_168MHZ]);

	rcc_periph_clock_enable(RCC_GPIOG);
	gpio_mode_setup(GPIOG, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO13 | GPIO14);

	xTaskCreate(blink1,
				(const char *const) "Blink Green",
				(const uint16_t) 100,
				(void *const) NULL,
				0,
				NULL);
	xTaskCreate(blink2,
				(const char *const) "Blink Red",
				(const uint16_t) 100,
				(void *const) NULL,
				0,
				NULL);

	vTaskStartScheduler();

	for(;;);
}
