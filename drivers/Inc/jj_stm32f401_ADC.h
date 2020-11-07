/*
 * jj_stm32f401_ADC.h
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#ifndef INC_JJ_STM32F401_ADC_H_
#define INC_JJ_STM32F401_ADC_H_

#include "jj_Addresses.h"


/*ADC CONFIGURATION*/
typedef struct {
	uint8_t channel;
	uint8_t conversion_mode;
	uint8_t resolution;
} jj_ADC_Config;


/*  config for user  */
#define CONV_MODE_SINGLE			0
#define CONV_MODE_CONT				1

#define RESOL_12BIT					0
#define RESOL_10BIT					1
#define RESOL_8BIT					2
#define RESOL_6BIT					3

#define ADC_CH0						0		//PA0
#define ADC_CH1						1		//PA1
#define ADC_CH2						2		//PA2
#define ADC_CH3						3		//PA3
#define ADC_CH4						4		//PA4
#define ADC_CH5						5		//PA5
#define ADC_CH6						6
#define ADC_CH7						7
#define ADC_CH8						8
#define ADC_CH9						9
#define ADC_CH10					10
#define ADC_CH11					11
#define ADC_CH12					12
#define ADC_CH13					13
#define ADC_CH14					14
#define ADC_CH15					15
#define ADC_CH16					16
#define ADC_CH17					17
#define ADC_CH18					18
/*-------------------*/
#define ADC_CR2_ADON				(1 << 0)
#define ADC_C2_SWSTART				(1 << 30)
#define ADC_CR1_AWDEN				(1 << 23)


void jj_ADC_Init(jj_ADC_Config config);
void jj_ADC_ENABLE(uint8_t en_dis);
void jj_ADC_CLK_EN(uint8_t en_dis);
uint16_t jj_ADC_READ(void);
void jj_ADC_START_NEW_CONV(void);

typedef struct {
	volatile uint32_t SR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SMPR1;
	volatile uint32_t SMPR2;
	volatile uint32_t JOFR1;
	volatile uint32_t JOFR2;
	volatile uint32_t JOFR3;
	volatile uint32_t JOFR4;
	volatile uint32_t HTR;
	volatile uint32_t LTR;
	volatile uint32_t SQR1;
	volatile uint32_t SQR2;
	volatile uint32_t SQR3;
	volatile uint32_t JSQR;
	volatile uint32_t JDR1;
	volatile uint32_t JDR2;
	volatile uint32_t JDR3;
	volatile uint32_t JDR4;
	volatile uint32_t DR;

} jj_ADC_Registers;


#define JJ_pADC1								((jj_ADC_Registers*)JJ_BASEADDR_ADC1)

#define JJ_ADC1_CLK_EN()						(JJ_RCC -> APB2ENR |= (1 << 8))
#define JJ_ADC1_CLK_DIS()						(JJ_RCC -> APB2ENR &= ~(1 << 8))


#endif /* INC_JJ_STM32F401_ADC_H_ */
