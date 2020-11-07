/*
 * jj_Kernel.h
 *
 *  Created on: Aug 18, 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#ifndef INC_JJ_KERNEL_H_
#define INC_JJ_KERNEL_H_

/*threads*/
#include "jj_RTOS_common.h"
#include <stdio.h>

void jj_schedule_next_thread_(void);
uint32_t jj_get_current_psp(void);
__attribute__((naked)) void jj_switch_sp_to_psp(void);
void jj_systick_init(uint32_t prescaler);
void jj_save_thread_stack_psp(uint32_t stack_addr);
void jj_go2next_thread(void);
__attribute__((naked)) void jj_scheduler_stack_init(uint32_t top_stack_p_addr);
void jj_SETUP_KERNEL(void);

void SysTick_Handler(void);
__attribute__((naked)) void PendSV_Handler(void);

typedef struct {
	void (*thrd_addr)(void);
	uint32_t thrd_psp;
	uint32_t thrd_current_state;
}Thread_Setup;

Thread_Setup THREADS[NUMBR_OF_THREADS];

/*---functions---*/
void jj_threads_init(void);
void jj_thread_stack_init(void);
/*threads*/
void jj_THREAD_1(void);
void jj_THREAD_2(void);
void jj_THREAD_3(void);
void jj_THREAD_4(void);
void jj_SETUP_THREADS(void);

#endif /* INC_JJ_KERNEL_H_ */
