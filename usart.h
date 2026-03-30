/*
 * usart.h
 *
 *  Created on: Aug 30, 2025
 *      Author: DELL
 */

#ifndef USART_H_
#define USART_H_


#include <stdint.h>
#include "base.h"



#define USART2_SR_OFFSET				(0x00)
#define USART2_SR						(*(volatile unsigned int*)(USART2_PERIPHERAL + USART2_SR_OFFSET))

#define USART2_CR1_OFFSET				(0x0C)
#define USART2_CR1						(*(volatile unsigned int*)(USART2_PERIPHERAL + USART2_CR1_OFFSET))

#define USART2_BRR_OFFSET				(0x08)
#define USART2_BRR						(*(volatile unsigned int*)(USART2_PERIPHERAL + USART2_BRR_OFFSET))

#define USART2_DR_OFFSET				(0x04)
#define USART2_DR						(*(volatile unsigned int*)(USART2_PERIPHERAL + USART2_DR_OFFSET))

#define RCC_CR_OFFSET					(0x00)
#define RCC_CR							(*(volatile unsigned int*)(RCC_PERIPHERAL + RCC_CR_OFFSET))

#define RCC_CFGR_OFFSET					(0x08)
#define RCC_CFGR						(*(volatile unsigned int*)(RCC_PERIPHERAL + RCC_CFGR_OFFSET))

#define RCC_APB1ENR_OFFSET				(0x24)
#define RCC_APB1ENR						(*(volatile unsigned int*)(RCC_PERIPHERAL + RCC_APB1ENR_OFFSET))

#define FLASH_ACR_OFFSET				(0x00)
#define FLASH_ACR						(*(volatile unsigned int*)(FLASH_PERIPHERAL + FLASH_ACR_OFFSET))





/*enable bits*/
/*#define USART2CR1_UE						(1U<<13)
#define USART2CR1_RE						(1U<<2)
#define USART2CR1_TE						(1U<<3)
#define USART2SR_RXNE						(1U<<5)
#define USART2SR_TXE						(1U<<7)
#define RCC_CR_HSION						(1U<<0)
#define RCC_CR_HSIRDY						(1U<<1)
#define FLASH_ACR_LATENCY					(1U<<0)
#define FLASH_ACR_LATENCY0					(0U<<0)
#define RCC_CFGR_HPRE						(15U<4)
#define RCC_CFGR_PPRE1						(7U<<8)
#define RCC_CFGR_PPRE2						(7U<<11)
#define RCC_CFGR_HPRE_DIV1					(0U<<4)
#define RCC_CFGR_PPRE1_DIV1					(0U<<8)
#define RCC_CFGR_PPRE2_DIV1					(0U<<11)
*/
/*function prototypes*/
void usart2_init();
void usart2_write(int);
int usart2_read();
void usart2_set_baudrate(uint32_t peripheral_clock,uint32_t baudrate);
void Systemclkconfig();



#endif /* USART_H_ */
