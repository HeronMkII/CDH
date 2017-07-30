/*
 * File Name:     usart_itf.h
 * Purpose:		  Serial communication for logging/debugging
 * Author:        Matthew Silverman
 * 
 */ 


#ifndef USART_ITF_H_
#define USART_ITF_H_

#define US_RX_PIN PIN_USART0_RXD_IDX
#define US_TX_PIN PIN_USART0_TXD_IDX
#define US_RX_PIN_FLAGS PIN_USART0_RXD_FLAGS 
#define US_TX_PIN_FLAGS PIN_USART0_TXD_FLAGS
#define US_BAUD_RATE 38400
#define USART USART0
#define IRDA_MODE 0

void usart_init(void);
void usart_clear(void);
void writec(char c);
void writes(char* str);
void writei(uint32_t i);

#endif /* USART_ITF_H_ */