/*
 * jj_stm32f401_TIM2_5.h
 *
 *  Created on: 18 Aug 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#ifndef INC_JJ_STM32F401_TIM2_5_H_
#define INC_JJ_STM32F401_TIM2_5_H_

#include "jj_Addresses.h"

/*#############################################  TIMERS 2 - 5  #####################################################*/
/*TIM CONFIGURATION*/
typedef struct {

	uint8_t DIR;
	uint16_t PRESCALER;
	uint32_t COUNTER;
	uint32_t ARR;

} jj_TIM2_5_Config;

#define TIM2_5_CR1_ENABLE				0
#define TIM2_5_CR1_UDIS					1
#define TIM2_5_CR1_URS					2
#define TIM2_5_CR1_DIR					4

#define TIM2_IRQnr						28
#define TIM3_IRQnr						29
#define TIM4_IRQnr						30
#define TIM5_IRQnr						50

/*for user config*/
#define TIM2_5_UPCOUNTER				0
#define TIM2_5_DOWNCOUNTER				1

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMCR;
	volatile uint32_t DIER;
	volatile uint32_t SR;
	volatile uint32_t EGR;
	volatile uint32_t CCMR1;
	volatile uint32_t CCMR2;
	volatile uint32_t CCER;
	volatile uint32_t CNT;
	volatile uint32_t PSC;
	volatile uint32_t ARR;
	uint32_t RSVDREG1;
	volatile uint32_t CCR1;
	volatile uint32_t CCR2;
	volatile uint32_t CCR3;
	volatile uint32_t CCR4;
	uint32_t RSVDREG2;
	volatile uint32_t DCR;
	volatile uint32_t DMAR;
	volatile uint32_t TIM2_5_OR;

} jj_TIM2_5_Registers;

#define JJ_pTIM2								((jj_TIM2_5_Registers*)JJ_BASEADDR_TIM2)
#define JJ_pTIM3								((jj_TIM2_5_Registers*)JJ_BASEADDR_TIM3)
#define JJ_pTIM4								((jj_TIM2_5_Registers*)JJ_BASEADDR_TIM4)
#define JJ_pTIM5								((jj_TIM2_5_Registers*)JJ_BASEADDR_TIM5)

/*SPI handler*/
typedef struct {
	/*base addr for gpio periph*/
	jj_TIM2_5_Registers *pTIMx;
	jj_TIM2_5_Config TIM_Config;

}jj_TIM2_5_Handle;

void jj_TIM2_5_init(jj_TIM2_5_Handle *pHandle);
void jj_TIM2_5_Enable(jj_TIM2_5_Registers *pTIM2_5, uint8_t en_dis);
void jj_TIM2_5_clk_cntr(jj_TIM2_5_Registers *pTIM2_5, uint8_t En_Dis);
void jj_TIM2_5_IRQ_Handler(jj_TIM2_5_Registers * pTIM2_5);

void ENBL_TIM2_5_IRQ(uint8_t TIMx_IRQnr);

#define JJ_TIM2_CLK_EN()						(JJ_RCC -> APB1ENR |= (1 << 0))
#define JJ_TIM3_CLK_EN()						(JJ_RCC -> APB1ENR |= (1 << 1))
#define JJ_TIM4_CLK_EN()						(JJ_RCC -> APB1ENR |= (1 << 2))
#define JJ_TIM5_CLK_EN()						(JJ_RCC -> APB1ENR |= (1 << 3))
#define JJ_TIM2_CLK_DIS()						(JJ_RCC -> APB1ENR &= ~(1 << 0))
#define JJ_TIM3_CLK_DIS()						(JJ_RCC -> APB1ENR &= ~(1 << 1))
#define JJ_TIM4_CLK_DIS()						(JJ_RCC -> APB1ENR &= ~(1 << 2))
#define JJ_TIM5_CLK_DIS()						(JJ_RCC -> APB1ENR &= ~(1 << 3))


#endif /* INC_JJ_STM32F401_TIM2_5_H_ */
