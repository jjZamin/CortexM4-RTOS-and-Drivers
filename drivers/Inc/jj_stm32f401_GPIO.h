/*
 * jj_stm32f401_GPIO.h
 *
 *  Created on: 18 Aug 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#ifndef INC_JJ_STM32F401_GPIO_H_
#define INC_JJ_STM32F401_GPIO_H_

#include "jj_Addresses.h"
#include <stdint.h>



/*GPIO PIN CONFIGURATION*/
typedef struct {
	uint8_t GPIO_PinNr;
	uint8_t GPIO_PinMODE;			// MODES
	uint8_t GPIO_PinSPEED;
	uint8_t GPIO_PinPuPd;
	uint8_t GPIO_PinOutPutType;
	uint8_t GPIO_AltFunct;
} jj_GPIO_pinConfig;




/*GPIO REGISETERS MACROS*/

/*
 * MODES, p158, refman
 * */

#define JJ_GPIO_MODE_IN 					0
#define JJ_GPIO_MODE_OUT					1
#define JJ_GPIO_MODE_AF						2
#define JJ_GPIO_MODE_ANLG					3
/*when input mode*/
#define JJ_GPIO_MODE_IRQ_FE					4 		//IRQ @falling edge
#define JJ_GPIO_MODE_IRQ_RE					5 		//IRQ @rising edge
#define JJ_GPIO_MODE_IRQ_FRE				6 		//IRQ @falling & rising edges

/*
 * OTYPE (output), p158, refman
 * */

#define JJ_GPIO_OUTPUT_PP					0		//output push pull
#define JJ_GPIO_OUTPUT_OD					1		//open drain

/*
 * SPEED (output), p159, refman
 * */

#define JJ_GPIO_SPEED_LOW					0
#define JJ_GPIO_SPEED_MEDIUM				1
#define JJ_GPIO_SPEED_HIGH					2
#define JJ_GPIO_SPEED_VHIGH					3		//very high

/*
 * Pull up, pull down, p159, refman
 * */

#define JJ_GPIO_PULL_NO						0
#define JJ_GPIO_PULL_UP						1
#define JJ_GPIO_PULL_DOWN					2

/*
 * Pin Numbers
 * */

#define JJ_PIN_0							0
#define JJ_PIN_1							1
#define JJ_PIN_2							2
#define JJ_PIN_3							3
#define JJ_PIN_4							4
#define JJ_PIN_5							5
#define JJ_PIN_6							6
#define JJ_PIN_7							7
#define JJ_PIN_8							8
#define JJ_PIN_9							9
#define JJ_PIN_10							10
#define JJ_PIN_11							11
#define JJ_PIN_12							12
#define JJ_PIN_13							13
#define JJ_PIN_14							14
#define JJ_PIN_15							15

/*
 * alternate functions
 * */

#define JJ_AF_0								0
#define JJ_AF_1								1
#define JJ_AF_2								2
#define JJ_AF_3								3
#define JJ_AF_4								4
#define JJ_AF_5								5
#define JJ_AF_6								6
#define JJ_AF_7								7
#define JJ_AF_8								8
#define JJ_AF_9								9
#define JJ_AF_10							10
#define JJ_AF_11							11
#define JJ_AF_12							12
#define JJ_AF_13							13
#define JJ_AF_14							14
#define JJ_AF_15							15

/*----------------------------------[START: PERIPHERAL STRUCTURES]----------------------------------*/
/*-----GPIO-----*/
typedef struct { //p164, refman
	volatile uint32_t MODER;	 		//0x00
	volatile uint32_t OTYPER;			//0x04
	volatile uint32_t OSPEEDR;			//0x08
	volatile uint32_t PUPDR;			//0x0CPUPDR
	volatile uint32_t IDR;				//0x10
	volatile uint32_t ODR;				//0x14
	volatile uint32_t BSRR;				//0x18
	volatile uint32_t LCKR;				//0x1C
	volatile uint32_t AFR[2];			//0x20 - 0x24
} jj_GPIO_Registers;

#define JJ_pGPIOA								((jj_GPIO_Registers*)JJ_BASEADDR_GPIOA)
#define JJ_pGPIOB								((jj_GPIO_Registers*)JJ_BASEADDR_GPIOB)
#define JJ_pGPIOC								((jj_GPIO_Registers*)JJ_BASEADDR_GPIOC)
#define JJ_pGPIOD								((jj_GPIO_Registers*)JJ_BASEADDR_GPIOD)
#define JJ_pGPIOE								((jj_GPIO_Registers*)JJ_BASEADDR_GPIOE)
#define JJ_pGPIOH								((jj_GPIO_Registers*)JJ_BASEADDR_GPIOH)

#define JJ_BASEADDR_GPIO_TO_4bitCODE(baseaddr)	((baseaddr == JJ_pGPIOA) ? 0 :\
												 (baseaddr == JJ_pGPIOB) ? 1 :\
												 (baseaddr == JJ_pGPIOC) ? 2 :\
												 (baseaddr == JJ_pGPIOD) ? 3 :\
												 (baseaddr == JJ_pGPIOE) ? 4 :\
												 (baseaddr == JJ_pGPIOH) ? 7 : 0 )
												//if a = b, return G, else go to next expression. (a = b ? G :\)

/*------GPIO CLOCKs----*/
#define JJ_GPIOA_CLK_EN()						(JJ_RCC -> AHB1ENR |= (1 << 0))
#define JJ_GPIOB_CLK_EN()						(JJ_RCC -> AHB1ENR |= (1 << 1))
#define JJ_GPIOC_CLK_EN()						(JJ_RCC -> AHB1ENR |= (1 << 2))
#define JJ_GPIOD_CLK_EN()						(JJ_RCC -> AHB1ENR |= (1 << 3))
#define JJ_GPIOE_CLK_EN()						(JJ_RCC -> AHB1ENR |= (1 << 4))
#define JJ_GPIOH_CLK_EN()						(JJ_RCC -> AHB1ENR |= (1 << 7))

#define JJ_GPIOA_CLK_DIS()						(JJ_RCC -> AHB1ENR &= ~(1 << 0))
#define JJ_GPIOB_CLK_DIS()						(JJ_RCC -> AHB1ENR &= ~(1 << 1))
#define JJ_GPIOC_CLK_DIS()						(JJ_RCC -> AHB1ENR &= ~(1 << 2))
#define JJ_GPIOD_CLK_DIS()						(JJ_RCC -> AHB1ENR &= ~(1 << 3))
#define JJ_GPIOE_CLK_DIS()						(JJ_RCC -> AHB1ENR &= ~(1 << 4))
#define JJ_GPIOH_CLK_DIS()						(JJ_RCC -> AHB1ENR &= ~(1 << 7))

/*------GPIO RESET----*/
#define JJ_GPIOA_RST()						do { (JJ_RCC -> AHB1RSTR |= (1 << 0)); (JJ_RCC -> AHB1RSTR &= ~(1 << 0)); } while(0)
#define JJ_GPIOB_RST()						do { (JJ_RCC -> AHB1RSTR |= (1 << 1)); (JJ_RCC -> AHB1RSTR &= ~(1 << 1)); } while(0)
#define JJ_GPIOC_RST()						do { (JJ_RCC -> AHB1RSTR |= (1 << 2)); (JJ_RCC -> AHB1RSTR &= ~(1 << 2)); } while(0)
#define JJ_GPIOD_RST()						do { (JJ_RCC -> AHB1RSTR |= (1 << 3)); (JJ_RCC -> AHB1RSTR &= ~(1 << 3)); } while(0)
#define JJ_GPIOE_RST()						do { (JJ_RCC -> AHB1RSTR |= (1 << 4)); (JJ_RCC -> AHB1RSTR &= ~(1 << 4)); } while(0)
#define JJ_GPIOH_RST()						do { (JJ_RCC -> AHB1RSTR |= (1 << 7)); (JJ_RCC -> AHB1RSTR &= ~(1 << 7)); } while(0)

#define NR_PRIOR_BITS					4

/*GPIO pin handler*/
typedef struct {
	/*base addr for gpio periph*/
	jj_GPIO_Registers *pGPIOx;
	jj_GPIO_pinConfig GPIO_PinConfig;

}jj_GPIOx_Handle;

/*---------------------------------------------------GPIO API----------------------------------------------------------------*/
void jj_GPIO_Init(jj_GPIOx_Handle *pHandle);
void jj_GPIO_DeInit(jj_GPIO_Registers *pGPIO);
void jj_GPIO_clk_cntr(jj_GPIO_Registers *pGPIO, uint8_t En_Dis);
uint8_t jj_GPIO_rdPin(jj_GPIO_Registers *pGPIO, uint8_t pinNr);
uint16_t jj_GPIO_rdPort(jj_GPIO_Registers *pGPIO);
void jj_GPIO_wrToPin(jj_GPIO_Registers *pGPIO, uint8_t pinNr, uint8_t value);
void jj_GPIO_wrToPort(jj_GPIO_Registers *pGPIO, uint8_t pinNr, uint16_t value);
void jj_Toggle_Pin(jj_GPIO_Registers *pGPIO, uint8_t pinNr);
void jj_IRQnr_Config(uint8_t IRQnr, uint8_t En_Dis);
void jj_IRQ_Handling(uint8_t pinNr);

#endif /* INC_JJ_STM32F401_GPIO_H_ */
