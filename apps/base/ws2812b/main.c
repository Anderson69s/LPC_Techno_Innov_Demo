#include <stdint.h>
#include "core/lpc_regs_12xx.h"
#include "core/lpc_core_cm0.h"
#include "core/pio.h"
#include "core/system.h"
#include "core/systick.h"
#include "lib/stdio.h"
#include "drivers/serial.h"
#include "drivers/gpio.h"
#include "drivers/adc.h"
#include "extdrv/status_led.h"

#include "extdrv/ws2812.h"

#define MODULE_VERSION    0x04
#define MODULE_NAME "GPIO Demo Module"
#define NB_LEDS 8

#define SELECTED_FREQ  FREQ_SEL_48MHz

const struct pio_config common_pins[] = {
	/* UART 0 */
	{ LPC_UART0_RX_PIO_0_1,  LPC_IO_DIGITAL },
	{ LPC_UART0_TX_PIO_0_2,  LPC_IO_DIGITAL },
	/* GPIO */
	{ LPC_GPIO_0_19, (LPC_IO_MODE_PULL_UP | LPC_IO_DIGITAL) },
	ARRAY_LAST_PIO,
};

const struct pio status_led_green = LPC_GPIO_1_4;
const struct pio status_led_red = LPC_GPIO_1_5;

const struct pio button = LPC_GPIO_0_12; /* ISP button */
const struct pio ws2812_data_out_pin = LPC_GPIO_0_19; /* Led control data pin */


/***************************************************************************** */
void system_init()
{
	startup_watchdog_disable(); /* Do it right now, before it gets a chance to break in */
	system_brown_out_detection_config(0);
	system_set_default_power_state();
	clock_config(SELECTED_FREQ);
	set_pins(common_pins);
	gpio_on();
	status_led_config(&status_led_green, &status_led_red);
	systick_timer_on(1); /* 1ms */
	systick_start();
}

void fault_info(const char* name, uint32_t len)
{
	serial_write(1, name, len);
	/* Wait for end of Tx */
	serial_flush(1);
	/* FIXME : Perform soft reset of the micro-controller ! */
	while (1);
}


enum all_modes {	
	red,
	green,
	blue,
	yellow,
	purple,
	cyan,
	white,
	fade_green,
	nothing = 0,
};
static volatile uint8_t new_mode = 0;
void button_request(uint32_t gpio) {
    new_mode++;
}
void mode_red(void)
{
	status_led(none);
	int i = 0;
	uint8_t red = 255, green = 0, blue = 0;
	for (i = 0; i < NB_LEDS; i++) {
		ws2812_set_pixel(i, red, green, blue);
	}
	ws2812_send_frame(0);
}
void mode_green(void)
{
	status_led(none);
	int i = 0;
	uint8_t red = 0, green = 255, blue = 0;
	for (i = 0; i < NB_LEDS; i++) {
		ws2812_set_pixel(i, red, green, blue);
	}
	ws2812_send_frame(0);
}
void mode_blue(void)
{
	status_led(none);	
	int i = 0;
	uint8_t red = 0, green = 0, blue = 255;
	for (i = 0; i < NB_LEDS; i++) {
		ws2812_set_pixel(i, red, green, blue);
	}
	ws2812_send_frame(0);
}
void mode_yellow(void)
{
	status_led(none);
	int i = 0;
	uint8_t red = 255, green = 255, blue = 0;
	for (i = 0; i < NB_LEDS; i++) {
		ws2812_set_pixel(i, red, green, blue);
	}
	ws2812_send_frame(0);
}
void mode_purple(void)
{
	status_led(none);
	int i = 0;
	uint8_t red = 255, green = 0, blue = 255;
	for (i = 0; i < NB_LEDS; i++) {
		ws2812_set_pixel(i, red, green, blue);
	}
	ws2812_send_frame(0);
}
void mode_cyan(void)
{
	status_led(none);
	int i = 0;
	uint8_t red = 0, green = 255, blue = 255;
	for (i = 0; i < NB_LEDS; i++) {
		ws2812_set_pixel(i, red, green, blue);
	}
	ws2812_send_frame(0);
}
void mode_white(void)
{
	status_led(none);
	int i = 0;
	uint8_t red = 255, green = 255, blue = 255;
	for (i = 0; i < NB_LEDS; i++) {
		ws2812_set_pixel(i, red, green, blue);
	}
	ws2812_send_frame(0);
}
void mode_fade_green(void)
{	
	status_led(red_on);
	int i = 0;	
	for(i = 0; i < 255; i++){
		ws2812_set_pixel(NB_LEDS, 0, i, 0);
		}
	msleep(50);		
	ws2812_send_frame(0);
}

void mode_nothing(void)
{
	status_led(red_on);
	msleep(75);
	status_led(red_off);
	msleep(75);
	status_led(green_on);
	msleep(75);
	status_led(green_off);
	msleep(75);
}
/***************************************************************************** */
int main(void)
{

	system_init();
	set_gpio_callback(button_request, &button, EDGE_RISING);
	status_led(none);
	ws2812_config(&ws2812_data_out_pin);
	while (1) {
		switch (new_mode) {
			case red:
				mode_red();
				break;
			case green:
				mode_green();
				break;
			case blue:
				mode_blue();
				break;			
			case yellow:
				mode_yellow();
				break;
			case purple:
				mode_purple();
				break;
			case cyan:
				mode_cyan();
				break;
			case white:
				mode_white();
				break;
			case fade_green:
				mode_fade_green();
				break;
			default :
				ws2812_stop();
				mode_nothing();
				msleep(1);
				new_mode = 0;
		}
	}
	return 0;
}
