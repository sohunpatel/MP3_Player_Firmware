#include "../libopencm3/include/libopencm3/stm32/gpio.h"
#include "../libopencm3/include/libopencm3/stm32/rcc.h"

static void gpio_setup(void)
{
	rcc_periph_clock_enable(RCC_GPIOI);
	gpio_mode_setup(GPIOI, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, GPIO1);
}

int main(void) {
	int i;
	gpio_setup();
	while (1) {
		gpio_toggle(GPIOI, GPIO1);
		for (i = 0; i < 10000000; i++) {
			__asm__("nop");
		}
	}
	return 0;
}
