/*
 * main.c
 */

// THIS PROGRAM ALLOWS THE DSP TO INTERFACE ADC0804 AND INDICATES THROUGH LEDs
// THAT SET POINT OF TEMPERATURE SENSOR HAS BEEN REACHED

#include <stdio.h>
#include <stdlib.h>
#include <csl_gpio.h>
#include <csl_gpiohal.h>

// CODE TO DEFINE GPIO HANDLE
GPIO_Handle gpio_handle;

// GPIO REGISTER CONFIGURATION
GPIO_Config gpio_config = {
    0x00000000, // gpgc = Interruption passthrough mode
    0x0000FFFF, // gpen = All GPIO 0-15 pins enabled
    0x00008070, // gdir = Pin 4,5,6,15 as outputs, rest as inputs
    0x00000000, // gpval = Saves the logical states of pins
    0x00000000, // gphm All interrupts disabled for IO pins
    0x00000000, // gplm All interrupts for CPU EDMA disabled
    0x00000000  // gppol -- default state */
};

// Program starts
main()
{
	// Board initialization
    DSK6713_init();

    // Open and configure the GPIO
    gpio_handle = GPIO_open( GPIO_DEV0, GPIO_OPEN_RESET );
    GPIO_config(gpio_handle,&gpio_config);

    Uint32 intr = 0;
    Uint32 val1 = 0; //To check IR Sensor input from PIN8
    Uint32 val2 = 0; //To check IR Sensor input from PIN9
    Uint32 val3 = 0; //To check IR Sensor input from PIN10
    Uint32 val4 = 0; //To check IR Sensor input from PIN11
    Uint32 val5 = 0; //To check IR Sensor input from PIN3
    Uint32 val6 = 0; //To check IR Sensor input from PIN6
    Uint32 val = 0;

    GPIO_pinWrite (gpio_handle, GPIO_PIN15, 1);
    GPIO_pinWrite (gpio_handle, GPIO_PIN6, 0);

    // Infinite loop checking for obstacle presence and indicating through LEDs
    while(1)
   	{
    	GPIO_pinWrite (gpio_handle, GPIO_PIN4, 1); // make RD high
    	GPIO_pinWrite (gpio_handle, GPIO_PIN5, 0); // make WR low
    	GPIO_pinWrite (gpio_handle, GPIO_PIN5, 1); // low to high pulse on WR for starting conversion
    	while(1) // polls until INTR=0
    	{
    		intr = GPIO_pinRead (gpio_handle, GPIO_PIN7);
    		if (intr == 0)
    			break;
    	}
    	GPIO_pinWrite (gpio_handle, GPIO_PIN4, 0); // high to low pulse to RD for reading the data from ADC
    	//Using lower 6 Bits from ADC
    	val1 = GPIO_pinRead (gpio_handle, GPIO_PIN8); // Bit 0 LSB
    	val2 = GPIO_pinRead (gpio_handle, GPIO_PIN9); // Bit 1
    	val3 = GPIO_pinRead (gpio_handle, GPIO_PIN10); // Bit 2
    	val4 = GPIO_pinRead (gpio_handle, GPIO_PIN11); // Bit 3
    	val5 = GPIO_pinRead (gpio_handle, GPIO_PIN3); // Bit 4
    	val6 = GPIO_pinRead (gpio_handle, GPIO_PIN13); // Bit 5 MSB
    	val = val1 | (val2<<1) | (val3<<2) | (val4<<3) | (val5<<4) | (val6<<5);
    	if (val >= 25) // Set Point - 50 degree
    	{
    		GPIO_pinWrite (gpio_handle, GPIO_PIN6, 1);
    		GPIO_pinWrite (gpio_handle, GPIO_PIN15, 0);
    	}
    	else
    	{
    		GPIO_pinWrite (gpio_handle, GPIO_PIN6, 0);
    		GPIO_pinWrite (gpio_handle, GPIO_PIN15, 1);
    	}
   	} //Infinite loop end

} //Program end
