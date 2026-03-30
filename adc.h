/*
 * adc.h
 *
 *  Created on: Aug 28, 2025
 *      Author: DELL
 */

#ifndef ADC_H_
#define ADC_H_

#include "base.h"

#define RCC_APB2ENR_OFFSET				(0x20)
#define RCC_APB2ENR						(*(volatile unsigned int*)(RCC_PERIPHERAL + RCC_APB2ENR_OFFSET))

#define ADC_SR_OFFSET					(0x00)
#define ADC_SR							(*(volatile unsigned int*)(ADC_PERIPHERAL + ADC_SR_OFFSET))

#define ADC_CR1_OFFSET					(0x04)
#define ADC_CR1							(*(volatile unsigned int*)(ADC_PERIPHERAL + ADC_CR1_OFFSET))

#define ADC_CR2_OFFSET					(0x08)
#define ADC_CR2							(*(volatile unsigned int*)(ADC_PERIPHERAL + ADC_CR2_OFFSET))

#define ADC_SMPR3_OFFSET				(0x14)
#define ADC_SMPR3						(*(volatile unsigned int*)(ADC_PERIPHERAL + ADC_SMPR3_OFFSET))

#define ADC_SQR5_OFFSET					(0x40)
#define ADC_SQR5						(*(volatile unsigned int*)(ADC_PERIPHERAL + ADC_SQR5_OFFSET))

#define ADC_SQR1_OFFSET					(0x30)
#define ADC_SQR1						(*(volatile unsigned int*)(ADC_PERIPHERAL + ADC_SQR1_OFFSET))

#define ADC_DR_OFFSET					(0x58)
#define ADC_DR							(*(volatile unsigned int*)(ADC_PERIPHERAL + ADC_DR_OFFSET))





/* enable bits*/
/*#define RCC_ADC1EN							(1U<<9)
#define	ADC_SR_EOC							(1U<<1)
#define ADC_CR2_ADON						(1U<<0)
#define ADC_CR2_CONT						(1U<<1)
#define ADC_SMPR3_SMP0						(4U<<0)
#define ADC_SQR5_SQ1						(0U<<0)
#define ADC_CR1_RES1						(1U<<24)
#define ADC_CR1_RES2						(1U<<25)
#define ADC_CR1_RES_24						(1U<<24)
#define ADC_CR1_RES_25						(1U<<25)
*/

/*Function prototypes*/
void adc_init();
void adc_conversion();
int adc_read();
void adc_sample_tranmit_sgnl();
//void adc_smp_sgnl(char * buff, int * prgrm_state);
//void adc_trnsmt_sgnl(char * buff);




#endif /* ADC_H_ */
