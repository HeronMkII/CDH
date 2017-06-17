/*
 * queues.h
 *
 * Created: 3/18/2017 4:06:40 PM
 *  Author: Ali
 */ 
#include <stdlib.h>
#include <stdio.h>

typedef struct  
{
	uint8_t priority;			// Priority of the message
	uint32_t * message_id;		// Identifier (command type, sensor ID, etc.)
	uint32_t * data;			// pointer to data array 
	uint8_t data_size;			// number of elements in data array
} message;


typedef struct  
{
	message * messages;
	int length;
	int size;
} p_queue;

void init_pque(void);
void add_to_pque(p_queue pq, uint8_t priority, uint32_t * message_id, uint32_t * data, uint8_t size);