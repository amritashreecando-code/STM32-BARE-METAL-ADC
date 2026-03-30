/*
 * usart.c
 *
 *  Created on: Aug 30, 2025
 *      Author: DELL
 */


#include "usart.h"

/*enable bits*/
#define USART2CR1_UE						(1U<<13)
#define USART2CR1_RE						(1U<<2)
#define USART2CR1_TE						(1U<<3)
#define USART2SR_RXNE						(1U<<5)
#define USART2SR_TXE						(1U<<7)
#define RCC_APB1ENR_USART2EN					(1U<<17)
#define RCC_CR_HSION						(1U<<0)
#define RCC_CR_HSIRDY						(1U<<1)
#define FLASH_ACR_LATENCY					(1U<<0)
#define FLASH_ACR_LATENCY_0					(0U<<0)
#define RCC_CFGR_HPRE						(15U<4)
#define RCC_CFGR_PPRE1						(7U<<8)
#define RCC_CFGR_PPRE2						(7U<<11)
#define RCC_CFGR_HPRE_DIV1					(0U<<4)
#define RCC_CFGR_PPRE1_DIV1					(0U<<8)
#define RCC_CFGR_PPRE2_DIV1					(0U<<11)
#define RCC_CFGR_SW0						(1U<<0)
#define RCC_CFGR_SW1						(1U<<1)
#define RCC_CFGR_SWS						(1U<<2)
#define RCC_CFGR_SWS2						(1U<<2)
#define RCC_CFGR_SWS3						(1U<<3)
#define SYS_CLK								16000000
//define baud_rate							115200
#define baud_rate							9600

void usart2_init()
{
	//allow clock access to USART2 peripheral
	RCC_APB1ENR	|= RCC_APB1ENR_USART2EN;


	//set USART2 alternate function in gpio.c
	//AF7,PA2 = USART2_TX,PA3 = USART2_RX


	//configure BRR
	usart2_set_baudrate(SYS_CLK,baud_rate);

	//enable TX and RX transfer
	USART2_CR1 |= USART2CR1_RE;
	USART2_CR1 |= USART2CR1_TE;

	//enable USART2 enable in CR1
	USART2_CR1 |= USART2CR1_UE;
}

void Systemclkconfig()
{
	RCC_CR |=RCC_CR_HSION;// setting HSI as the clk source

	while(!(RCC_CR & RCC_CR_HSIRDY)); // HSI  oscillator stable

	//configure flash latency (0 wait states for 16 Mhz)
	FLASH_ACR &= ~(FLASH_ACR_LATENCY); //clearing the bit 0 LATENCY bit

	//Setting 0 wait state ie bit 0 to  0 in the LATENCY bit
	FLASH_ACR |= FLASH_ACR_LATENCY_0;

	//clearing the HPRE ,PPRE1 and PPRE2 bits in RCC_CFGR reg
	RCC_CFGR &= ~(RCC_CFGR_HPRE | RCC_CFGR_PPRE1 | RCC_CFGR_PPRE2);

	//setting the Division by 1 in the HPRE bits ie setting the bits 4,5,6,7 to 1111
	RCC_CFGR |= RCC_CFGR_HPRE_DIV1; //AHB = 16MHZ(SYSCLK/1)

	//Setting the division by 1 in the PPRE1 bits ie setting the bits 8,9,10 to 111
	RCC_CFGR |= RCC_CFGR_PPRE1_DIV1; //APB1 = 16MHZ(SYSCLK/1)

	//Setting the division by 1 in the PPRE2 bits ie setting the bits 11,12,13 to 111
	RCC_CFGR |= RCC_CFGR_PPRE2_DIV1; //APB2 = 16MHZ(SYSCLK/1)

	//SWitch the clk source ,first software  switch ie making SW bits (bits 0 and  1) as  01 for switching to
	// HSI oscillator as clk source and then making SWS bits( bits 2 and 3) for polling ie for checking the
	//actual hardware update

	RCC_CFGR |= RCC_CFGR_SW0;
	RCC_CFGR &= ~(RCC_CFGR_SW1);

	//first clear the SWS bits
	RCC_CFGR &= ~(RCC_CFGR_SWS);

	//then set bit 2 to 1 and bit 3 to 0
	RCC_CFGR |= RCC_CFGR_SWS2;
	RCC_CFGR &= ~(RCC_CFGR_SWS3);

	//polling to check whether clk has been switched to HSI
	while(!(RCC_CFGR |= RCC_CFGR_SWS));


}
void usart2_write(int ch)
{
	while(!(USART2_SR & USART2SR_TXE))
		;
	  USART2_DR = (ch & 0xFF);
}
int usart2_read()
{
	while(!(USART2_SR & USART2SR_RXNE))
		;
		return USART2_DR;
}
 void usart2_set_baudrate(uint32_t peripheral_clk,uint32_t baudrate)

{

		// to set baudrate
		//peripheral clock, 16MHz
		// usart_brr registers
	    USART2_BRR = ((peripheral_clk + (baudrate/2U)) / baudrate);

}
