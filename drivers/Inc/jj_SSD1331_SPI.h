/*
 * jj_SSD1331_SPI.h
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#ifndef INC_JJ_SSD1331_SPI_H_
#define INC_JJ_SSD1331_SPI_H_

#include "jj_stm32f401_SPI.h"
#include <string.h>
#include <stdlib.h>

void SPI2_init(void);
void _SPI_TX(uint8_t data);
void _dc(uint8_t en_dis);
void _rst(uint8_t en_dis);
void _SPI_TX_BUF(uint8_t *buf, uint32_t size);


#endif /* INC_JJ_SSD1331_SPI_H_ */
