/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */
#include <asf.h>
#include <can_driver.h>

/*  Initialize the priorities of various interrupts on the Cortex-M3 System */
static void prvInitializeInterruptPriorities(void);


int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();
	board_init();
	
	prvInitializeInterruptPriorities();
	NVIC_SetPriorityGrouping(0);

	
	
	can_init_asf();
	

	
	while(1){
		
		can_send(123, 456, 1, 1, 1);
		can_global_send_transfer_cmd(CAN0, CAN_TCR_MB0);


	}
	
	
	return 0;
}

static void prvInitializeInterruptPriorities(void)
{
	uint32_t priority = 11;
	IRQn_Type can1_int_num = (IRQn_Type)44;
	IRQn_Type can0_int_num = (IRQn_Type)43;
		
	NVIC_SetPriority(can1_int_num, priority);
	
	priority = 12;	
	NVIC_SetPriority(can0_int_num, priority);
	
	priority = NVIC_GetPriority(can1_int_num);
	
	return;
}