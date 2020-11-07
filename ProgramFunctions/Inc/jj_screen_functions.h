/*
 * jj_screen_functions.h
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#ifndef INC_JJ_SCREEN_FUNCTIONS_H_
#define INC_JJ_SCREEN_FUNCTIONS_H_

#include <stdint.h>
#include "jj_SSD1331_driver.h"

/*ADC*/
volatile uint16_t adc_read_value;
volatile uint16_t adc_read_value_buffer;
volatile uint8_t adc_flag;
volatile uint8_t timer_flag;

volatile uint32_t adc_count;
/*---*/

volatile uint8_t _x_pos;
volatile uint8_t _y_pos;

void _draw_plot_(void);
void _draw_intro(void);
void _draw_coord(void);
void _curtain_close(uint32_t speed);

#define ALL_IRQ_DIS()				do{__asm volatile ("MOV R0, #0x01"); __asm volatile ("MSR PRIMASK, R0"); } while(0)
#define ALL_IRQ_EN()				do{__asm volatile ("MOV R0, #0x00"); __asm volatile ("MSR PRIMASK, R0"); } while(0)



#endif /* INC_JJ_SCREEN_FUNCTIONS_H_ */
