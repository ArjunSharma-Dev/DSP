/*
 * main.c
 */

// THIS PROGRAM ALLOWS THE DSP TO INTERFACE IR SENSOR AND INDICATE THE NUMBER OF PEOPLE COUNTED
// THROUGH LED 7 SEGMENT DISPLAY

#include <stdio.h>
#include <stdlib.h>
#include <csl_gpio.h>
#include <csl_gpiohal.h>

// Function prototypes
void displaynumber(int num);

// CODE TO DEFINE GPIO HANDLE
GPIO_Handle gpio_handle;

// GPIO REGISTER CONFIGURATION
GPIO_Config gpio_config = {
    0x00000000, // gpgc = Interruption passthrough mode
    0x0000FFFF, // gpen = All GPIO 0-15 pins enabled
    0x00000FF0, // gdir = Pin 4,5,6,7,8,9,10,11 as outputs, rest as inputs
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

    int counter = 0;
    Uint32 detectionLH = 0; //To get low-to-high transition IR Sensor input from PIN15
    Uint32 reset = 0; //To check if reset button is pressed from PIN13

    //Display initial count as 0
    displaynumber(counter);

    // Infinite loop checking for obstacle presence and indicating through LEDs
    while(1)
   	{
   	    detectionLH = GPIO_deltaHighGet (gpio_handle,GPIO_PIN15); //IR sensor input
   	    reset = GPIO_deltaHighGet (gpio_handle,GPIO_PIN13); //Reset button input

   	    //Reset button pressed
   	    if (reset == (1<<13))
   	    {
   	    	GPIO_deltaHighClear (gpio_handle,GPIO_PIN13);
   	    	counter=0;
   	    	displaynumber(counter);
   	    }

   	    //IR sensor detects person , count increases
   		if (detectionLH == (1<<15))
   		{
   			GPIO_deltaHighClear (gpio_handle,GPIO_PIN15);
   			counter++;
   			if (counter==100)
   				counter=0;
   			displaynumber(counter);
   		}
   	} //Infinite loop end

} //Program end

// Function definitions
void displaynumber(int number)
{
	int num1,num2;

	num1 = number/10; //Get tens place
	num2 = number%10; //Get units place

	//Tens place : A - PIN8 ; B - PIN9 ; C - PIN10 ; D - PIN11 ;
	switch (num1)
	{
	case 0 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 1 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 2 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 3 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 4 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 5 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 6 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 7 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,0);
		break;
	case 8 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,1);
		break;
	case 9 : GPIO_pinWrite (gpio_handle,GPIO_PIN8,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN9,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN10,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN11,1);
		break;
	}

	//Units place : A - PIN4 ; B - PIN5 ; C - PIN6 ; D - PIN7 ;
	switch (num2)
	{
	case 0 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 1 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 2 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 3 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 4 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 5 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 6 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 7 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,0);
		break;
	case 8 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,1);
		break;
	case 9 : GPIO_pinWrite (gpio_handle,GPIO_PIN4,1);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN5,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN6,0);
	 GPIO_pinWrite (gpio_handle,GPIO_PIN7,1);
		break;
	}
}
