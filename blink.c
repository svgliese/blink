// blink.c
//
// Example program blink for
// http://www.airspayce.com/mikem/bcm2835/examples.html
// bcm2835 library
// http://www.airspayce.com/mikem/bcm2835/index.html
// used as base
//
// Check pin 11 (GPIO 17) on an off every 10 msecs
// and set pin 12 (GPIO 18) on if low level detected at pin 11

#include "bcm2835.h"
#include <stdio.h>
#include <syslog.h>
#include <signal.h>
#include "becomedaemon.h"


// Blinks on RPi Plug P1 pin 11 (which is GPIO pin 17)
#define PIN12 RPI_GPIO_P1_12
#define PIN11 RPI_GPIO_P1_11


int main(int argc, char **argv)
{
	int res;
	res = becomeDaemon(0);
	if (res!=0)
		return res;
	signal(SIGTTOU, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	openlog("Blink log", LOG_PID|LOG_CONS, LOG_DAEMON);
	syslog(LOG_INFO, "Blink started");
	closelog();
	// If you call this, it will not actually access the GPIO
	// Use for testing
	//    bcm2835_set_debug(1);

	if (!bcm2835_init())
		return 1;

	// Set the pin to be an output
	bcm2835_gpio_fsel(PIN12, BCM2835_GPIO_FSEL_OUTP);

	// Set RPI pin P1-15 to be an input
	bcm2835_gpio_fsel(PIN11, BCM2835_GPIO_FSEL_INPT);
	//  with a pullup
	bcm2835_gpio_set_pud(PIN11, BCM2835_GPIO_PUD_UP);
	// And a low detect enable
	bcm2835_gpio_len(PIN11);

	// Blink
	while (1) {
		if (bcm2835_gpio_eds(PIN11))
		{
			// Now clear the eds flag by setting it to 1
			bcm2835_gpio_set_eds(PIN11);
			//printf("low event detect for pin 11\n");
			// Turn it on
			bcm2835_gpio_write(PIN12, HIGH);
		}
		else
		{
			// turn it off
			bcm2835_gpio_write(PIN12, LOW);
		}

		// wait a bit
		bcm2835_delay(10);
	}
	bcm2835_close();
	return 0;
}

