/****************************************************************************
 *   core/systick.h
 *
 * System tick timer control
 *
 * Copyright 2012 Nathael Pajani <nathael.pajani@ed3l.fr>
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

#ifndef CORE_SYSTICK_H
#define CORE_SYSTICK_H

#include <stdint.h>

/***************************************************************************** */
/*               System Tick Timer                                             */
/***************************************************************************** */

/* Driver for the internal systick timer of the LPC1224.
 * Refer to the LPC1224 documentation (UM10441.pdf) for more information
 */


/* Start the system tick timer
 * Starting the systick timer also resets the internal tick counters.
 * If you need a value that goes beyond one start/stop cycle and accross resets,
 *    then it's up to you to keep track of this using systick_get_tick_count() and/or
 *    systick_get_clock_cycles().
 */
void systick_start(void);

/* Stop the system tick timer */
void systick_stop(void);

/* Reset the system tick timer, making it count down from the reload value again
 * Reseting the systick timer also resets the internal tick counters.
 * If you need a value that goes beyond one start/stop cycle and accross resets,
 *    then it's up to you to keep track of this using systick_get_tick_count() and/or
 *    systick_get_clock_cycles().
 */
void systick_reset(void);

/* Get system tick timer current value (counts at get_main_clock() !)
 * systick_get_timer_val returns a value between 0 and systick_get_timer_reload_val()
 */
uint32_t systick_get_timer_val(void);

/* Get system tick timer reload value */
uint32_t systick_get_timer_reload_val(void);

/* Check if systick is running (return 1) or not (return 0) */
uint32_t is_systick_running(void);

/* Get the system tick period in ms
 * A vaue of 0 means the system tick timer has not been configured.
 * Note : calls to msleep() or usleep() will configure the system tick timer
 *        with a value of 1ms if it was not configured yet.
 */
uint32_t systick_get_tick_ms_period(void);

/* Get the number of system ticks ... since last wrapping of the counter, which
 * is about 50 days with a 1ms system tick. */
uint32_t systick_get_tick_count(void);

/* Get the number of clock cycles ... since last wrapping of the counter. */
uint32_t systick_get_clock_cycles(void);

/* Power up the system tick timer.
 * ms is the interval between system tick timer interrupts. If set to 0, the default
 *     value is used, which should provide a 1ms period.
 */
void systick_timer_on(uint32_t ms);

/* Removes the main clock from the selected timer block */
void systick_timer_off(void);

/* Register a callback to be called every 'period' system ticks.
 * returns the callback number if registration was OK.
 * returns negative value on error.
 * The callback will get the "global_wrapping_system_ticks" as argument, which wraps every 50 days
 *   or so with a 1ms tick
 */
#define MAX_SYSTICK_CALLBACKS  4
int add_systick_callback(void (*callback) (uint32_t), uint16_t period);
/* Remove a registered callback, given the callback address used to register it. */
int remove_systick_callback(void (*callback) (uint32_t));



/* This function can be used when you are absolutly certain that systick timer is running, and when
 * you need to sleep less than 1000us (1ms)
 */
void usleep_short(uint32_t us);


#endif /* CORE_SYSTICK_H */
