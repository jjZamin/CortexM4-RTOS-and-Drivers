/*
	jj_RTOS_common.h
 *
 *  Created on: Aug 18, 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#ifndef INC_JJ_RTOS_COMMON_H_
#define INC_JJ_RTOS_COMMON_H_

#include "jj_Addresses.h"
#include <stdint.h>
/*############################################ [KERNAL] ############################################*/

/*tick desired freq for systick*/
#define THREAD_RUN_PERIOD			1000U //IRQ from systick will happen every 1 ms (on a 16Mhz clock)
#define SYSTEM_CLOCK				16000000U

#define THREAD_STACK_SIZE			1024U //(1kB)
#define SCHEDULER_STACK_SIZE		1024U //(1kB)
#define SRAM_SIZE					(96 * 1024) // 96kB

#define THRD1_STACK_pSTART			SRAM_END_ADDR
#define THRD2_STACK_pSTART			(SRAM_END_ADDR - (THREAD_STACK_SIZE ))
#define THRD3_STACK_pSTART			(SRAM_END_ADDR - (THREAD_STACK_SIZE * 2))
#define THRD4_STACK_pSTART			(SRAM_END_ADDR - (THREAD_STACK_SIZE * 3))
#define SCHD_STACK_pSTART			(SRAM_END_ADDR - (SCHEDULER_STACK_SIZE * 4))
#define NUMBR_OF_THREADS			4 //4 program threads + 1 sleep thread (idle)

#define SYSTICK_CSR_ENABLE			(1 << 0)    //DUI
#define SYSTICK_CSR_IRQ				(1 << 1)	// IRQ enable systikc
#define SYSTICK_CSR_sCLK			(1 << 2)	//clock source

//table 2-17 in DUI - using PSP after return, non floating point
#define EXC_RETURN_ADDR				0xFFFFFFFDU

// must always be set, as cortex M4 only runs THUMB ISA.
#define T_BIT						0x01000000U //THUMB MODE, t-bit @bit24


//pendSV
#define PENDSV_SET					(1 << 28)

//using PRIMASK register, EN/DIS global IRQ.
#define ALL_IRQ_DIS()				do{__asm volatile ("MOV R0, #0x01"); __asm volatile ("MSR PRIMASK, R0"); } while(0)
#define ALL_IRQ_EN()				do{__asm volatile ("MOV R0, #0x00"); __asm volatile ("MSR PRIMASK, R0"); } while(0)

/*##################################################################################################*/


#endif /* INC_JJ_RTOS_COMMON_H_ */
