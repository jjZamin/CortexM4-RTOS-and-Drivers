/**
 ******************************************************************************
 * @file           : main.c
 * @author         : jj.Zamin
 * @brief          : Main program body
 ******************************************************************************
*/


#include <string.h>
#include "jj_Kernel.h"
#include "jj_SSD1331_driver.h"
#include "jj_inits.h"
#include "jj_screen_functions.h"

#define _SHIP_WIDTH  	6
#define _SHIP_HEIGHT  	3
#define _SHIP_DELAY		5000

#define _ENEMY_WIDTH  	10
#define _ENEMY_HEIGHT  	5
#define _ENEMY_DELAY	8000

void init_all(void);

volatile uint8_t _ship_x = 50;
volatile uint8_t _ship_y = 50;

volatile uint8_t _enemy_x = 10;
volatile uint8_t _enemy_y = 10;
volatile uint8_t _enemy_switch = 0;
volatile uint8_t _enemy_color = 0;


volatile uint8_t _SHOOT_ = 0;
volatile uint8_t _bullet_x = 0;
volatile uint8_t _bullet_y = 0;

volatile uint8_t _life_left = 10;
volatile uint8_t _dead = 0;


int main(void)
{
	init_all();

	jj_SETUP_KERNEL();
	jj_THREAD_1();

	while(1);
}


/*threads*/
void jj_sleep_(void) {
	while(1) {}
}

void jj_THREAD_1(void) { //my ship
	while(1) {
		if(!jj_GPIO_rdPin(JJ_pGPIOA, JJ_PIN_5)) {
			delay(_SHIP_DELAY);
			_scr_draw_rect(_ship_x, _ship_y, _ship_x+_SHIP_WIDTH, _ship_y+_SHIP_HEIGHT, 0x00000000, 0x00000000, JJ_ENABLE);
			_ship_x--;
			if(_ship_x < 6) {
				_ship_x = 6;
			}
			_scr_draw_rect(_ship_x, _ship_y, _ship_x+_SHIP_WIDTH, _ship_y+_SHIP_HEIGHT, 0x12341234, 0xAAABCCDE, JJ_ENABLE);
		}
		else if(!jj_GPIO_rdPin(JJ_pGPIOA, JJ_PIN_6)) {
			delay(_SHIP_DELAY);
			_scr_draw_rect(_ship_x, _ship_y, _ship_x+_SHIP_WIDTH, _ship_y+_SHIP_HEIGHT, 0x00000000, 0x00000000, JJ_ENABLE);
			_ship_x++;
			if(_ship_x > 85) {
				_ship_x = 85;
			}
			_scr_draw_rect(_ship_x, _ship_y, _ship_x+_SHIP_WIDTH, _ship_y+_SHIP_HEIGHT, 0x12341234, 0xAAABCCDE, JJ_ENABLE);
		}
	}
}

void jj_THREAD_2(void) {
	while(1) { //enemy
		if(!_dead) {
			delay(_ENEMY_DELAY);
			_scr_draw_rect(_enemy_x, _enemy_y, _enemy_x+_ENEMY_WIDTH, _enemy_y+_ENEMY_HEIGHT, 0x00000000, 0x00000000, JJ_ENABLE);

			if(_enemy_x == 80) {
				_enemy_switch = 0;
			}
			else if(_enemy_x == 10) {
				_enemy_switch = 1;
			}
			if(_enemy_switch) {
				_enemy_x++;
			}
			else {
				_enemy_x--;
			}
			_scr_draw_rect(_enemy_x, _enemy_y, _enemy_x+_ENEMY_WIDTH, _enemy_y+_ENEMY_HEIGHT, _enemy_color*2, _enemy_color, JJ_ENABLE);
			_enemy_color++;
			if(_enemy_color > 0xffff) {
				_enemy_color = 0;
			}
		}
		else {
			_scr_draw_rect(_enemy_x, _enemy_y, _enemy_x+_ENEMY_WIDTH, _enemy_y+_ENEMY_HEIGHT, 0x00000000, 0x00000000, JJ_ENABLE);
			for(uint32_t i = 0; i < 30; i++) {
				_scr_write_text(17, 25, "YOU WON", 0xa0343404*i);
			}
		}
	}
}
//A[5,6,7,9]
void jj_THREAD_3(void) { //winning!
	while(1) {
		if(_dead) {
			for(uint32_t i = 0; i < 30; i++) {
				_scr_draw_pixel(10, 14, 0xffff*i*2);
				_scr_draw_pixel(14, 11, 0xff0f*i*2);
				_scr_draw_pixel(12, 18, 0xfcff*i*2);
				_scr_draw_pixel(14, 10, 0xffff*i*2);
				_scr_draw_pixel(21, 17, 0xfaaf*i*3);
				_scr_draw_pixel(18, 12, 0x00ff*i*4);
				delay(1000);
			}

		}
	}
}

void jj_THREAD_4(void) { //shooting
	while(1) {

		if(!jj_GPIO_rdPin(JJ_pGPIOA, JJ_PIN_7) && !_SHOOT_) {
			delay(100000);
			_SHOOT_ = 1;
		}
		if(_SHOOT_) {
			_bullet_x = _ship_x + 3;
			_bullet_y = _ship_y;
			for(uint32_t i = 0; i < 60; i++) {
				_scr_draw_pixel(_bullet_x, _bullet_y, 0x00000000);
				_bullet_y--;
				_scr_draw_pixel(_bullet_x, _bullet_y, 0xffaabbcc);

				if((_enemy_y-4 == _bullet_y) && (_enemy_x == _bullet_x || _enemy_x+1 == _bullet_x || _enemy_x+2 == _bullet_x
						|| _enemy_x+3 == _bullet_x || _enemy_x+4 == _bullet_x || _enemy_x+5 == _bullet_x || _enemy_x+6 == _bullet_x
						|| _enemy_x+7 == _bullet_x || _enemy_x+8 == _bullet_x || _enemy_x+9 == _bullet_x || _enemy_x+10 == _bullet_x)) {


					delay(10000);
					_scr_draw_rect(0, 0, _life_left, 4, 0x00000000, 0x00000000, JJ_ENABLE);
					if(_life_left > 0) {
						_life_left--;
						if(_life_left == 0) {
							_dead = 1;
						}
					}
					if(!_dead) {
						_scr_draw_rect(0, 0, _life_left, 2, 0xaaabbbaa, 0xb0c45b00, JJ_ENABLE);
					}
					else {
						_scr_draw_rect(0, 0, _life_left, 4, 0x00000000, 0x00000000, JJ_ENABLE);
					}

				}

				delay(1000);
				if(_bullet_y == 0) {
					_scr_draw_pixel(_bullet_x, _bullet_y, 0x00000000);
					break;
				}
			}
			_SHOOT_ = 0;
		}
	}
}

void ADC_IRQHandler(void) {
	adc_read_value = jj_ADC_READ();
	adc_count++;
	if(	adc_count > 1000) {
		adc_count = 0;
		adc_flag = 1;
	}
	jj_ADC_START_NEW_CONV();
}

void TIM2_IRQHandler(void) {
	jj_TIM2_5_IRQ_Handler(JJ_pTIM2);
}

/*
void EXTI15_10_IRQHandler(void) {
	delay(200000);
	jj_IRQ_Handling(JJ_PIN_13);
	stm_btn_flag = 1;
}
*/

void init_all(void) {
	//ADC_init();
	//TIM2_init(1000, 16000);
	SSD1331_init();
	pin_btnstm32_setup();
	_scr_clear_full_screen();
	_scr_draw_rect(_enemy_x, _enemy_y, _enemy_x+_ENEMY_WIDTH, _enemy_x+_ENEMY_HEIGHT, 0xABCD6729, 0x9876ABDC, JJ_ENABLE);
	_scr_draw_rect(_ship_x, _ship_y, _ship_x+_SHIP_WIDTH, _ship_y+_SHIP_HEIGHT, 0x12341234, 0xAAABCCDE, JJ_ENABLE);
	//_draw_intro();
	/*---------------------------------------*/
}



