/*
 * jj_inits.h
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#ifndef INC_JJ_INITS_H_
#define INC_JJ_INITS_H_

#include "jj_stm32f401_GPIO.h"
#include "jj_stm32f401_ADC.h"
#include "jj_stm32f401_TIM2_5.h"
#include <string.h>

void ADC_init(void);
void TIM2_init(uint32_t PRESCLR, uint32_t count_to);
void pin_btnstm32_setup(void);

#endif /* INC_JJ_INITS_H_ */
