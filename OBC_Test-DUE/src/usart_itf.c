/*
 * File Name:     usart_itf.c
 * Purpose:		  Serial communication for logging/debugging
 * Author:        Matthew Silverman
 * 
 */ 

#include "usart_itf.h"

void usart_init(void){
	gpio_configure_pin(US_RX_PIN, US_RX_PIN_FLAGS);
	gpio_configure_pin(US_TX_PIN, US_TX_PIN_FLAGS);
	
	const sam_usart_opt_t settings = {
		// check data sheet for relevant values
		US_BAUD_RATE,
		US_MR_CHRL_8_BIT,
		US_MR_PAR_NO,
		US_MR_NBSTOP_1_BIT,
		US_MR_CHMODE_NORMAL,
		/* This field is only used in IrDA mode. */
		IRDA_MODE
	};
	
	sysclk_enable_peripheral_clock(BOARD_ID_USART);
	usart_init_rs232(USART,&settings,sysclk_get_cpu_hz());
	
	usart_disable_interrupt(USART,0xffffffff);
	
	usart_enable_tx(USART);
	usart_enable_rx(USART);
}

void usart_clear(void){
	usart_reset_rx(USART);
	usart_reset_tx(USART);
	
	usart_enable_tx(USART);
	usart_enable_rx(USART);
}

void writec(char c){
	usart_putchar(USART,c);
}

void writes(const char* str){
	usart_write_line(USART,str);
}

void writei(uint32_t i){
	usart_write(USART,i);
}