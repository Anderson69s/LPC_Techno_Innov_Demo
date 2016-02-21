/****************************************************************************
 *   apps/i2c_temp/main.c
 *
 * TMP101 I2C temperature sensor example
 *
 * Copyright 2013-2014 Nathael Pajani <nathael.pajani@ed3l.fr>
 *
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 *************************************************************************** */


#include <stdint.h>
#include "core/lpc_regs_12xx.h"
#include "core/lpc_core_cm0.h"
#include "core/pio.h"
#include "core/system.h"
#include "core/systick.h"
#include "lib/stdio.h"
#include "drivers/i2c.h"
#include "drivers/serial.h"
#include "drivers/gpio.h"
#include "extdrv/status_led.h"
#include "extdrv/tmp101_temp_sensor.h"


#define MODULE_VERSION    0x04
#define MODULE_NAME "GPIO Demo Module"


#define SELECTED_FREQ  FREQ_SEL_48MHz

/***************************************************************************** */
/* Pins configuration */
/* pins blocks are passed to set_pins() for pins configuration.
 * Unused pin blocks can be removed safely with the corresponding set_pins() call
 * All pins blocks may be safelly merged in a single block for single set_pins() call..
 */
const struct pio_config common_pins[] = {
	/* UART 0 */
	{ LPC_UART0_RX_PIO_0_1,  LPC_IO_DIGITAL },
	{ LPC_UART0_TX_PIO_0_2,  LPC_IO_DIGITAL },
	/* I2C 0 */
	{ LPC_I2C0_SCL_PIO_0_10, (LPC_IO_DIGITAL | LPC_IO_OPEN_DRAIN_ENABLE) },
	{ LPC_I2C0_SDA_PIO_0_11, (LPC_IO_DIGITAL | LPC_IO_OPEN_DRAIN_ENABLE) },
	ARRAY_LAST_PIO,
};

#define TMP101_ADDR  0x94
struct tmp101_sensor_config tmp101_sensor = {
	.addr = TMP101_ADDR,
	.resolution = TMP_RES_ELEVEN_BITS,
};

const struct pio temp_alert = LPC_GPIO_0_7;

const struct pio status_led_green = LPC_GPIO_1_4;
const struct pio status_led_red = LPC_GPIO_1_5;

/***************************************************************************** */
/* Temperature */
/* The Temperature Alert pin is on GPIO Port 0, pin 7 (PIO0_7) */
/* The I2C Temperature sensor is at address 0x94 */
void WAKEUP_Handler(void)
{
}

void temp_config(uint8_t addr, int uart_num)
{
	int ret = 0;

	/* Temp Alert */
	config_gpio(&temp_alert, LPC_IO_MODE_PULL_UP, GPIO_DIR_IN, 0);
	/* FIXME : add a callback on temp_alert edge */

	/* Temp sensor */
	ret = tmp101_sensor_config(&tmp101_sensor);
	if (ret != 0) {
		serial_write(uart_num, "Temp config error\r\n", 19);
	}
}

void temp_display(uint8_t addr, int uart_num)
{
	uint16_t raw = 0;
	int deci_degrees = 0;
	int len = 0;

	tmp101_sensor_start_conversion(&tmp101_sensor);
	msleep(250); /* Wait for the end of the conversion : 40ms */
	len = tmp101_sensor_read(&tmp101_sensor, &raw, &deci_degrees);
	if (len != 0) {
		serial_write(uart_num, "Temp read error\r\n", 19);
	} else {
		uprintf(uart_num, "Temp read: %d,%d - raw: 0x%04x.\r\n",
				(deci_degrees/10), (deci_degrees%10), raw);
	}
}


/***************************************************************************** */
void system_init()
{
	/* Stop the watchdog */
	startup_watchdog_disable(); /* Do it right now, before it gets a chance to break in */

	/* Note: Brown-Out detection must be powered to operate the ADC. adc_on() will power
	 *  it back on if called after system_init() */
	system_brown_out_detection_config(0);
	system_set_default_power_state();
	clock_config(SELECTED_FREQ);
	set_pins(common_pins);
	gpio_on();
	status_led_config(&status_led_green, &status_led_red);
	/* System tick timer MUST be configured and running in order to use the sleeping
	 * functions */
	systick_timer_on(1); /* 1ms */
	systick_start();
}

/* Define our fault handler. This one is not mandatory, the dummy fault handler
 * will be used when it's not overridden here.
 * Note : The default one does a simple infinite loop. If the watchdog is deactivated
 * the system will hang.
 */
void fault_info(const char* name, uint32_t len)
{
	serial_write(1, name, len);
	/* Wait for end of Tx */
	serial_flush(1);
	/* FIXME : Perform soft reset of the micro-controller ! */
	while (1);
}



/***************************************************************************** */
int main(void) {
	system_init();
	uart_on(0, 115200, NULL);

	i2c_on(I2C_CLK_100KHz);

	/* Configure onboard temp sensor */
	temp_config(TMP101_ADDR, 0);

	while (1) {
		chenillard(250);
		temp_display(TMP101_ADDR, 0);
	}
	return 0;
}
