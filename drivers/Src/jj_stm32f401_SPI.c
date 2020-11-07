/*
 * jj_stm32f401_SPI.c
 *
 *  Created on: 18 Aug 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#include "jj_stm32f401_SPI.h"

void jj_SPI_Init(jj_SPIx_Handle *pHandle) {

	uint32_t CR1 = 0;

	//mode

	//bus config
	if(pHandle->SPI_PinConfig.SPI_bus_config == SPI_BUS_FULL_DUPLEX) {
		CR1 &= ~(1 << SPI_CR1_BIDIMODE);
	}
	else if(pHandle->SPI_PinConfig.SPI_bus_config == SPI_BUS_HALF_DUPLEX) {
		CR1 |= (1 << SPI_CR1_BIDIMODE);
	}
	else if(pHandle->SPI_PinConfig.SPI_bus_config == SPI_BUS_SIMPLEX_RX_ONLY) {
		CR1 &= ~(1 << SPI_CR1_BIDIMODE);
		CR1 |= (1 << SPI_CR1_RXONLY);
	}

	//sclk
	CR1 |= ((pHandle->SPI_PinConfig.SPI_Sclk_speed << SPI_CR1_BR));

	//DFF
	CR1 |= ((pHandle->SPI_PinConfig.SPI_DFF << SPI_CR1_DFF));

	//CPOL
	CR1 |= ((pHandle->SPI_PinConfig.SPI_CPOL << SPI_CR1_CPOL));

	//CPHA
	CR1 |= ((pHandle->SPI_PinConfig.SPI_CPHA << SPI_CR1_CPHA));

	//SSM
	CR1 |= ((pHandle->SPI_PinConfig.SPI_SSM << SPI_CR1_SSM));

	//mode
	CR1 |= ((pHandle->SPI_PinConfig.SPI_device_mode << SPI_CR1_MSTR)); //second bit in CR1 register for SPI p.602 refman


	pHandle->pSPIx->CR1 = CR1;
}


void jj_SPI_DeInit(jj_SPI_Registers *pSPI) {
	if(pSPI == JJ_pSPI1) {
		JJ_SPI1_RST();
	}
	else if(pSPI == JJ_pSPI2) {
		JJ_SPI2_RST();
	}
	else if(pSPI == JJ_pSPI3) {
		JJ_SPI3_RST();
	}
}
void jj_SPI_clk_cntr(jj_SPI_Registers *pSPI, uint8_t En_Dis) {

	if(En_Dis == JJ_ENABLE) {
		if(pSPI == JJ_pSPI1) {
			JJ_SPI1_CLK_EN();
		}
		else if(pSPI == JJ_pSPI2) {
			JJ_SPI2_CLK_EN();
		}
		else if(pSPI == JJ_pSPI3) {
			JJ_SPI3_CLK_EN();
		}
	}
	else {
		if(pSPI == JJ_pSPI1) {
			JJ_SPI1_CLK_DIS();
		}
		else if(pSPI == JJ_pSPI2) {
			JJ_SPI2_CLK_DIS();
		}
		else if(pSPI == JJ_pSPI3) {
			JJ_SPI3_CLK_DIS();
		}
	}
}


/*read SR flags*/
uint8_t SPI_get_SR_flag(jj_SPI_Registers *pSPI, uint8_t flag_name) {

	if((pSPI->SR & flag_name)) {
		return FLAG_IS_SET;
	}
	return FLAG_IS_RESET;
}

/*a blocking call ~polling type*/
void jj_SPI_TX(jj_SPI_Registers *pSPI, uint8_t *pTxBuffer, uint32_t length) {

	while(length > 0) {
		//wait for TXE
		while(SPI_get_SR_flag(pSPI, SPI_SR_TXE_FLAG) == FLAG_IS_RESET);

		//check the dff bit
		if(pSPI->CR1 & (1 << SPI_CR1_DFF)) {
			//16 bit
			pSPI->DR = *((uint16_t*)pTxBuffer);
			length--;
			length--; //twice as 2 bytes are sent at a time
			(uint16_t*)pTxBuffer++;
		}
		else {
			//8 bit
			pSPI->DR = *(pTxBuffer);
			length--;
			pTxBuffer++; //go to next byte.
		}
	}
}
void jj_SPI_RX(jj_SPI_Registers *pSPI, uint8_t *pRxBuffer, uint32_t length) {

	while(length > 0) {
		//wait for RXE
		while(SPI_get_SR_flag(pSPI, SPI_SR_RXNE_FLAG) == FLAG_IS_RESET);

		//check the dff bit
		if(pSPI->CR1 & (1 << SPI_CR1_DFF)) {
			//load data from DR into RX buffer
			*((uint16_t*)pRxBuffer) = pSPI->DR;
			length--;
			length--; //twice as 2 bytes are sent at a time
			(uint16_t*)pRxBuffer++;
		}
		else {
			//8 bit
			*(pRxBuffer) = pSPI->DR;
			length--;
			pRxBuffer++; //go to next byte.
		}
	}
}

void jj_SPI_ENABLE(jj_SPI_Registers *pSPI, uint8_t En_Dis) {
	if(En_Dis == JJ_ENABLE) {
		pSPI->CR1 |= (1 << SPI_CR1_SPE);
	}
	else {
		pSPI->CR1 &= ~(1 << SPI_CR1_SPE);
	}
}

void jj_SPI_SSI(jj_SPI_Registers *pSPI, uint8_t En_Dis) {
	if(En_Dis == JJ_ENABLE) {
		pSPI->CR1 |= (1 << SPI_CR1_SSI);
	}
	else {
		pSPI->CR1 &= ~(1 << SPI_CR1_SSI);
	}
}

void jj_SPI_SSOE(jj_SPI_Registers *pSPI, uint8_t En_Dis) {
	if(En_Dis == JJ_ENABLE) {
		pSPI->CR2 |= (1 << SPI_CR2_SSOE);
	}
	else {
		pSPI->CR2 &= ~(1 << SPI_CR2_SSOE);
	}
}

