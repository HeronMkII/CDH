/*
 * File Name:     can_driver.c
 * Purpose:		  
 * Author:        Ali Haydaroglu
 * 
 */ 
#include "can_driver.h"

/*  can_init_asf
	
	Purpose: Initialization code taken from ASF: http://asf.atmel.com/docs/latest/sam3x/html/sam_can_quickstart.html
*/


void CAN1_Handler(void)
{
	gpio_set_pin_low(LED);
}



void can_init_asf(){
	
	uint32_t ul_sysclk = sysclk_get_cpu_hz();
	
	
	
	pmc_enable_periph_clk(ID_CAN0);
	pmc_enable_periph_clk(ID_CAN1);
	
	can_init(CAN0, ul_sysclk, CAN_BPS_50K);
	can_init(CAN1, ul_sysclk, CAN_BPS_50K);
	

	
	can_reset_all_mailbox(CAN0);
	can_reset_all_mailbox(CAN1);
	

	
	can1_mailbox.ul_mb_idx = 0;
	can1_mailbox.uc_obj_type = CAN_MB_RX_MODE;
	can1_mailbox.ul_id_msk = CAN_MAM_MIDvA_Msk | CAN_MAM_MIDvB_Msk;
	can1_mailbox.ul_id = CAN_MID_MIDvA(0x00);
	can_mailbox_init(CAN1, &can1_mailbox);
	
	can0_mailbox.ul_mb_idx = 0;
	can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	can0_mailbox.uc_tx_prio = 15;
	can0_mailbox.uc_id_ver = 0;
	can0_mailbox.ul_id_msk = 0;
	can_mailbox_init(CAN0, &can0_mailbox);
	
	can_disable_interrupt(CAN0, CAN_DISABLE_ALL_INTERRUPT_MASK);
	can_disable_interrupt(CAN1, CAN_DISABLE_ALL_INTERRUPT_MASK);
	can_enable_interrupt(CAN1, GLOBAL_MAILBOX_MASK);
	NVIC_EnableIRQ(CAN1_IRQn);
}




/*  can_initialize
	
	Purpose: This function initializes a both CAN controllers with as 
	many mailboxes as specified, operating according to the parameters
	here
	
	Note: Currently, CAN0 is a TX controller and CAN1 is an RX controller
	
	Return:
		1 if successful, 0 otherwise
*/
uint8_t can_initialize(){
	
	/* Peripheral clock enable */
	uint32_t ul_mck = sysclk_get_cpu_hz();						
	pmc_enable_periph_clk(ID_CAN0);									
	pmc_enable_periph_clk(ID_CAN1);
	
	/* Initialize baudrates, return 0 if initialization fails */
	if (!(can_init(CAN0,ul_mck,CAN_BPS_250K) & can_init(CAN1,ul_mck,CAN_BPS_250K))){
		return 0;
	}
	
	/* Disable unused mailboxes */
	can_reset_all_mailbox(CAN0);
	can_reset_all_mailbox(CAN1);
	
	/* Set up interrupts */
	can_disable_interrupt(CAN0, CAN_DISABLE_ALL_INTERRUPT_MASK);	//CAN0 will be the TX controller
	can_enable_interrupt(CAN1, CAN_IER_MB0);						//CAN1 will be RX, enable interrupts
	NVIC_EnableIRQ(CAN1_IRQn);
	
	/* Initialize mailboxes here */
	can_make_mailbox(setup_mb, CAN0_MB0, CAN0_DIR, CAN0_MB0_PRIO);
	can_mailbox_init(CAN0, setup_mb);
	
	can_make_mailbox(setup_mb, CAN1_MB0, CAN1_DIR, CAN1_MB0_PRIO);
	can_mailbox_init(CAN1, setup_mb);
	
	/* Initialization successful */
	return 1;
}

/*  can_init_mailbox and can_make_mailbox
	
	Purpose: Makes a single CAN mailbox struct on either 
	controller for use as a TX or RX mailbox
	
	Note: Out of the 6 mailbox modes, only two can be initialized here. 
	The function assumes standard (not extended) frames
	
	Parameters: 
		data_direction	CAN_TX or CAN_RX, sets the mailbox object type
		mailbox_id		CANn_MBx where n = 0,1; x = 0-7	
		priority		Transmission priority (0 for RX)
*/

void can_make_mailbox(can_mb_conf_t *p_mailbox, uint8_t mailbox_id, uint8_t data_direction, uint8_t priority){
	reset_mailbox_conf(p_mailbox);
	
	if (data_direction == CAN_TX){			        //Transmission mailbox setup
		p_mailbox->uc_obj_type = CAN_MB_TX_MODE;
		p_mailbox->ul_id = CAN_MID_MIDvA(mailbox_id);
		p_mailbox->uc_tx_prio = priority;
	}
	else {											 //Receiving mailbox setup
		p_mailbox->uc_obj_type = CAN_MB_RX_MODE;
		p_mailbox->ul_id_msk = CAN_MID_MIDvA_Msk | CAN_MID_MIDvB_Msk;
		p_mailbox->ul_id = CAN_MID_MIDvA(mailbox_id);
	}
	
	if (mailbox_id > 8) {							//Map global CAN mailbox numbers (1-16) to controller numbers (0-7)
		p_mailbox->ul_mb_idx = mailbox_id - 9;		//Mailbox is on CAN1
	}
	else {
		p_mailbox->ul_mb_idx = mailbox_id - 1;		//Mailbox is on CAN0
	}
}

/*
	reset_mailbox_conf
	
	Purpose: This function resets a mailbox object
	Parameters:
		p_mailbox		Pointer to mailbox object
*/
void reset_mailbox_conf(can_mb_conf_t *p_mailbox)
{
	p_mailbox->ul_mb_idx = 0;
	p_mailbox->uc_obj_type = 0;
	p_mailbox->uc_id_ver = 0;
	p_mailbox->uc_length = 0;
	p_mailbox->uc_tx_prio = 0;
	p_mailbox->ul_status = 0;
	p_mailbox->ul_id_msk = 0;
	p_mailbox->ul_id = 0;
	p_mailbox->ul_fid = 0;
	p_mailbox->ul_datal = 0;
	p_mailbox->ul_datah = 0;
}

uint8_t can_send(uint32_t low, uint32_t high, uint8_t mailbox_id, uint8_t msg_ID, uint8_t priority){
	
	/*
	uint8_t mb = mailbox_id - 1;
	
	can_make_mailbox(tx_mb, mailbox_id, CAN_TX, priority);
	can_mailbox_init(CAN0, tx_mb);
	
	tx_mb->ul_id = CAN_MID_MIDvA(msg_ID);
	tx_mb->ul_datal = low;
	tx_mb->ul_datah = high;
	tx_mb->uc_length = MAX_CAN_FRAME_DATA_LEN;
	z
	can_mailbox_write(CAN0, tx_mb);					    //Assume TX on CAN0
	can_global_send_transfer_cmd(CAN0, (0x1u << mb));	//From definition of CAN_TCR_MB7, saves a switch statement
	//can_global_send_transfer_cmd(CAN0, CAN_TCR_MB7);
	*/
	
	/* atmel code, for debugging */
	can0_mailbox.ul_mb_idx = 0;
	can0_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	can0_mailbox.uc_tx_prio = 15;
	can0_mailbox.uc_id_ver = 0;
	can0_mailbox.ul_id_msk = 0;
	can_mailbox_init(CAN0, &can0_mailbox);
	can0_mailbox.ul_id = CAN_MID_MIDvA(0x00);
	can0_mailbox.ul_datal = 0x0F0F0F0F;
	can0_mailbox.ul_datah = 0x0F0F0F0F;
	can0_mailbox.uc_length = 8;
	can_mailbox_write(CAN0, &can0_mailbox);
	
	return 0;
}