/*
 * gpio.h
 *
 *  Created on: Aug 28, 2025
 *      Author: DELL
 */

#ifndef GPIO_H_
#define GPIO_H_

#include "base.h"

#define GPIOA_MODER_OFFSET			(0x00)
#define GPIOA_MODER					(*(volatile unsigned int*)(GPIOA_PERIPHERAL + GPIOA_MODER_OFFSET))

//#define GPIOB_MODER_OFFSET			(0x00)
//#define GPIOB_MODER					(*(volatile unsigned int*)(GPIOB_PERIPHERAL + GPIOB_MODER_OFFSET))

//#define GPIOC_MODER_OFFSET			(0x00)
//#define GPIOC_MODER					(*(volatile unsigned int*)(GPIOC_PERIPHERAL + GPIOC_MODER_OFFSET))


//#define GPIOA_ODR_OFFSET			(0x14)
//#define GPIOA_ODR					(*(volatile unsigned int*)(GPIOA_PERIPHERAL + GPIOA_ODR_OFFSET))

//#define GPIOB_ODR_OFFSET			(0x14)
//#define GPIOB_ODR					(*(volatile unsigned int*)(GPIOB_PERIPHERAL + GPIOB_ODR_OFFSET))


//#define GPIOC_IDR_OFFSET			(0x10)
//#define GPIOC_IDR					(*(volatile unsigned int*)(GPIOC_PERIPHERAL + GPIOC_IDR_OFFSET))

#define GPIOA_AFRL_OFFSET			(0x20)
#define GPIOA_AFRL					(*(volatile unsigned int*)(GPIOA_PERIPHERAL + GPIOA_AFRL_OFFSET))


#define RCC_AHBENR_OFFSET			(0x1C)
#define RCC_AHBENR					(*(volatile unsigned int*)(RCC_PERIPHERAL + RCC_AHBENR_OFFSET))



/* Function prototypes*/
void gpio_init(void);
//void led_toggle(void);
//void red_led_on();
//void red_led_off();
//void orange_led_on();
//void orange_led_off();
//void led_prgrmstate_set(int* prgrm_state);
//void led_prgrmstate_dsplay(int* prgrm_state);
//void led_delay(void);



#endif /* GPIO_H_ */
