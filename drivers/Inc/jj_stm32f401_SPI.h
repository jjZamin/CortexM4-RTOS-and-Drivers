/*
 * jj_stm32f401_SPI.h
 *
 *  Created on: 18 Aug 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#ifndef INC_JJ_STM32F401_SPI_H_
#define INC_JJ_STM32F401_SPI_H_

#include "jj_Addresses.h"

/*################################################# [SPI] #################################################*/

typedef struct {
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t CRCPR;
	volatile uint32_t RXCRCR;
	volatile uint32_t TXCRCR;
} jj_SPI_Registers;

#define JJ_pSPI1							((jj_SPI_Registers*)JJ_BASEADDR_SPI1)
#define JJ_pSPI2							((jj_SPI_Registers*)JJ_BASEADDR_SPI2)
#define JJ_pSPI3							((jj_SPI_Registers*)JJ_BASEADDR_SPI3)

/*------SPI CLOCKs----*/
#define JJ_SPI1_CLK_EN()						(JJ_RCC -> APB2ENR |= (1 << 12))
#define JJ_SPI2_CLK_EN()						(JJ_RCC -> APB1ENR |= (1 << 14))
#define JJ_SPI3_CLK_EN()						(JJ_RCC -> APB1ENR |= (1 << 15))

#define JJ_SPI1_CLK_DIS()						(JJ_RCC -> APB2ENR &= ~(1 << 12))
#define JJ_SPI2_CLK_DIS()						(JJ_RCC -> APB1ENR &= ~(1 << 14))
#define JJ_SPI3_CLK_DIS()						(JJ_RCC -> APB1ENR &= ~(1 << 15))

#define JJ_SPI1_RST()						do { (JJ_RCC -> APB2RSTR |= (1 << 12)); (JJ_RCC -> APB2RSTR &= ~(1 << 12)); } while(0)
#define JJ_SPI2_RST()						do { (JJ_RCC -> APB1RSTR |= (1 << 14)); (JJ_RCC -> APB1RSTR &= ~(1 << 14)); } while(0)
#define JJ_SPI3_RST()						do { (JJ_RCC -> APB1RSTR |= (1 << 15)); (JJ_RCC -> APB1RSTR &= ~(1 << 15)); } while(0)

/*------- BIT POSITION DEFINITIONS OF SPI REGISTER CR1 ----------*/
#define SPI_CR1_CPHA				0
#define SPI_CR1_CPOL				1
#define SPI_CR1_MSTR				2
#define SPI_CR1_BR					3
#define SPI_CR1_SPE					6
#define SPI_CR1_LSBFIRST			7
#define SPI_CR1_SSI					8
#define SPI_CR1_SSM					9
#define SPI_CR1_RXONLY				10
#define SPI_CR1_DFF					11
#define SPI_CR1_BIDIMODE			15

/*------- BIT POSITION DEFINITIONS OF SPI REGISTER CR2 ----------*/
#define SPI_CR2_RXDMAEN				0
#define SPI_CR2_TXDMAEN				1
#define SPI_CR2_SSOE				2
#define SPI_CR2_FRF					4
#define SPI_CR2_ERRIE				5
#define SPI_CR2_RXNEIE				6
#define SPI_CR2_TXEIE				7

/*------- BIT POSITION DEFINITIONS OF SPI REGISTER SR -----------*/
#define SPI_SR_RXNE					0
#define SPI_SR_TXE					1
#define SPI_SR_CHSIDE				2
#define SPI_SR_UDR					3
#define SPI_SR_CRCERR				4
#define SPI_SR_MODF					5
#define SPI_SR_OVR					6
#define SPI_SR_BSY					7
#define SPI_SR_FRE					8

/*-- flags --*/
#define SPI_SR_TXE_FLAG				(1 << SPI_SR_TXE)
#define SPI_SR_RXNE_FLAG			(1 << SPI_SR_RXNE)
#define SPI_SR_BUSY_FLAG			(1 << SPI_SR_BSY)

/*IRQ*/
#define SPI1_IRQ_NR					35
#define SPI2_IRQ_NR					36
#define SPI3_IRQ_NR					51

/*SPI CONFIGURATION*/
typedef struct {
	uint8_t SPI_device_mode;
	uint8_t SPI_bus_config;
	uint8_t SPI_Sclk_speed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;
} jj_SPI_Config;

/*
 * @SPI_device_mode
 * */
#define SPI_MODE_MASTER						1
#define SPI_MODE_SLAVE						0

/*
 * @SPI_bus_config
 * */
#define SPI_BUS_FULL_DUPLEX					1
#define SPI_BUS_HALF_DUPLEX					2
#define SPI_BUS_SIMPLEX_RX_ONLY				3

/*
 * @SPI_Sclk_speed
 * */
#define SPI_SCLK_DIV2						0
#define SPI_SCLK_DIV4						1
#define SPI_SCLK_DIV8						2
#define SPI_SCLK_DIV16						3
#define SPI_SCLK_DIV32						4
#define SPI_SCLK_DIV64						5
#define SPI_SCLK_DIV128						6
#define SPI_SCLK_DIV256						7

/*
 * @SPI_DFF
 * */
#define SPI_8BIT							0
#define SPI_16BIT							1

/*
 * @SPI_CPOL, @SPI_CPHA
 * */
#define SPI_CPOL_HIGH						1
#define SPI_CPOL_LOW						0
#define SPI_CPHA_ON_RISING					1
#define SPI_CPHA_ON_FALLING					0

/*
 * @SPI_SSM
 * */
#define SPI_SSM_EN							1
#define SPI_SSM_DIS							0

/*-------------------------------------------------------------------*/


/*SPI handler*/
typedef struct {
	/*base addr for gpio periph*/
	jj_SPI_Registers *pSPIx;
	jj_SPI_Config SPI_PinConfig;

}jj_SPIx_Handle;


/*prototypes*/
void jj_SPI_Init(jj_SPIx_Handle *pHandle);
void jj_SPI_DeInit(jj_SPI_Registers *pSPI);
void jj_SPI_clk_cntr(jj_SPI_Registers *pSPI, uint8_t En_Dis);
void jj_SPI_TX(jj_SPI_Registers *pSPI, uint8_t *pTxBuffer, uint32_t length);
void jj_SPI_RX(jj_SPI_Registers *pSPI, uint8_t *pRxBuffer, uint32_t length);
void jj_SPI_IRQnr_Config(uint8_t IRQnr, uint8_t En_Dis);
void jj_SPI_IRQ_Priority(uint8_t IRQnr, uint32_t IRQpriority);
void jj_SPI_IRQ_Handling(jj_SPIx_Handle *pHandle);
void jj_SPI_SSI(jj_SPI_Registers *pSPI, uint8_t En_Dis);
void jj_SPI_SSOE(jj_SPI_Registers *pSPI, uint8_t En_Dis); //for hardware NSS, SSM = 0, SSOE = 1
void jj_SPI_ENABLE(jj_SPI_Registers *pSPI, uint8_t En_Dis);


/*##################################################################################################################*/


#endif /* INC_JJ_STM32F401_SPI_H_ */
