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
#include <usart_itf.h>

/*  Initialize the priorities of various interrupts on the Cortex-M3 System */
static void prvInitializeInterruptPriorities(void);

int main (void)
{
	sysclk_init();
	board_init();
	cpu_irq_enable();

	// Initialize CAN interrupts		
	irq_initialize_vectors();
	prvInitializeInterruptPriorities();
	NVIC_SetPriorityGrouping(0);

	can_init_asf();

	// Initialize the USART
	usart_clear();
	usart_init();
	
	gpio_set_pin_high(LED); // CAN interrupt will set this low
	
	// Uncomment this loop to send CAN messages as well as receive
	
	/*while(1){
		can_send(0x05, 0x0a, 1, 1, 1);						// Expecting 5 blinks, 3 seconds pause, then 10 blinks
		can_global_send_transfer_cmd(CAN0, CAN_TCR_MB0);
	}*/
	
	// A simple USART test
	
	const char* test = "test string";
	writes(test);
	
	char space = ' ';
	writec(space);
	
	uint32_t itest = 123;
	writei(itest);
	
	while(1);
	return 0;
}

static void prvInitializeInterruptPriorities(void)
{
	IRQn_Type can1_int_num = (IRQn_Type)44;
	IRQn_Type can0_int_num = (IRQn_Type)43;
		
	NVIC_ClearPendingIRQ(can0_int_num);
	NVIC_ClearPendingIRQ(can1_int_num);
	
	uint32_t priority = 11;
	NVIC_SetPriority(can1_int_num, priority);
	
	priority = 12;	
	NVIC_SetPriority(can0_int_num, priority);
}