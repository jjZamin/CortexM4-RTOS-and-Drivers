/*
 * jj_stm32f401_GPIO.c
 *
 *  Created on: 18 Aug 2020
 *      Author: jj.Zamin (G.Mazin)
 */


#include "jj_stm32f401_GPIO.h"

void jj_GPIO_Init(jj_GPIOx_Handle *pHandle) {

	uint32_t temp = 0;
	//MODE--------
	/*---non interrupt mode---*/

	/*
	 * If GPIO_MODE is less or equal to analog (4), then it's non interrupt mode
	 * */
	if(pHandle -> GPIO_PinConfig.GPIO_PinMODE <= JJ_GPIO_MODE_ANLG) {

		/*
		 * Shift the chosen PIN MODE in Handle struct number of pins to left
		 * so if MODE = b'11' for Pin 2, 00000000000000000000000000000011 << 2*2 ---> temp = 00000000000000000000000000110000.
		 *
		 * */
		temp = pHandle -> GPIO_PinConfig.GPIO_PinMODE << (2 * pHandle -> GPIO_PinConfig.GPIO_PinNr);

		/*
		 * In pHandle, take the base address of the pin and offset it (MODER = Offset by 0, as it's the first value in the struct and so
		 * it points directly to the base address of the pin) - so store TEMP (MODER @PINx) in address pointed by tje pHandle->pGPIOx->MODER pointer
		 * */
		pHandle->pGPIOx->MODER &= ~(0x3 << (pHandle -> GPIO_PinConfig.GPIO_PinNr * 2)); //clear
		pHandle->pGPIOx->MODER |= temp; //set
	}
	else {
		/*---IRQ mode---*/

		if(pHandle -> GPIO_PinConfig.GPIO_PinMODE == JJ_GPIO_MODE_IRQ_FE) {
			//1) FTSR register, p.210 //falling edge
			JJ_EXTI->FTSR |= (1 << pHandle -> GPIO_PinConfig.GPIO_PinNr);
			JJ_EXTI->RTSR &= ~(1 << pHandle -> GPIO_PinConfig.GPIO_PinNr); //just in case, reset the RTSR
		}
		else if(pHandle -> GPIO_PinConfig.GPIO_PinMODE == JJ_GPIO_MODE_IRQ_RE) {
			//1) RTSR register, p.210 //rising edge
			JJ_EXTI->RTSR |= (1 << pHandle -> GPIO_PinConfig.GPIO_PinNr);
			JJ_EXTI->FTSR &= ~(1 << pHandle -> GPIO_PinConfig.GPIO_PinNr);
		}
		else if(pHandle -> GPIO_PinConfig.GPIO_PinMODE == JJ_GPIO_MODE_IRQ_FRE) {
			//1) RTSR+FTSR register, p.210 //both edges
			JJ_EXTI->FTSR |= (1 << pHandle -> GPIO_PinConfig.GPIO_PinNr);
			JJ_EXTI->RTSR |= (1 << pHandle -> GPIO_PinConfig.GPIO_PinNr); //just in case, reset the RTSR

		}

		//2) GPIO port, SYSCFG_EXTICR, p.142
		uint8_t extix = (pHandle -> GPIO_PinConfig.GPIO_PinNr) / 4;		//which one of the EXTI(1-4) regs to chose from based on the PIN NR
		uint8_t extipin = (pHandle -> GPIO_PinConfig.GPIO_PinNr) % 4;	//which field to fill out (*4 because 4 bits)
		uint8_t EXTI_code = JJ_BASEADDR_GPIO_TO_4bitCODE(pHandle -> pGPIOx);

		JJ_SYSCFG_CLK_EN();
		JJ_SYSCFG -> EXTICR[extix] |= (EXTI_code << (extipin * 4));

		//3) Enable exti interrupt delivery, IMR, p.209
		JJ_EXTI->IMR |= (1 << pHandle -> GPIO_PinConfig.GPIO_PinNr);
	}

	//SPEED--------
	temp = 0;
	temp = pHandle -> GPIO_PinConfig.GPIO_PinSPEED << (2 * pHandle -> GPIO_PinConfig.GPIO_PinNr);
	pHandle->pGPIOx->OSPEEDR &= ~(0x3 << (pHandle -> GPIO_PinConfig.GPIO_PinNr * 2)); //clear
	pHandle -> pGPIOx -> OSPEEDR |= temp;
	//Pull up pull down-------
	temp = 0;
	temp = pHandle -> GPIO_PinConfig.GPIO_PinPuPd << (2 * pHandle -> GPIO_PinConfig.GPIO_PinNr);
	pHandle->pGPIOx-> PUPDR &= ~(0x3 << (pHandle -> GPIO_PinConfig.GPIO_PinNr * 2)); //clear
	pHandle -> pGPIOx -> PUPDR |= temp;
	//Output type
	temp = 0;
	temp = pHandle -> GPIO_PinConfig.GPIO_PinOutPutType << (pHandle -> GPIO_PinConfig.GPIO_PinNr);
	pHandle->pGPIOx->OTYPER &= ~(0x01 << (pHandle -> GPIO_PinConfig.GPIO_PinNr)); //clear
	pHandle -> pGPIOx -> OTYPER |= temp;
	//Alt functionality, 2 register 1: PIN0 - PIN7, register 2: PIN8 - PIN15
	temp = 0;
	if(pHandle -> GPIO_PinConfig.GPIO_PinMODE == JJ_GPIO_MODE_AF) {
		volatile uint32_t AFreg_nr = (pHandle -> GPIO_PinConfig.GPIO_PinNr) / 8;
		volatile uint32_t fieled_nr = (pHandle -> GPIO_PinConfig.GPIO_PinNr) % 8;
		pHandle -> pGPIOx -> AFR[AFreg_nr] |= (pHandle -> GPIO_PinConfig.GPIO_AltFunct << (4 * fieled_nr));
	}
}

void jj_GPIO_DeInit(jj_GPIO_Registers *pGPIOx) {

	if(pGPIOx == JJ_pGPIOA) {
		JJ_GPIOA_RST();
	}
	else if(pGPIOx == JJ_pGPIOB) {
		JJ_GPIOB_RST();
	}
	else if(pGPIOx == JJ_pGPIOC) {
		JJ_GPIOC_RST();
	}
	else if(pGPIOx == JJ_pGPIOD) {
		JJ_GPIOD_RST();
	}
	else if(pGPIOx == JJ_pGPIOE) {
		JJ_GPIOE_RST();
	}
	else if(pGPIOx == JJ_pGPIOH) {
		JJ_GPIOH_RST();
	}
}


/*
 * Enable/Disable clock for any give port.
 * @arg1: JJ_GPIOx (x = A,B,C,D,E,H)
 * @arg2: ENABLE/DISABLE
 *
 * */
void jj_GPIO_clk_cntr(jj_GPIO_Registers *pGPIOx, uint8_t En_Dis) {

	if(En_Dis == JJ_ENABLE) {
		if(pGPIOx == JJ_pGPIOA) {
			JJ_GPIOA_CLK_EN();
		}
		else if(pGPIOx == JJ_pGPIOB) {
			JJ_GPIOB_CLK_EN();
		}
		else if(pGPIOx == JJ_pGPIOC) {
			JJ_GPIOC_CLK_EN();
		}
		else if(pGPIOx == JJ_pGPIOD) {
			JJ_GPIOD_CLK_EN();
		}
		else if(pGPIOx == JJ_pGPIOE) {
			JJ_GPIOE_CLK_EN();
		}
		else if(pGPIOx == JJ_pGPIOH) {
			JJ_GPIOH_CLK_EN();
		}
	}
	else {
		if(pGPIOx == JJ_pGPIOA) {
			JJ_GPIOA_CLK_DIS();
		}
		else if(pGPIOx == JJ_pGPIOB) {
			JJ_GPIOB_CLK_DIS();
		}
		else if(pGPIOx == JJ_pGPIOC) {
			JJ_GPIOC_CLK_DIS();
		}
		else if(pGPIOx == JJ_pGPIOD) {
			JJ_GPIOD_CLK_DIS();
		}
		else if(pGPIOx == JJ_pGPIOE) {
			JJ_GPIOE_CLK_DIS();
		}
		else if(pGPIOx == JJ_pGPIOH) {
			JJ_GPIOH_CLK_DIS();
		}
	}
}

/*
 * read pin
 * */

uint8_t jj_GPIO_rdPin(jj_GPIO_Registers *pGPIO, uint8_t pinNr) {

	uint8_t value = 0;
	value = (uint8_t) ((pGPIO -> IDR >> pinNr) & 0x00000001); //to get the pinNr bit out of the register, as it's binary - shift the desired pin to zero'th bit.
	return value;
}

/*
 * read port
 * */

uint16_t jj_GPIO_rdPort(jj_GPIO_Registers *pGPIO) {

	uint16_t value = 0;

	value = (uint16_t) ((pGPIO -> IDR));

	return value;
}


void jj_GPIO_wrToPin(jj_GPIO_Registers *pGPIO, uint8_t pinNr, uint8_t value) {

	if(value == JJ_SET) {
		pGPIO -> ODR |= (1 << pinNr);
	}
	else {
		pGPIO -> ODR &= ~(1 << pinNr);
	}
}


void jj_GPIO_wrToPort(jj_GPIO_Registers *pGPIO, uint8_t pinNr, uint16_t value) {

	pGPIO -> ODR = value;
}


void jj_Toggle_Pin(jj_GPIO_Registers *pGPIO, uint8_t pinNr) {

	pGPIO -> ODR ^= (1 << pinNr);
}


void jj_IRQnr_Config(uint8_t IRQnr, uint8_t En_Dis) {


	//cortex-m4 generic user manual
	if(En_Dis == JJ_ENABLE) { //enable

		if(IRQnr <= 31) {
			//ISER0, p.4-3
			*JJ_ADDR_ISER0 |= (1 << IRQnr);
		}
		else if(IRQnr > 31 && IRQnr <= 63) {
			//ISER1
			*JJ_ADDR_ISER1 |= (1 << (IRQnr % 32));

		}
		else if(IRQnr > 63 && IRQnr <= 95) {
			//ISER2
			*JJ_ADDR_ISER2 |= (1 << (IRQnr % 64));
		}
	}
	else {					//disable

		if(IRQnr <= 31) {
			//ICER0, p.4-3
			*JJ_ADDR_ICER0 |= (1 << IRQnr);

		}
		else if(IRQnr > 31 && IRQnr <= 63) {
			//ICER1
			*JJ_ADDR_ICER1 |= (1 << (IRQnr % 32));
		}
		else if(IRQnr > 63 && IRQnr <= 95) {
			//ICER2
			*JJ_ADDR_ICER2 |= (1 << (IRQnr % 64));
		}
	}
}

void jj_IRQ_Handling(uint8_t pinNr) {

	//if pending bit is set, reset it (set it to 1 which is reset in PR register for EXTIx)
	if((JJ_EXTI -> PR) & (1 << pinNr)) {
		JJ_EXTI -> PR |= (1 << pinNr);
	}
}
