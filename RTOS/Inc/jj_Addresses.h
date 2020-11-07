/*
 * jj_Addresses.h
 *
 *  Created on: Aug 18, 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#ifndef INC_JJ_ADDRESSES_H_
#define INC_JJ_ADDRESSES_H_

#include <stdint.h>

/*############################################ [KERNAL] ############################################*/

/*--- SRAM ---*/
#define SRAM_START_ADDR					0x20000000U //p.42, refman
#define SRAM_END_ADDR					0x20018000U
/*------------*/

/*---SYSTICK---*/
#define SYSTICK_CSR_ADDR				0xE000E010	//4-33 DUI
#define SYSTICK_RELOADVAL_ADDR			0xE000E014
/*-------------*/

/*---System Handler Control and State Register: DUI---*/
#define SHCRS_ADDR					0xE000ED24
/*----------------------------------------------------*/

/*---pendSV: DUI---*/
#define ICSR_ADDR					0xE000ED04U
/*-----------------*/
/*##################################################################################################*/

/*----------------------------------[START: BUSDOMAINS base addresses]----------------------------------*/
//peripheral base address (0x40000000)

#define JJ_BASEADDR_APB1PERIPH				0x40000000U				//p39 refman
#define JJ_BASEADDR_APB2PERIPH				0x40010000U
#define JJ_BASEADDR_AHB1PERIPH				0x40020000U
#define JJ_BASEADDR_AHB2PERIPH				0x50000000U
/*----------------------------------[END: BUSDOMAINS base addresses]----------------------------------*/

/*SYSTEM CONFIG, EXTERNAL IRQ*/
#define JJ_BASEADDR_EXTI					(JJ_BASEADDR_APB2PERIPH + 0x3C00U)
#define JJ_BASEADDR_SYSCFG					(JJ_BASEADDR_APB2PERIPH + 0x3800U)

/*############################################ [GPIO] ##############################################*/
// AHB1, p38  refman
#define JJ_BASEADDR_GPIOA					(JJ_BASEADDR_AHB1PERIPH + 0x0000U)
#define JJ_BASEADDR_GPIOB					(JJ_BASEADDR_AHB1PERIPH + 0x0400U)
#define JJ_BASEADDR_GPIOC					(JJ_BASEADDR_AHB1PERIPH + 0x0800U)
#define JJ_BASEADDR_GPIOD					(JJ_BASEADDR_AHB1PERIPH + 0x0C00U)
#define JJ_BASEADDR_GPIOE					(JJ_BASEADDR_AHB1PERIPH + 0x1000U)
#define JJ_BASEADDR_GPIOH					(JJ_BASEADDR_AHB1PERIPH + 0x1C00U)
#define JJ_BASEADDR_RCC						(JJ_BASEADDR_AHB1PERIPH + 0x3800U)

/*baseaddr for ISERx registers 0-2 [processor specific]*/
#define JJ_ADDR_ISER0					((volatile uint32_t*)0xE000E100) //IRQ enable regs
#define JJ_ADDR_ISER1					((volatile uint32_t*)0xE000E104)
#define JJ_ADDR_ISER2					((volatile uint32_t*)0xE000E108)

#define JJ_ADDR_ICER0					((volatile uint32_t*)0xE000E180) //IRQ disable regs
#define JJ_ADDR_ICER1					((volatile uint32_t*)0xE000E184)
#define JJ_ADDR_ICER2					((volatile uint32_t*)0xE000E188)

#define JJ_ADDR_ICPR0					((volatile uint32_t*)0xE000E280)

#define JJ_ADDR_IPR0					((volatile uint32_t*)0xE000E400) //IRQ priority regs
#define JJ_ADDR_IPR1					((volatile uint32_t*)0xE000E404)
#define JJ_ADDR_IPR2					((volatile uint32_t*)0xE000E408)
#define JJ_ADDR_IPR3					((volatile uint32_t*)0xE000E40C)

/*Vector addresses (RAM address where the IRQ Rutine address is stored*/
#define JJ_ADDR_EXTI0_VEC				0x00000058
#define JJ_ADDR_EXTI1_VEC				0x0000005C
#define JJ_ADDR_EXTI2_VEC				0x00000060
#define JJ_ADDR_EXTI3_VEC				0x00000064
#define JJ_ADDR_EXTI4_VEC				0x00000068
#define JJ_ADDR_EXTI9_5_VEC				0x0000009C
#define JJ_ADDR_EXTI10_15_VEC			0x000000E0

/*################################################# [SPI] #################################################*/
#define JJ_BASEADDR_SPI1					(JJ_BASEADDR_APB2PERIPH + 0x3000U)
#define JJ_BASEADDR_SPI2					(JJ_BASEADDR_APB1PERIPH + 0x3800U)
#define JJ_BASEADDR_SPI3					(JJ_BASEADDR_APB1PERIPH + 0x3C00U)

/*#############################################  TIMERS 2 - 5  #####################################################*/
#define JJ_BASEADDR_TIM2			0x40000000U
#define JJ_BASEADDR_TIM3			0x40000400U
#define JJ_BASEADDR_TIM4			0x40000800U
#define JJ_BASEADDR_TIM5			0x40000C00U

/*#############################################  ADC  #####################################################*/
#define JJ_BASEADDR_ADC1						0x40012000U
#define JJ_ADC_CCR_REG							((volatile uint32_t*)(JJ_BASEADDR_ADC1 + 0x300U + 0x04U))


/* RCC STRUCTURE */
/*-----RCC REGISTER-----*/
typedef struct {
	volatile uint32_t CR;				//0x00
	volatile uint32_t PLLCFGR;			//0x04
	volatile uint32_t CFGR;				//0x08
	volatile uint32_t CIR;				//0x0C
	volatile uint32_t AHB1RSTR;			//0x10
	volatile uint32_t AHB2RSTR;			//0x14
	uint32_t RSVDREG1;					//0x18
	uint32_t RSVDREG2;					//0x1C
	volatile uint32_t APB1RSTR;			//0x20
	volatile uint32_t APB2RSTR; 		//0x24
	uint32_t RSVDREG3;					//0x28
	uint32_t RSVDREG4;					//0x2C
	volatile uint32_t AHB1ENR;			//0x30
	volatile uint32_t AHB2ENR;			//0x34
	uint32_t RSVDREG5;					//0x38
	uint32_t RSVDREG6;					//0x3C
	volatile uint32_t APB1ENR;			//0x40
	volatile uint32_t APB2ENR;			//0x44
	uint32_t RSVDREG7;					//0x48
	uint32_t RSVDREG8;					//0x4C
	volatile uint32_t AHB1LPENR;		//0x50
	volatile uint32_t AHB2LPENR;		//0x54
	uint32_t RSVDREG9;					//0x58
	uint32_t RSVDREG10;					//0x5C
	volatile uint32_t APB1LPENR;		//0x60
	volatile uint32_t APB2LPENR;		//0x64
	uint32_t RSVDREG11;					//0x68
	uint32_t RSVDREG12;					//0x6C
	volatile uint32_t BDCR;				//0x70
	volatile uint32_t CSR;				//0x74
	uint32_t RSVDREG13;					//0x78
	uint32_t RSVDREG14;					//0x7C
	volatile uint32_t SSCGR;			//0x80
	volatile uint32_t PLLI2SCFGR;		//0x84
	uint32_t RSVDREG15;					//0x88
	volatile uint32_t DCKCFGR;			//0x8C
} jj_RCC_Registers;
#define JJ_RCC									((jj_RCC_Registers*)JJ_BASEADDR_RCC)
/*---- IRQ EXTI ----*/

/*IRQ numbers*/
#define JJ_EXTI0_IRQ_NR						6
#define JJ_EXTI1_IRQ_NR						7
#define JJ_EXTI2_IRQ_NR						8
#define JJ_EXTI3_IRQ_NR						9
#define JJ_EXTI4_IRQ_NR						10
#define JJ_EXTI9_5_IRQ_NR					23
#define JJ_EXTI10_15_IRQ_NR					40

typedef struct {
	volatile uint32_t IMR;
	volatile uint32_t EMR;
	volatile uint32_t RTSR;
	volatile uint32_t FTSR;
	volatile uint32_t SWIER;
	volatile uint32_t PR;
} jj_EXTI_Registers;
#define JJ_EXTI									((jj_EXTI_Registers*)JJ_BASEADDR_EXTI)

/*---- SYS CONFIG ----*/
typedef struct {
	volatile uint32_t MEMRPM;
	volatile uint32_t PMC;
	volatile uint32_t EXTICR[4];
	uint32_t RSVDREG1;					//0x18
	uint32_t RSVDREG2;					//0x18
	volatile uint32_t CMPCR;
} jj_SYSCFG_Registers;
#define JJ_SYSCFG								((jj_SYSCFG_Registers*)JJ_BASEADDR_SYSCFG)

/*------SYSCONFIG----*/
#define JJ_SYSCFG_CLK_EN()						(JJ_RCC -> APB2ENR |= (1 << 14))
#define JJ_SYSCFG_CLK_DIS()						(JJ_RCC -> APB2ENR &= ~(1 << 14))

/*----------------------------------[START: GENERIC MACROS]----------------------------------*/
#define JJ_ENABLE 									1
#define JJ_DISABLE 									0
#define JJ_SET										JJ_ENABLE
#define JJ_RESET									JJ_DISABLE
#define FLAG_IS_SET									1
#define FLAG_IS_RESET								0
/*----------------------------------[END: GENERIC MACROS]----------------------------------*/


#endif /* INC_JJ_ADDRESSES_H_ */
