/*
 * main.c
 */

// THIS PROGRAM ALLOWS THE DSP TO INTERFACE IR SENSORS AND INDICATE PRESENCE OF OBSTACLE
// THROUGH LEDs

#include <stdio.h>
#include <stdlib.h>
#include <csl_gpio.h>
#include <csl_gpiohal.h>

#define FALSE 0
#define TRUE 1

// CODE TO DEFINE GPIO HANDLE
GPIO_Handle gpio_handle;

// GPIO REGISTER CONFIGURATION
GPIO_Config gpio_config = {
    0x00000000, // gpgc = Interruption passthrough mode
    0x0000FFFF, // gpen = All GPIO 0-15 pins enabled
    0x0000BF8B, // gdir = Pin 1,3,7,8,9,10,11,12,13,15 as outputs, rest as inputs
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

    Uint32 val1 = 0; //To check IR Sensor input from PIN4
    Uint32 val2 = 0; //To check IR Sensor input from PIN5
    Uint32 val3 = 0; //To check IR Sensor input from PIN6

    // Infinite loop checking for obstacle presence and indicating through LEDs
    while(1)
   	{
   		val1 = GPIO_pinRead(gpio_handle,GPIO_PIN4); //left
   		val2 = GPIO_pinRead(gpio_handle,GPIO_PIN5); //middle
   		val3 = GPIO_pinRead(gpio_handle,GPIO_PIN6); //right

   		// Pin 1 - left LED ; Pin 3 - Middle LED ; Pin 8 - Right LED
   		// Pin 7 - Buzzer
   		// LED 7 segment connections
   		// Pin 9 - a ; Pin 10 - b ; Pin 11 - c ; Pin 12 - d ;
   		// Pin 13 - e ; Pin 15 - g ;
   		// f is always lighted as it is common in all the display combination

   		// No obstacle detected
   		if (val1==FALSE && val2==FALSE && val3==FALSE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,0); //Buzzer off
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,0);

   			// Display S - straight
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,1);
   		}
   		// Left IR sensor detects obstacle
   		else if (val1==TRUE && val2==FALSE && val3==FALSE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,1); //Buzzer on
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,1);

   			// Display R - right
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,1);
   		}
   		// Left IR & Middle IR sensor detects obstacle
   		else if (val1==TRUE && val2==TRUE && val3==FALSE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,1); //Buzzer on
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,1);

   			// Display R - right
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,1);
   		}
   		// Right IR sensor detects obstacle
   		else if (val1==FALSE && val2==FALSE && val3==TRUE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,1); //Buzzer on
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,0);

   			// Display L - left
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,0);
   		}
   		// Right IR & Middle IR sensor detects obstacle
   		else if (val1==FALSE && val2==TRUE && val3==TRUE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,1); //Buzzer on
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,0);

   			// Display L - left
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,0);
   		}
   		// Left IR & Right IR sensor detects obstacle
   		else if (val1==TRUE && val2==FALSE && val3==TRUE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,1); //Buzzer on
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,1);

   			// Display B - back
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,1);
   		}
   		// Middle IR sensor detects obstacle
   		else if (val1==FALSE && val2==TRUE && val3==FALSE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,1); //Buzzer on
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,1);

   			// Display L - left ( can also be chosen to display R)
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,0);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,0);
   		}
   		// All IR sensor detects obstacle
   		else if (val1==TRUE && val2==TRUE && val3==TRUE)
   		{
   			GPIO_pinWrite(gpio_handle,GPIO_PIN7,1); //Buzzer on
   			GPIO_pinWrite(gpio_handle,GPIO_PIN1,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN3,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN8,1);

   			// Display B - back
   			GPIO_pinWrite(gpio_handle,GPIO_PIN9,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN10,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN11,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN12,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN13,1);
   			GPIO_pinWrite(gpio_handle,GPIO_PIN0,1);
   		}
   	} //Infinite loop end

} //Program end
