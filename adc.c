/*
 * adc.c
 *
 *  Created on: Aug 28, 2025
 *      Author: DELL
 */

#ifndef ADC_C_
#define ADC_C_

#include <stdio.h>

#include "usart.h"
#include "adc.h"
/*enable bits*/
#define RCC_ADC1EN							(1U<<9)
#define	ADC_SR_EOC							(1U<<1)
#define ADC_SR_RCNR 						(1U<<8)
#define ADC_SR_ADONS						(1U<<6)
#define ADC_CR2_ADON						(1U<<0)
#define ADC_CR2_CONT						(1U<<1)
#define ADC_SMPR3_SMP0_CLR					(7U<<0) // for clearing the SMPR3 SMP0 bits
#define ADC_SMPR3_SMP0						(4U<<0) // for setting the bits 0,1,2 of SMP0 to 4(100)ie48clkcycles
#define ADC_SQR1_L_CLR						(31U<<20)
#define ADC_SQR1_L							(0U<<20)
#define ADC_SQR5_SQ1_CLR					(31U<<0) // for clearing  the SQ1 bits from 0 to 4
#define ADC_SQR5_SQ1						(0U<<0)	// for setting the channel 0
//#define ADC_CR1_RES1						(1U<<24)
//#define ADC_CR1_RES2						(1U<<25)
#define ADC_CR1_RES_CLR						(3U<<24) // for clearing the resolution bits
#define ADC_CR1_RES							(2U<<24)  //for setting the bits 24 and 25 to 0 & 1
//#define ADC_CR1_RES_24					(0U<<24)
//#define ADC_CR1_RES_25					(1U<<25)
#define ADC_CR2_SWSTART						(1U<<30)


/*function prototypes*/

void adc_init()
{
	//allow clock access to usart peripheral
	RCC_APB2ENR |= RCC_ADC1EN;

	//set  GPIOA0 in gpio.c mode to analog


	//set data resolution
	//first clear the bits and then set the bits 24and 25 to 0 and 1 respectively for 8 bit resolution
	/*ADC_CR1 &= ~(ADC_CR1_RES1);
	ADC_CR1 &= ~(ADC_CR1_RES2);

	ADC_CR1 |= ADC_CR1_RES_24;
	ADC_CR1 |= ADC_CR1_RES_25;

*/
	//set data resolution
	//first clear the bits and then set the bits 24and 25 to 0 and 1 respectively for 8 bit resolution
	ADC_CR1 &= ~(ADC_CR1_RES_CLR);
	ADC_CR1 |= ADC_CR1_RES;





	// set channel conversion time in cycles and the order of conversion
	//first clear the SMP0  bits and then set the SMP0 bits ie 0,1,2 to 100
	ADC_SMPR3 &= ~(ADC_SMPR3_SMP0_CLR);
	ADC_SMPR3 |= ADC_SMPR3_SMP0;

	//set the total no of conversions needed by setting L bit in the ADC_SQR1 reg
	//first clear the L bits and then set these bits to 00000 as L = no of conversions - 1
	ADC_SQR1 &= ~(ADC_SQR1_L_CLR);
	ADC_SQR1 |= ADC_SQR1_L;


	//select the channel (ie channel0) and set the no of conversions and the sequence of conversion
	//first clear the SQ1 bits of the SQR5 reg and then set the bits (0 to 4) to 00000
	ADC_SQR5 &= ~(ADC_SQR5_SQ1_CLR);
	ADC_SQR5 |= ADC_SQR5_SQ1;

	//The RCNR bit is set and cleared by hardware after one of the SQRx register is written or after the
	//OVR it is cleared it indicates a new conversion can be launched by setting the SWSTART bit
	//to check whether RCNR bit is 0 and ADONS bit is 1, only then SWSTART bit can be HIGH
	//ie conversion can start

	//while((ADC_SR & ADC_SR_RCNR) && !(ADC_SR & ADC_SR_ADONS));


	//enable adc module
	ADC_CR2 |= ADC_CR2_ADON;

	//add a small delay
	for(volatile int i = 0; i < 1000; i++);

	while(!(ADC_SR & ADC_SR_ADONS)); // Wait for ADC to be enabled (ADONS bit set)

	while(ADC_SR & ADC_SR_RCNR); // Wait for RCNR to be cleared

}
void adc_conversion()
{
	ADC_CR2 |= ADC_CR2_CONT;  // Set continuous conversion mode

	ADC_CR2 |= ADC_CR2_SWSTART; //start the conversion

}
int adc_read()
{
	while(!(ADC_SR & ADC_SR_EOC))
		;
	return ADC_DR;
}
/*void adc_smp_sgnl(char * buff, int * prgrm_state)
{
	char byte_one;
	int uart_byte;
	if(*prgrm_state == ON)
		char *ptr = buff;
	for(int x=0;x<64;x++)
	{
		uart_byte = adc_read();
		byte_one = uart_byte & 0xFF;
		*buff++ = byte_one;
	}
	//sampling complete
	void adc_transmit_sgnl(ptr);
}
void adc_transmit_sgnl(char *buff)
{
	for(int x=0;x<64;x++)
	{
		uart_write(*buff++);
	}
}
*/
void adc_sample_tranmit_sgnl()
{
	int uart_byte;
	char buff[64]; // here name of the array ie buff stores the base address of the array
	char *ptr = buff;//buff and ptr both have the same base address
	for (int i=0;i<64;i++)
	{
		uart_byte = adc_read();
		//adc_read() returns the ADC value in the ADC_DR reg and that value stored in uart byte
		*ptr = (char)(uart_byte & 0xFF);//keeps only the last 8 bits
		usart2_write(*ptr);// passes the value stored in the base address contained in ptr
		ptr++; // increments the address by 1
		for(volatile int i=0; i<10000; i++); // small delay

	}
}

/*void adc_sample_tranmit_sgnl()
{
    int value = adc_read();   // read one sample
    int temp = value & 0xFF;  // keep 8-bit

    // Send as readable ASCII number
    char str[10];
    sprintf(str, "%d\r\n", temp);

    char *p = str;
    while(*p)
    {
        usart2_write(*p++);
    }

    for(volatile int i=0; i<10000; i++); // small delay
}
*/



#endif /* ADC_C_ */
