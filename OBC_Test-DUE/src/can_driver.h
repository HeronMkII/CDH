/*
 * can_driver.h
 *
 * Created: 2/26/2017 12:31:16 AM
 *  Author: Ali
 */ 


#ifndef CAN_DRIVER_H_
#define CAN_DRIVER_H_

/* Library Includes */

#include <asf/sam/drivers/can/can.h>
#include <stdio.h>
#include <board.h>
#include <sysclk.h>
#include <exceptions.h>
#include <pmc.h>
#include <conf_board.h>
#include <conf_clock.h>
#include <pio.h>
#include <can.h>
#include <sam_gpio/sam_gpio.h>

/* CAN Structures */

can_mb_conf_t * setup_mb;
can_mb_conf_t * tx_mb;

can_mb_conf_t can0_mailbox;
can_mb_conf_t can1_mailbox;

//can_mb_conf_t can0_mailbox;

/* Enable CAN mailboxes */
// Move this to a board configure file!
#define CONF_BOARD_CAN0		1
#define CONF_BOARD_CAN1		1


/* CAN Setup Parameters */

#define MAX_CAN_FRAME_DATA_LEN  8

/* CAN Mailbox Data Direction */

#define CAN_TX				    0
#define CAN_RX				    1

/* CAN Mailbox IDs */

#define CAN0_MB0				1
#define CAN0_MB1				2
#define CAN0_MB2				3
#define CAN0_MB3				4
#define CAN0_MB4				5
#define CAN0_MB5				6
#define CAN0_MB6				7
#define CAN0_MB7				8

#define CAN1_MB0				9
#define CAN1_MB1				10
#define CAN1_MB2				11
#define CAN1_MB3				12
#define CAN1_MB4				13
#define CAN1_MB5				14
#define CAN1_MB6				15
#define CAN1_MB7				16

/* CAN Mailbox Setup Parameters*/

#define CAN0_DIR				CAN_TX
#define CAN1_DIR				CAN_RX

#define CAN0_MB0_PRIO			10
#define CAN0_MB1_PRIO			10
#define CAN0_MB2_PRIO			10
#define CAN0_MB3_PRIO			10
#define CAN0_MB4_PRIO			10
#define CAN0_MB5_PRIO			10
#define CAN0_MB6_PRIO			10
#define CAN0_MB7_PRIO			10

#define CAN1_MB0_PRIO			0
#define CAN1_MB1_PRIO			0
#define CAN1_MB2_PRIO			0
#define CAN1_MB3_PRIO			0
#define CAN1_MB4_PRIO			0
#define CAN1_MB5_PRIO			0
#define CAN1_MB6_PRIO			0
#define CAN1_MB7_PRIO			0

// LED used for testing. LED2_GPIO for CDH SAM3X board, LED0_GPIO for Arduino Due
#define LED LED2_GPIO


/* Functions */

void can_init_asf(void);

uint8_t can_initialize(void);
void reset_mailbox_conf(can_mb_conf_t *p_mailbox);
void can_init_mailbox(uint8_t mailbox_id, uint8_t data_direction, uint8_t priority);
uint8_t can_send(uint32_t low, uint32_t high, uint8_t mailbox_id, uint8_t msg_ID, uint8_t priority);
void can_make_mailbox(can_mb_conf_t *p_mailbox, uint8_t mailbox_id, uint8_t data_direction, uint8_t priority);


/* Pin Definitions - Need to set board to sam3x_ek */

/* ------------------------------------------------------------------------ */
/* CAN                                                                      */
/* ------------------------------------------------------------------------ */

/*! CAN0 RXEN: Select input for high speed mode or ultra low current sleep mode */
#define PIN_CAN0_TRANSCEIVER_RXEN\
	{ PIO_PB21, PIOB, ID_PIOB, PIO_OUTPUT_1, PIO_DEFAULT }

/*! CAN0 RS: Select input for high speed mode or low-current standby mode */
#define PIN_CAN0_TRANSCEIVER_RS\
	{ PIO_PB20, PIOB, ID_PIOB, PIO_OUTPUT_0, PIO_DEFAULT }

/*! CAN0 TXD: Transmit data input */
#define PIN_CAN0_TXD\
	{ PIO_PA0A_CANTX0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT }

/*! CAN0 RXD: Receive data output */
#define PIN_CAN0_RXD\
	{ PIO_PA1A_CANRX0, PIOA, ID_PIOA, PIO_PERIPH_A, PIO_DEFAULT }

/*! List of all CAN0 definitions. */
#define PINS_CAN0    PIN_CAN0_TXD, PIN_CAN0_RXD

/** CAN0 transceiver PIN RS. */
#define PIN_CAN0_TR_RS_IDX        PIO_PB20_IDX
#define PIN_CAN0_TR_RS_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

/** CAN0 transceiver PIN EN. */
#define PIN_CAN0_TR_EN_IDX        PIO_PB21_IDX
#define PIN_CAN0_TR_EN_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

/** CAN0 PIN RX. */
#define PIN_CAN0_RX_IDX           (PIO_PA1_IDX)
#define PIN_CAN0_RX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)

/** CAN0 PIN TX. */
#define PIN_CAN0_TX_IDX           (PIO_PA0_IDX)
#define PIN_CAN0_TX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)

/*! CAN1 RXEN: Select input for high speed mode or ultra low current sleep mode */
#define PIN_CAN1_TRANSCEIVER_RXEN\
	{ PIO_PE16, PIOE, ID_PIOE, PIO_OUTPUT_1, PIO_DEFAULT }

/*! CAN1 RS: Select input for high speed mode or low-current standby mode */
#define PIN_CAN1_TRANSCEIVER_RS\
	{ PIO_PE15, PIOE, ID_PIOE, PIO_OUTPUT_0, PIO_DEFAULT }

/*! CAN1 TXD: Transmit data input */
#define PIN_CAN1_TXD\
	{ PIO_PB14A_CANTX1, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT }

/*! CAN1 RXD: Receive data output */
#define PIN_CAN1_RXD\
	{ PIO_PB15A_CANRX1, PIOB, ID_PIOB, PIO_PERIPH_A, PIO_DEFAULT }

/*! List of all CAN1 definitions. */
#define PINS_CAN1    PIN_CAN1_TXD, PIN_CAN1_RXD

/** CAN1 transceiver PIN RS. */
//#define PIN_CAN1_TR_RS_IDX        PIO_PE15_IDX
//#define PIN_CAN1_TR_RS_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)
//
///** CAN1 transceiver PIN EN. */
//#define PIN_CAN1_TR_EN_IDX        PIO_PE16_IDX
//#define PIN_CAN1_TR_EN_FLAGS      (PIO_TYPE_PIO_OUTPUT_0 | PIO_DEFAULT)

/** CAN1 PIN RX. */
#define PIN_CAN1_RX_IDX           (PIO_PB15_IDX)
#define PIN_CAN1_RX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)

/** CAN1 PIN TX. */
#define PIN_CAN1_TX_IDX           (PIO_PB14_IDX)
#define PIN_CAN1_TX_FLAGS         (PIO_PERIPH_A | PIO_DEFAULT)


#endif /* CAN_DRIVER_H_ */