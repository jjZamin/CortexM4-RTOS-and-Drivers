/*
 * jj_screen_functions.c
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#include "jj_screen_functions.h"

/*ADC*/
volatile uint16_t adc_read_value = 0;
volatile uint16_t adc_read_value_buffer = 0;
volatile uint8_t adc_flag = 0;

/*---*/

volatile uint8_t _x_pos = 5;
volatile uint8_t _y_pos = 50;


void _draw_coord(void) {
	_scr_draw_line(2, (4096/100+17), 2, (15), 0xABCD);
	_scr_draw_line(2, (4096/100+17), 90, (4096/100+17), 0xABCD);
	_scr_write_text(0, 4, "3.3V", 0x3CF5);
	_scr_draw_line(0, (4096/50+17), 4, (4096/50+17), 0xFFFF);
	_scr_draw_line(0, 15, 4, 15, 0xFFFF);
}

void _draw_plot_(void) {
	if(adc_flag == 1) {
		adc_flag = 0;
		ALL_IRQ_DIS();
		_scr_draw_pixel(_x_pos, (adc_read_value/100 + 15), 0xFFFF320A);
		adc_read_value_buffer = (adc_read_value/100 + 15);
		_x_pos++;
		if(_x_pos > 95) {
			_scr_clear_part_screen(5, 15, 95, (4096/100+15));
			_x_pos = 5;
		}
		ALL_IRQ_EN();
	}
}

void _curtain_close(uint32_t speed) {
	for(uint32_t i = 0; i < 100; i++) {
		_scr_clear_part_screen(0, 0, 95, i);
		delay(speed);
	}
}

void _draw_intro(void) {

	for(uint32_t i = 0; i < 80; i++) {
		_scr_write_text(19, 25, "JJ RTOS", i);
		delay(10000);
	}
	for(uint32_t i = 0; i < 40; i++) {
		_scr_write_text(19, 25+i, "JJ RTOS", i);
		delay(10000);
	}
	_curtain_close(40000);
}

