# Station Météo V3 by Anderson69s

- I just add an app : thermometre
- Forked from : <http://git.techno-innov.fr/modules>

This repository provides example code for the development modules made by
Techno-Innov.

It has support for the LPC1224 as used on the development modules, and
for the peripherals found on the development modules (user led, eeprom,
temperature sensor, CC1101 RF transceiver, ...).
Support for various other cool stuff is added when we play with it.

Example applications are created in the apps directory, with one
sub-directory for each application. These are (and must stay) independent.

More usefull stuff is up to you. Creating an app is *very* simple. Copy
an example from apps/ to the name you want and start coding.
** Please, no spaces (or special characters) in the directory name ! **


********************
BUID and FLASH

Build has been tested using gcc, and only gcc, in the version provided by
Debian GNU/Linux distribution, and a few other binary versions available for
download on the Internet, but any ARM gcc toolchain should do.

In order to get the debian ARM gcc cross-toolchain you should install the
following packaages : gcc-arm-none-eabi, binutils-arm-none-eabi

There's no need for the related libc package here, the libc does not fit
in our micro-controller memory. Instead have a look at the content of the
lib/ directory, and add stuff there.

Once done you should build using the provided makefile by running the
simple "make" command in the base directory, which will build all apps, or
run "make <app_name>" to build a specific application. You can also run the
simple "make" command in the specific app subdirectory to compile this
application alone.

To flash the binary (the one with .bin) to the LPC Flash you will need the
lpctool package, now packaged for Debian, starting with Jessie, or available
in our git repository : http://git.techno-innov.fr/lpctools (Clone using :
git clone http://gitclone.techno-innov.fr/lpctools and then build (make) and
use :)
Usual command lines :
   lpcprog -d /dev/ttyUSB0 -c id
   lpcprog -d /dev/ttyUSB0 -c flash app_name.bin
See lpctools readme and lpcprog or isp help (-h) or manpages for more
information.


********************
SUPPORTED FEATURES and INTERFACES

- LPC1224 micro-controller definitions
   - Cortex-M0 specific definitions
   - Cortex-M0 and LPC1224 Registers
   - Interrupts
   - ROM based division routines
   - Utility functions to replace ctz and clz instructions (not present in Cortex M0)
   - IAP ROM based functions (tested for user flash access only)

- Bootstrap
   - vector table
   - reset handler

- System
   - flash accelerator configuration
   - watchdog (stop)
   - clock / PLL config
   - systick
   - precise msleep and usleep functions (using systick)
   - pio configuration

- Simple C Library
   - memcpy and memset
   - strcpy, strncpy, strcmp, strncmp, strchr, strrchr, strlen, strnlen
   - snprintf, vsnprintf

- Integrated Interface drivers
   - UART (as UART or RS485)
   - I²C
   - ADC
   - GPIO
   - GPIO interrupts
   - Counter / Timers
   - SPI (SSP)
   - PWM
   - RTC (partial)

- External Device drivers
   - I²C EEPROM
   - TMP101 I²C temperature sensor
   - DHT11 temperatur and Humidity sensor
   - CC1101 Sub 1GHz RF Transceiver
   - Status led
   - Epaper display
   - WS2812 chainable leds

- Other
   - 8x8 font for use with Epaper display


********************
TODO :

- Deep sleep mode support.
- Test all the GPIO in different modes
- Add support for SDCard over SPI
- Complete RTC Support
- Comparator support
- Watchdog support
- CRC engine support
- Test UART IrDA mode
