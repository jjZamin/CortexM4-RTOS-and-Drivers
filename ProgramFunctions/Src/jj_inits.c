/*
 * jj_inits.c
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#include "jj_inits.h"


void ADC_init(void) {
	jj_GPIOx_Handle ADC_PIN; //PA0
	memset(&ADC_PIN, 0, sizeof(ADC_PIN));

	ADC_PIN.pGPIOx = JJ_pGPIOA;
	ADC_PIN.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_0;
	ADC_PIN.GPIO_PinConfig.GPIO_PinMODE = JJ_GPIO_MODE_ANLG;
	ADC_PIN.GPIO_PinConfig.GPIO_PinPuPd = JJ_GPIO_PULL_NO;
	jj_GPIO_clk_cntr(JJ_pGPIOA, JJ_ENABLE);
	jj_GPIO_Init(&ADC_PIN);

	jj_ADC_Config ADC_conf;
	//ADC_conf.channel = ADC_CH0;
	ADC_conf.conversion_mode = CONV_MODE_SINGLE;
	jj_ADC_CLK_EN(JJ_ENABLE);
	jj_ADC_Init(ADC_conf);
	jj_ADC_ENABLE(JJ_ENABLE);
}

void TIM2_init(uint32_t PRESCLR, uint32_t count_to) {

	jj_TIM2_5_Handle TIM2;
	memset(&TIM2, 0, sizeof(TIM2));

	TIM2.pTIMx = JJ_pTIM2;
	TIM2.TIM_Config.DIR = TIM2_5_UPCOUNTER;
	TIM2.TIM_Config.PRESCALER = PRESCLR;
	TIM2.TIM_Config.ARR = count_to;

	jj_TIM2_5_clk_cntr(JJ_pTIM2, JJ_ENABLE);
	jj_TIM2_5_init(&TIM2);
	ENBL_TIM2_5_IRQ(TIM2_IRQnr);
	jj_TIM2_5_Enable(JJ_pTIM2, JJ_ENABLE);
}

void pin_btnstm32_setup(void) {

	jj_GPIOx_Handle BTN_GPIO; //PC13
	memset(&BTN_GPIO, 0, sizeof(BTN_GPIO));

	BTN_GPIO.pGPIOx = JJ_pGPIOC;
	BTN_GPIO.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_13;
	BTN_GPIO.GPIO_PinConfig.GPIO_PinMODE = JJ_GPIO_MODE_IN;//JJ_GPIO_MODE_IRQ_RE;
	BTN_GPIO.GPIO_PinConfig.GPIO_PinPuPd = JJ_GPIO_PULL_UP;
	jj_GPIO_clk_cntr(JJ_pGPIOC, JJ_ENABLE);
	jj_GPIO_Init(&BTN_GPIO);

	jj_GPIOx_Handle BTNo_GPIO; //PA5, PA6, PA7, PA9
	memset(&BTNo_GPIO, 0, sizeof(BTNo_GPIO));

	BTNo_GPIO.pGPIOx = JJ_pGPIOA;
	BTNo_GPIO.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_5;
	BTNo_GPIO.GPIO_PinConfig.GPIO_PinMODE = JJ_GPIO_MODE_IN;//JJ_GPIO_MODE_IRQ_RE;
	BTNo_GPIO.GPIO_PinConfig.GPIO_PinPuPd = JJ_GPIO_PULL_UP;
	jj_GPIO_clk_cntr(JJ_pGPIOA, JJ_ENABLE);
	jj_GPIO_Init(&BTNo_GPIO);
	BTNo_GPIO.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_6;
	jj_GPIO_Init(&BTNo_GPIO);
	BTNo_GPIO.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_7;
	jj_GPIO_Init(&BTNo_GPIO);
	BTNo_GPIO.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_9;
	jj_GPIO_Init(&BTNo_GPIO);

	//IRQ config
//	jj_IRQnr_Config(JJ_EXTI10_15_IRQ_NR, JJ_ENABLE);
//	jj_IRQ_Priority(JJ_PIN_13, 5);
//	jj_IRQ_Handling(JJ_EXTI10_15_IRQ_NR);
}
