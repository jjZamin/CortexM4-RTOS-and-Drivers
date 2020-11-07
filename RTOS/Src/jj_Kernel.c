/*
 * jj_Kernel.c
 *
 *  Created on: Aug 18, 2020
 *      Author: jj.Zamin (G.Mazin)
 */

#include "jj_Kernel.h"

uint8_t running_thread = 0;

void jj_schedule_next_thread_(void) {
	uint32_t *pICSR = (uint32_t*)ICSR_ADDR;
	*pICSR |= (PENDSV_SET);
}

uint32_t jj_get_current_psp(void) {
	return THREADS[running_thread].thrd_psp;
}

__attribute__((naked)) void jj_switch_sp_to_psp(void) {

	//[all this code is still using the MSP stack pointer, as we haven't switched to PSP yet for the threads]

	//THREAD 1 PSP
	//get value of PSP of current thread
	//CAREFUL! - - - this function is called from main, so LR is corrupted, so let's push LR to MAIN func
	__asm volatile ("PUSH {LR}");				//save return address
	__asm volatile ("BL jj_get_current_psp");	//current PSP will be stores in R0, LR is now for this function, not main!
	__asm volatile ("MSR PSP, R0");			//stores the PSP in R0 into the PSP register
	__asm volatile ("POP {LR}");				//getting the MAIN func LR back, so we can jump back to the caller (main)
	// control register: setting bit 1 to = 1 (0x02), activating PSP (table 2-10, DUI)
	__asm volatile ("MOV R0, #0x02"); 		//store 0x02 in R0
	__asm volatile ("MSR CONTROL, R0");		// MSR (move [value] to special register), here: R0 = 0x02, activating PSP
	__asm volatile ("BX LR");
	//stackpointer change from MSP to PSP
}


/* systick init*/
void jj_systick_init(uint32_t prescaler) {

	uint32_t *pRVR = (uint32_t*)SYSTICK_RELOADVAL_ADDR;
	uint32_t *pCSR = (uint32_t*)SYSTICK_CSR_ADDR;
	uint32_t count_value = (SYSTEM_CLOCK/prescaler) - 1; //counts to 16000 before every IRQ - giving 1ms between IRQs
	//-1 because when SysTick timer counts 4, 3, 2, 1, 0 - the IRQ doesn't happen on 0 but on the next clock
	//systick is a 24 bit counter

	/*loading the tick_hz value into the register */
	// clear the rvr register
	*pRVR &= ~(0x00FFFFFF);
	*pRVR |= count_value;

	//settings
	*pCSR |=SYSTICK_CSR_IRQ;
	*pCSR |=SYSTICK_CSR_sCLK; //processor clock

	//enable systick
	*pCSR |=SYSTICK_CSR_ENABLE;
}

void jj_save_thread_stack_psp(uint32_t stack_addr) {
	THREADS[running_thread].thrd_psp = stack_addr;
}

void jj_go2next_thread(void) {
		running_thread++;
		running_thread = running_thread % NUMBR_OF_THREADS;
}

__attribute__((naked)) void PendSV_Handler(void) {

	/*low priority - so other interrupts are handled first, so it's for interrupt noisy environtment*/
	/*[in handler mode processor always uses the MSP, so we use NOT POP and PUSH but LOAD and STORE]*/
	/* save state of current thread! */

	//1) get PSP of current thread
	__asm volatile ("MRS R0, PSP"); //(move register to special register
	//2) store R4-R11, rest is stored automaticcally by the processor when any handler occurs
	// "!" means not only use addresse of PSP in R0, but also stores the new decremented address back into R0.
	__asm volatile ("STMDB R0!, {R4-R11}"); //stores multiple registers, decrememnt before (like push)
	//3) save PSP of current thread, for later retrieval of this data
	__asm volatile ("PUSH {LR}");
	__asm volatile ("BL jj_save_thread_stack_psp"); //always saves from R0 as argument. So PSP is saved.

	/*--next threads state is loaded back into the registers--*/
	//1) which thread?
	__asm volatile ("BL jj_go2next_thread"); //update to next thread and come back here
	//2) get psp of next thread
	__asm volatile ("BL jj_get_current_psp"); //get the PSP of this thread to be run, stored in R0
	//3) retrieve r4-r11 for next thread
	__asm volatile ("LDMIA R0!, {R4-R11}");				//load several registers; increment the pointer (in R0 now) after
	//4) update PSP with thread psp that is to be run now.
	__asm volatile ("MSR PSP, R0"); //for the system to load PC and all other registers from RAM to registers
	//return to caller
	__asm volatile ("POP {LR}"); //naked function - also LR is being corrupted inside this function.
	__asm volatile ("BX LR");

}

__attribute__((naked)) void jj_scheduler_stack_init(uint32_t top_stack_p_addr) {

	//chaing MSP, only done in assembly
	__asm volatile ("MSR MSP, %0" : : "r" (top_stack_p_addr) : );
	__asm volatile ("BX LR"); //nake function = you have to write return, because it has no return your self
}


void SysTick_Handler(void) {

	uint32_t *pICSR = (uint32_t*)ICSR_ADDR;
	*pICSR |= (PENDSV_SET);
}

void jj_threads_init(void) {


	THREADS[0].thrd_psp = THRD1_STACK_pSTART;
	THREADS[1].thrd_psp = THRD2_STACK_pSTART;
	THREADS[2].thrd_psp = THRD3_STACK_pSTART;
	THREADS[3].thrd_psp = THRD4_STACK_pSTART;

	THREADS[0].thrd_addr = jj_THREAD_1;
	THREADS[1].thrd_addr = jj_THREAD_2;
	THREADS[2].thrd_addr = jj_THREAD_3;
	THREADS[3].thrd_addr = jj_THREAD_4;
}

void jj_thread_stack_init(void) {

	uint32_t *pPSP; //to store dummies into the stacks for the beginning of the tasks.

	for(uint32_t i = 0; i < NUMBR_OF_THREADS; i++) {

		pPSP = (uint32_t*)THREADS[i].thrd_psp; //go through all 4 tasks' start_ stack pointer
		pPSP--; //stack is decending
		*pPSP = T_BIT;

		pPSP--; //PC
		*pPSP = (uint32_t)THREADS[i].thrd_addr;

		pPSP--; //LR
		*pPSP = EXC_RETURN_ADDR;

		//storing the remaining general purpose registers (R4 - Rn..)
		for(uint8_t j = 0; j < 13; j++) {
			pPSP--;
			*pPSP = 0;
		}

		//saving the stack pointer of the given thread;
		THREADS[i].thrd_psp = (uint32_t)pPSP;
	}
}

void jj_SETUP_KERNEL(void) {

	__asm volatile ("MOV R11, LR");
	jj_scheduler_stack_init(SCHD_STACK_pSTART);
	jj_threads_init();
	jj_thread_stack_init();
	jj_systick_init(THREAD_RUN_PERIOD);
	jj_switch_sp_to_psp();
	__asm volatile ("MOV LR, R11");
	__asm volatile ("BX LR");
}
