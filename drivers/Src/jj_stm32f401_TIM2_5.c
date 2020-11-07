/*
 * jj_stm32f401_TIM2_5.c
 *
 *  Created on: 18 Aug 2020
 *      Author: jj.Zamin (G.Mazin)
 */

/*
 * jj_drvr_timers_stm32f401xx.c
 *
 *  Created on: 16 Aug 2020
 *      Author: ghenm
 *
 *
 *      TIM2-TIM5
 */
#include "jj_stm32f401_TIM2_5.h"

void jj_TIM2_5_init(jj_TIM2_5_Handle *pHandle) {

	if(pHandle->TIM_Config.DIR == TIM2_5_DOWNCOUNTER) {
		pHandle->pTIMx->CR1 |= (1 << TIM2_5_CR1_DIR);
	}
	else {
		pHandle->pTIMx->CR1 &= ~(1 << TIM2_5_CR1_DIR);
	}

	pHandle->pTIMx->PSC = pHandle->TIM_Config.PRESCALER;
	pHandle->pTIMx->ARR = pHandle->TIM_Config.ARR;
	pHandle->pTIMx->EGR = 0x00000000;
	pHandle->pTIMx->DIER |= (1 << 0);

	pHandle->pTIMx->CR2 |= (1 << 7);
}

void ENBL_TIM2_5_IRQ(uint8_t TIMx_IRQnr) {
	(*JJ_ADDR_ISER0) |= (1 << TIMx_IRQnr);
}

void jj_TIM2_5_clk_cntr(jj_TIM2_5_Registers *pTIM2_5, uint8_t En_Dis) {
	if(En_Dis == JJ_ENABLE) {
		if(pTIM2_5 == JJ_pTIM2) {
			JJ_TIM2_CLK_EN();
		}
		else if(pTIM2_5 == JJ_pTIM3) {
			JJ_TIM3_CLK_EN();
		}
		else if(pTIM2_5 == JJ_pTIM4) {
			JJ_TIM4_CLK_EN();
		}
		else if(pTIM2_5 == JJ_pTIM5) {
			JJ_TIM5_CLK_EN();
		}
	}
	else {
		if(pTIM2_5 == JJ_pTIM2) {
			JJ_TIM2_CLK_DIS();
		}
		else if(pTIM2_5 == JJ_pTIM3) {
			JJ_TIM3_CLK_DIS();
		}
		else if(pTIM2_5 == JJ_pTIM4) {
			JJ_TIM4_CLK_DIS();
		}
		else if(pTIM2_5 == JJ_pTIM5) {
			JJ_TIM5_CLK_DIS();
		}
	}
}

void jj_TIM2_5_IRQ_Handler(jj_TIM2_5_Registers *pTIM2_5) {
	pTIM2_5 -> SR &= ~(1 << 0); //resetting the UIF flag
}

void jj_TIM2_5_Enable(jj_TIM2_5_Registers * pTIM2_5, uint8_t en_dis) {
	if(en_dis == JJ_ENABLE) {
		pTIM2_5 -> CR1 |= (1 << TIM2_5_CR1_ENABLE);
	}
	else {
		pTIM2_5 -> CR1 &= ~(1 << TIM2_5_CR1_ENABLE);
	}
}


