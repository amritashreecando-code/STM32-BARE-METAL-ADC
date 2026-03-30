/*
 * gpio.c
 *
 *  Created on: Aug 28, 2025
 *      Author: DELL
 */



#include "gpio.h"

/*enable bits*/
#define RCC_GPIOAEN						(1U<<0)
#define RCC_GPIOBEN						(1U<<1)
#define RCC_GPIOCEN						(1U<<2)
//#define USERLED							(1U<<5)
#define GPIOA8							(1U<<8)
#define ORANGE_LED						(1U<<5) // For enabling ODR bits
#define PUSHBUTTON						(1U<<13) //for enabling IDR bits



void gpio_init()
{
	//allow clock access to GPIOA
	RCC_AHBENR |= RCC_GPIOAEN;

	//allow clock access to GPIOB
	RCC_AHBENR |= RCC_GPIOBEN;

	//allow clock access to GPIOC
	RCC_AHBENR |= RCC_GPIOCEN;



	//set the  mode of the GPIOA (pin8) ie set the general purpose O mode by enabling the MODER reg
	// this is required for enabling the ODR as the pin A8 is chosen as output
	//GPIOA_MODER |= (1U<<16);  /* setting the port A8 as the output port*/
	//GPIOA_MODER &= ~(1U<<17);

	//Set the mode of the GPIOB (pin5) ie set the GPO mode by enabling the MODER reg
	//this is required for enabling ODR(bit 5) as the pin B5 is chosen as output
	//GPIOB_MODER |= (1U<<10); /*setting the port B5 as the output port*/
	//GPIOB_MODER &= ~(1U<<11);

	//Set the mode of the GPIOC (pin13) ie set the input state by enabling the MODER reg
	//this is required for enabling IDR(bit 13) as the pin C13 is the input pin(push button)(00)
	//GPIOC_MODER &= ~(1U<<26);
	//GPIOC_MODER &= ~(1U<<27);

	//set the alternate function mode(10) for GPIOA as we will be using PA2 as TX in GPIOA_AFRL
		GPIOA_MODER &= ~(1U<<4);
		GPIOA_MODER |= (1U<<5);


	//set the alternate function mode for GPIOA as we will be using PA3 as RX in GPIOA_AFRL
		GPIOA_MODER &= ~(1U<<6);
		GPIOA_MODER |= (1U<<7);

	//set analog function for PA0
		GPIOA_MODER |= (1U<<0);
		GPIOA_MODER |= (1U<<1);


	//set alternate function for PA2 (AF7)
		GPIOA_AFRL |= (1U<<8);
		GPIOA_AFRL |= (1U<<9);
		GPIOA_AFRL |= (1U<<10);
		GPIOA_AFRL &= ~(1U<<11);

	//set alternate function for PA3 (AF7)
		GPIOA_AFRL |= (1U<<12);
		GPIOA_AFRL |= (1U<<13);
		GPIOA_AFRL |= (1U<<14);
		GPIOA_AFRL &= ~(1U<<15);




}

/*void led_toggle()
{
	GPIOA_ODR |= USERLED;
	led_delay();
	GPIOA_ODR &= ~(USERLED);
	led_delay();
}*/
/*void red_led_on()
{
	GPIOA_ODR |= GPIOA8;


}

void red_led_off()
{
	GPIOA_ODR &= ~(GPIOA8);
}

void led_delay()
{
	for(volatile int x=0;x<500000;x++);
}

void orange_led_on()
{
	GPIOB_ODR |= ORANGE_LED;
}

void orange_led_off()
{
	GPIOB_ODR &= ~(ORANGE_LED);
}

void led_prgrmstate_set(int *prgrm_state)
{
	if(!(GPIOC_IDR & PUSHBUTTON))
		{
			if(*prgrm_state == OFF)
			{
				*prgrm_state = ON;
				led_delay();
			}
			else if(*prgrm_state == ON)
			{
				*prgrm_state = OFF;
				led_delay();
			}

		}

}
void led_prgrmstate_dsplay(int *prgrm_state)
{

	if(*prgrm_state == OFF)
		{
			red_led_on();
			orange_led_off();
			led_delay();
		}

		else if(*prgrm_state == ON)
		{
			red_led_off();
			orange_led_on();
			led_delay();
		}
}
*/


