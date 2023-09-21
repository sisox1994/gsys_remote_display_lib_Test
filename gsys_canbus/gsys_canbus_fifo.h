#ifndef GSYS_CANBUS_FIFO_H
#define GSYS_CANBUS_FIFO_H

#include "gsys_canbus_msg.h"

// CANBUS FIFO Size define 
#define FIFO_SIZE 30

// CANBUS FIFO Structure define 
typedef struct{

	CanMessage_t arr[FIFO_SIZE];
	int front;
	int rear;
	int count;

}CANBUS_FIFO_t;


// RX FIFO
void initCanRxFIFO(void);
void enqueue_CanRxMsg(CanMessage_t src);
CanMessage_t dequeue_CanRxMsg(void);

void canRxfifo_count_monitor(void);


// Tx FIFO
void initCanTxFIFO(void);
void enqueue_CanTxMsg(CanMessage_t src);
CanMessage_t dequeue_CanTxMsg(void);


#endif // GSYS_CANBUS_FIFO_H
