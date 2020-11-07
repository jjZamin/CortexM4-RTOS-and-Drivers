/*
 * jj_SSD1331_driver.c
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#include "jj_SSD1331_driver.h"

void delay(uint32_t nr) {
	for(uint32_t i = 0; i < nr; i++);
}

uint8_t* check_borders(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t _x1, uint8_t _y1) {

	uint8_t *p;
	static uint8_t border_buff[6];
	memset(&border_buff, 0, sizeof(border_buff));

	if((int8_t)x1 < 0){x1 = 0;}
	if((int8_t)x2 < 0){x2 = 0;}
	if((int8_t)y1 < 0){y1 = 0;}
	if((int8_t)y2 < 0){y2 = 0;}
	if(x1 > SCREEN_WIDTH){x1 = SCREEN_WIDTH;}
	if(x2 > SCREEN_WIDTH){x2 = SCREEN_WIDTH;}
	if(y1 > SCREEN_HEIGHT){y1 = SCREEN_HEIGHT;}
	if(y2 > SCREEN_HEIGHT){y2 = SCREEN_HEIGHT;}
	if((int8_t)_x1 < 0){_x1 = 0;}
	if((int8_t)_y1 < 0){_y1 = 0;}
	if(_x1 > SCREEN_WIDTH){_x1 = _x1 - SCREEN_WIDTH;}
	if(_y1 > SCREEN_HEIGHT){_y1 = _y1 - SCREEN_HEIGHT;}

	border_buff[0] = x1;
	border_buff[1] = y1;
	border_buff[2] = x2;
	border_buff[3] = y2;
	border_buff[4] = _x1;
	border_buff[5] = _y1;

	p = &border_buff[0];

	return p;
}


/*-----------------*/

void _SEND_CMD(uint8_t cmd) {
	_dc(JJ_DISABLE);
	_SPI_TX(cmd);
}

void _SEND_DATA(uint8_t data) {
	_dc(JJ_ENABLE);
	_SPI_TX(data);
}

void SSD1331_init(void) {
	SPI2_init();
	_rst(JJ_DISABLE);
	delay(250000);
	_rst(JJ_ENABLE);

	/* INIT CMDS */
	_SEND_CMD(DISPLAY_OFF);
	_SEND_CMD(MASTER_CONFIG);
	_SEND_CMD(0x8E);
	_SEND_CMD(CONTRAST_A);
	_SEND_CMD(0x80);
	_SEND_CMD(CONTRAST_B);
	_SEND_CMD(0x80);
	_SEND_CMD(CONTRAST_C);
	_SEND_CMD(0x80);
	_SEND_CMD(MASTER_CURRENT);
	_SEND_CMD(0x0E);
	_SEND_CMD(SECOND_PRECHARGE_SPEED_A);
	_SEND_CMD(0x81);
	_SEND_CMD(SECOND_PRECHARGE_SPEED_B);
	_SEND_CMD(0x82);
	_SEND_CMD(SECOND_PRECHARGE_SPEED_C);
	_SEND_CMD(0x83);
	_SEND_CMD(REMAP);
	_SEND_CMD(0x72);
	_SEND_CMD(DISP_STARTLINE);
	_SEND_CMD(0x00);
	_SEND_CMD(DISP_OFFSET);
	_SEND_CMD(0x00);
	_SEND_CMD(DISP_MODE_NORMAL);
	_SEND_CMD(0x3F);
	_SEND_CMD(POWER_SAVE_MODE);
	_SEND_CMD(0x00);
	_SEND_CMD(PHASE_ADJ);
	_SEND_CMD(0x31);
	_SEND_CMD(DISP_CLKDIV);
	_SEND_CMD(0xF0);
	_SEND_CMD(PRECHARGE_LEVEL);
	_SEND_CMD(0x3A);
	_SEND_CMD(V_COMH);
	_SEND_CMD(DEACT_SCROLL);
	_SEND_CMD(DISPLAY_ON);
}

void _scr_clear_part_screen(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2) {

	//uint8_t *p = check_borders(x1, y1, x2, y2, 0, 0);
	ALL_IRQ_DIS();
	_SEND_CMD(CLEAR_WINDOW);
	_SEND_CMD(x1);
	_SEND_CMD(y1);
	_SEND_CMD(x2);
	_SEND_CMD(y2);
	ALL_IRQ_EN();
}

void _scr_clear_full_screen(void) {

	ALL_IRQ_DIS();
	_SEND_CMD(CLEAR_WINDOW);
	_SEND_CMD(0x00);
	_SEND_CMD(0x00);
	_SEND_CMD(SCREEN_WIDTH);
	_SEND_CMD(SCREEN_HEIGHT);
	delay(2000);
	ALL_IRQ_EN();
}

void _scr_draw_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint32_t _edge_color, uint32_t _fill_color, uint8_t _fill_en) {

	uint32_t edge_color = 0;
	uint32_t fill_color = 0;


	ALL_IRQ_DIS();
	if(_fill_en == JJ_ENABLE) {_SEND_CMD(FILL); _SEND_CMD(0x01);}
	if(_fill_en == JJ_DISABLE) {_SEND_CMD(FILL); _SEND_CMD(0x00);}

	//uint8_t *p = check_borders(x1, y1, x2, y2, 0, 0);

	_SEND_CMD(DRAW_RECT);
	_SEND_CMD(x1);
	_SEND_CMD(y1);
	_SEND_CMD(x2);
	_SEND_CMD(y2);

	edge_color = _edge_color;
	_SEND_CMD((uint8_t)edge_color);
	edge_color = _edge_color >> 8;
	_SEND_CMD((uint8_t)edge_color);
	edge_color = _edge_color >> 16;
	_SEND_CMD((uint8_t)edge_color);

	fill_color = _fill_color;
	_SEND_CMD((uint8_t)fill_color);
	fill_color = _fill_color >> 8;
	_SEND_CMD((uint8_t)fill_color);
	fill_color = _fill_color >> 16;
	_SEND_CMD((uint8_t)fill_color);
	delay(100);
	ALL_IRQ_EN();
}

void _scr_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint32_t _line_color) {

	uint32_t line_color = 0;

	//uint8_t *p = check_borders(x1, y1, x2, y2, 0, 0);

	_SEND_CMD(DRAW_LINE);
	_SEND_CMD(x1);
	_SEND_CMD(y1);
	_SEND_CMD(x2);
	_SEND_CMD(y2);

	line_color = _line_color;
	_SEND_CMD((uint8_t)line_color);
	line_color = _line_color >> 8;
	_SEND_CMD((uint8_t)line_color);
	line_color = _line_color >> 16;
	_SEND_CMD((uint8_t)line_color);

}

void _scr_copypaste(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t _x1, uint8_t _y1) {

	//uint8_t *p = check_borders(x1, y1, x2, y2, _x1, _y1);
	ALL_IRQ_DIS();
	_SEND_CMD(COPY);
	_SEND_CMD(x1);
	_SEND_CMD(y1);
	_SEND_CMD(x2);
	_SEND_CMD(y2);
	_SEND_CMD(_x1);
	_SEND_CMD(_y1);
	ALL_IRQ_EN();
}

void _scr_copypaste_clean(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t _x1, uint8_t _y1) {

	ALL_IRQ_DIS();
	_scr_copypaste(x1, y1, x2, y2, _x1, _y1);
	delay(100);
	_scr_clear_part_screen(x1, y1, x2, y2);
	delay(100);
	ALL_IRQ_EN();
}

void _scr_draw_pixel(uint8_t x, uint8_t y, uint32_t _pixel_color) {

	uint32_t clr = 0;
	ALL_IRQ_DIS();
	if(x <= 0) {x = 0;}
	if(x >= SCREEN_WIDTH) {x = SCREEN_WIDTH;}
	if(y <= 0) {y = 0;}
	if(y >= SCREEN_HEIGHT) {y = SCREEN_HEIGHT;}

	_SEND_CMD(COLUMN_ADDRESS);
	_SEND_CMD(x);
	_SEND_CMD(SCREEN_WIDTH);
	_SEND_CMD(ROW_ADDRESS);
	_SEND_CMD(y);
	_SEND_CMD(SCREEN_HEIGHT);
	clr = _pixel_color;
	_SEND_DATA((uint8_t)clr);
	clr = (_pixel_color >> 8);
	_SEND_DATA((uint8_t)clr);
	clr = (_pixel_color >> 16);
	_SEND_DATA((uint8_t)clr);
	ALL_IRQ_EN();
}

void _scr_send_buffer(uint8_t *buf, uint32_t size) {
	_dc(JJ_DISABLE);
	_SPI_TX_BUF(buf, size);
}


uint8_t _scr_which_symbol(char symbol) {

	uint8_t _this_letter = 0;

	switch(symbol) {
		case ' ':
			_this_letter = 0;
			break;
		case 'A':
			_this_letter = 1;
			break;
		case 'B':
			_this_letter = 2;
			break;
		case 'C':
			_this_letter = 3;
			break;
		case 'D':
			_this_letter = 4;
			break;
		case 'E':
			_this_letter = 5;
			break;
		case 'F':
			_this_letter = 6;
			break;
		case 'G':
			_this_letter = 7;
			break;
		case 'H':
			_this_letter = 8;
			break;
		case 'I':
			_this_letter = 9;
			break;
		case 'J':
			_this_letter = 10;
			break;
		case 'K':
			_this_letter = 11;
			break;
		case 'L':
			_this_letter = 12;
			break;
		case 'M':
			_this_letter = 13;
			break;
		case 'N':
			_this_letter = 14;
			break;
		case 'O':
			_this_letter = 15;
			break;
		case 'P':
			_this_letter = 16;
			break;
		case 'Q':
			_this_letter = 17;
			break;
		case 'R':
			_this_letter = 18;
			break;
		case 'S':
			_this_letter = 19;
			break;
		case 'T':
			_this_letter = 20;
			break;
		case 'U':
			_this_letter = 21;
			break;
		case 'V':
			_this_letter = 22;
			break;
		case 'W':
			_this_letter = 23;
			break;
		case 'X':
			_this_letter = 24;
			break;
		case 'Y':
			_this_letter = 25;
			break;
		case 'Z':
			_this_letter = 26;
			break;
		case '0':
			_this_letter = 27;
			break;
		case '1':
			_this_letter = 28;
			break;
		case '2':
			_this_letter = 29;
			break;
		case '3':
			_this_letter = 30;
			break;
		case '4':
			_this_letter = 31;
			break;
		case '5':
			_this_letter = 32;
			break;
		case '6':
			_this_letter = 33;
			break;
		case '7':
			_this_letter = 34;
			break;
		case '8':
			_this_letter = 35;
			break;
		case '9':
			_this_letter = 36;
			break;
		case '.':
			_this_letter = 37;
			break;
		case ':':
			_this_letter = 38;
			break;

		default:
			_this_letter = 0;
			break;
	}
	return _this_letter;
}


void _scr_write_text(uint8_t x, uint8_t y, char text[], uint32_t _color) {
	uint8_t _x = x;
	uint8_t _y = y;

	char letter;
	uint8_t _x_cnt = 0;
	uint8_t _letter_cnt = 0;
	uint8_t _this_letter = 0;
	uint8_t _x_buf = 0;

	ALL_IRQ_DIS();
	while(_letter_cnt < strlen(text) ) {

		letter = text[_letter_cnt];

		_this_letter = _scr_which_symbol(letter);

		for(uint8_t i = 0; i < 64; i++) {
			if(__ascii[_this_letter][i] == 1) {
				_scr_draw_pixel(_x, _y, _color);
			}
			else {
				_scr_draw_pixel(_x, _y, 0x0000);
			}
			_x++;
			_x_cnt++;

			if(_x_cnt > 7) {
				_x_cnt = 0;
				_x = x + _x_buf;
				_y++;
			}
		}

		_x_cnt = 0;
		_letter_cnt++;
		_x_buf = _x_buf + 8;
		_y = y;
		_x = x + _x_buf;
	}
	ALL_IRQ_EN();
}

char* _scr_return_number(uint32_t nr, char *buffer) {
	itoa(nr, buffer, 10);
	return &buffer[0];
}
