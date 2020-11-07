/*
 * jj_SSD1331_SPI.c
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#include "jj_SSD1331_SPI.h"
#include "jj_stm32f401_GPIO.h"

void rst_dc_pins_init(void) {

	//PB1: rst
	//PB2: dc

	jj_GPIOx_Handle rst_dc_PINS;
	memset(&rst_dc_PINS, 0, sizeof(rst_dc_PINS));

	rst_dc_PINS.pGPIOx = JJ_pGPIOB;
	rst_dc_PINS.GPIO_PinConfig.GPIO_PinMODE = JJ_GPIO_MODE_OUT;
	rst_dc_PINS.GPIO_PinConfig.GPIO_PinOutPutType = JJ_GPIO_OUTPUT_PP;
	rst_dc_PINS.GPIO_PinConfig.GPIO_PinPuPd = JJ_GPIO_PULL_DOWN;
	rst_dc_PINS.GPIO_PinConfig.GPIO_PinSPEED = JJ_GPIO_SPEED_HIGH;
	jj_GPIO_clk_cntr(JJ_pGPIOB, JJ_ENABLE);

	//rst [PB1]
	rst_dc_PINS.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_1;
	jj_GPIO_Init(&rst_dc_PINS);

	//dc [PB2]
	rst_dc_PINS.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_2;
	jj_GPIO_Init(&rst_dc_PINS);


}

void SPI2_gpio_init(void) {

	rst_dc_pins_init();

	/*--spi2--*/
	//MOSI: PB15 -> AF05
	//MISO: PB14 -> AF05
	//SCLK: PB13 -> AF05
	//NSS: PB12 -> AF05



	jj_GPIOx_Handle SPI2_PINS; // PC3
	memset(&SPI2_PINS, 0, sizeof(SPI2_PINS));

	SPI2_PINS.pGPIOx = JJ_pGPIOB;
	SPI2_PINS.GPIO_PinConfig.GPIO_PinMODE = JJ_GPIO_MODE_AF;
	SPI2_PINS.GPIO_PinConfig.GPIO_AltFunct = JJ_AF_5;		//p.46, datasheet
	SPI2_PINS.GPIO_PinConfig.GPIO_PinOutPutType = JJ_GPIO_OUTPUT_PP;
	SPI2_PINS.GPIO_PinConfig.GPIO_PinPuPd = JJ_GPIO_PULL_UP;
	SPI2_PINS.GPIO_PinConfig.GPIO_PinSPEED = JJ_GPIO_SPEED_HIGH;
	jj_GPIO_clk_cntr(JJ_pGPIOB, JJ_ENABLE);

	//MOSI [PB15]
	SPI2_PINS.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_15;
	jj_GPIO_Init(&SPI2_PINS);

	//MISO
	//SPI2_PINS.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_14;
	//jj_GPIO_Init(&SPI2_PINS);

	//SCLK [PB13]
	SPI2_PINS.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_13;
	jj_GPIO_Init(&SPI2_PINS);

	//NSS
	//SPI2_PINS.GPIO_PinConfig.GPIO_PinNr = JJ_PIN_12;
	//jj_GPIO_Init(&SPI2_PINS);

}

void SPI2_init(void) {

	SPI2_gpio_init();

	jj_SPIx_Handle SPI2_INIT;
	memset(&SPI2_INIT, 0, sizeof(SPI2_INIT));

	SPI2_INIT.pSPIx = JJ_pSPI2;
	SPI2_INIT.SPI_PinConfig.SPI_device_mode = SPI_MODE_MASTER;
	SPI2_INIT.SPI_PinConfig.SPI_bus_config = SPI_BUS_FULL_DUPLEX;
	SPI2_INIT.SPI_PinConfig.SPI_Sclk_speed = SPI_SCLK_DIV2;
	SPI2_INIT.SPI_PinConfig.SPI_DFF = SPI_8BIT;
	SPI2_INIT.SPI_PinConfig.SPI_CPOL = SPI_CPOL_HIGH;
	SPI2_INIT.SPI_PinConfig.SPI_CPHA = SPI_CPHA_ON_RISING;
	SPI2_INIT.SPI_PinConfig.SPI_SSM = SPI_SSM_EN;
	jj_SPI_clk_cntr(JJ_pSPI2, JJ_ENABLE);
	jj_SPI_Init(&SPI2_INIT);
	jj_SPI_SSI(JJ_pSPI2, JJ_ENABLE);
	jj_SPI_ENABLE(JJ_pSPI2, JJ_ENABLE);
}

void _SPI_TX(uint8_t data) {
	jj_SPI_TX(JJ_pSPI2, &data, 1);
}

void _SPI_TX_BUF(uint8_t *buf, uint32_t size) {
	jj_SPI_TX(JJ_pSPI2, buf, size);
}

void _dc(uint8_t en_dis) {
	jj_GPIO_wrToPin(JJ_pGPIOB, JJ_PIN_2, en_dis);
}

void _rst(uint8_t en_dis) {
	jj_GPIO_wrToPin(JJ_pGPIOB, JJ_PIN_1, en_dis);
}
