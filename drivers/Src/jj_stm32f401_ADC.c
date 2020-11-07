/*
 * jj_stm32f401_ADC.c
 *
 *  Created on: 18 Aug 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#include "jj_stm32f401_ADC.h"

void jj_ADC_Init(jj_ADC_Config config) {
	if(config.conversion_mode == CONV_MODE_CONT) {
		JJ_pADC1->CR2 |= (1 << 1);
	}
	else {
		JJ_pADC1->CR2 &= ~(1 << 1);
	}

	JJ_pADC1->CR1 &= ~(1 << 0 | 1 << 1 | 1 << 2 | 1 << 3 | 1 << 4 );
	JJ_pADC1->CR1 |= (1 << 5); //IRQ enabled
	JJ_pADC1->CR2 |= (1 << 10); //EOCS

	JJ_pADC1->SMPR2 |= (1 << 0 | 1 << 1 | 1 << 2);

	(*JJ_ADC_CCR_REG) |= ( 1 << 16 );
	(*JJ_ADC_CCR_REG) |= ( 1 << 17 ); //div by 8
}

uint16_t jj_ADC_READ(void) {
	return (uint16_t) (JJ_pADC1->DR);
}

void jj_ADC_CLK_EN(uint8_t en_dis) {
	if(en_dis == JJ_ENABLE) {
		JJ_ADC1_CLK_EN();
	}
	else {
		JJ_ADC1_CLK_DIS();
	}
}

void jj_ADC_ENABLE(uint8_t en_dis) {

	if(en_dis == JJ_ENABLE) {
		JJ_pADC1->CR2 |= ADC_CR2_ADON;
		JJ_pADC1->CR1 |= ADC_CR1_AWDEN;
		(*JJ_ADDR_ISER0) |= (1 << 18); //ADC irq nr
		JJ_pADC1->CR2 |= ADC_C2_SWSTART;
	}
	else {
		JJ_pADC1->CR2 &= ~(ADC_CR2_ADON);
		//JJ_pADC1->CR1 &= ~(ADC_CR1_AWDEN);
		(*JJ_ADDR_ISER0) &= ~(1 << 18); //ADC irq nr
		JJ_pADC1->CR2 &= ~ADC_C2_SWSTART;
	}
}

void jj_ADC_START_NEW_CONV(void) {
	JJ_pADC1->CR2 |= ADC_C2_SWSTART;
}
