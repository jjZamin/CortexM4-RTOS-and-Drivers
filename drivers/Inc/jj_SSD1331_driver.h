/*
 * jj_SSD1331_driver.h
 *
 *  Created on: 18 Aug 2020
 *      Author: ghenm
 */

#ifndef INC_JJ_SSD1331_DRIVER_H_
#define INC_JJ_SSD1331_DRIVER_H_

#include "jj_SSD1331_SPI.h"
#include "jj_SSD1331_SYMBOLS.h"
#include <stdlib.h>

#define ALL_IRQ_DIS()				do{__asm volatile ("MOV R0, #0x01"); __asm volatile ("MSR PRIMASK, R0"); } while(0)
#define ALL_IRQ_EN()				do{__asm volatile ("MOV R0, #0x00"); __asm volatile ("MSR PRIMASK, R0"); } while(0)

/* INIT SCREEN CMDS */
#define MASTER_CONFIG 				0xAD
#define DISPLAY_OFF					0xAE
#define DISPLAY_ON					0xAF
#define CONTRAST_A					0x81
#define CONTRAST_B					0x82
#define CONTRAST_C					0x83
#define MASTER_CURRENT				0x87
#define SECOND_PRECHARGE_SPEED_A	0x8A
#define SECOND_PRECHARGE_SPEED_B	0x8B
#define SECOND_PRECHARGE_SPEED_C	0x8C
#define REMAP						0xA0
#define DISP_STARTLINE				0xA1
#define DISP_OFFSET					0xA2
#define DISP_MODE_NORMAL			0xA4
#define MUX_RATION					0xA8
#define POWER_SAVE_MODE				0xB0
#define PHASE_ADJ					0xB1
#define DISP_CLKDIV					0xB3
#define PRECHARGE_LEVEL				0xBB
#define V_COMH						0xBE
#define DEACT_SCROLL				0x2E
#define CLEAR_WINDOW				0x25
#define COLUMN_ADDRESS              0x15
#define ROW_ADDRESS                 0x75

/* SCREEN SIZE */
#define SCREEN_WIDTH 				95
#define SCREEN_HEIGHT 				63

/* DRAWING CMDS */
#define FILL						0x26
#define DRAW_RECT					0x22
#define DRAW_LINE					0x21
#define COPY						0x23

/* colors */

/* functions */
void delay(uint32_t nr);
void SSD1331_init(void);
void _scr_clear_part_screen(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);
void _scr_clear_full_screen(void);
void _scr_draw_rect(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint32_t _edge_color, uint32_t _fill_color, uint8_t _fill_en);
void _scr_draw_line(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint32_t _line_color);
void _scr_copypaste(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t _x1, uint8_t _y1);
void _scr_copypaste_clean(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t _x1, uint8_t _y1);
void _scr_draw_pixel(uint8_t x, uint8_t y, uint32_t _pixel_color);
void _scr_send_buffer(uint8_t *buf, uint32_t size);
void _scr_write_text(uint8_t x, uint8_t y, char text[], uint32_t _color);
char* _scr_return_number(uint32_t nr, char *buffer);

#endif /* INC_JJ_SSD1331_DRIVER_H_ */
