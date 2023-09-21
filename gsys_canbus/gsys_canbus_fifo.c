#include "gsys_canbus_fifo.h"

// CanRX FIFO Instance define 
static CANBUS_FIFO_t canRxfifo = { 0 };

// CanTx FIFO Instance define 
static CANBUS_FIFO_t canTxfifo = { 0 };


// This function monitors the CAN receive FIFO count and takes action if certain conditions are met.
void canRxfifo_count_monitor(){

	// Check if the count of elements in the CAN receive FIFO is zero.
	if (canRxfifo.count == 0){
		if ((canRxfifo.rear + 1) != (canRxfifo.front % FIFO_SIZE)){
			// If the conditions are met, reinitialize the CAN receive FIFO.
			initCanRxFIFO();
		}
	}
}

// Checks if a CANBUS FIFO is Full.
static int isFull(CANBUS_FIFO_t *fifo) {
	return fifo->count == FIFO_SIZE;
}

// Checks if a CANBUS FIFO is Empty.
static int isEmpty(CANBUS_FIFO_t *fifo) {
	return fifo->count == 0;
}



// [RX FIFO]
// CanRX FIFO Initial
void initCanRxFIFO() {

	canRxfifo.front = 0;
	canRxfifo.rear = -1;
	canRxfifo.count = 0;
}

// CanRX FIFO Enqueue
void enqueue_CanRxMsg(CanMessage_t src) {

	static uint8_t full_state;  // (0: Not Full, 1: Full)

	if (!isFull(&canRxfifo)) {
		canRxfifo.rear = (canRxfifo.rear + 1) % FIFO_SIZE;
		memcpy(&canRxfifo.arr[canRxfifo.rear], &src, sizeof(CanMessage_t));
		canRxfifo.count++;
		full_state = 0;
	}else {
		if (full_state == 0){
			full_state = 1;
			//printf("CanRX FIFO is full, enqueue operation failed.\n");
		}
	}
}

// CanRX FIFO Dequeue
CanMessage_t dequeue_CanRxMsg() {

	static uint8_t empty_state;  // (0: Not Empty, 1: Empty)
	CanMessage_t ret = { 0 };

	if (!isEmpty(&canRxfifo)) {
		memcpy(&ret, &canRxfifo.arr[canRxfifo.front], sizeof(CanMessage_t));
		canRxfifo.front = (canRxfifo.front + 1) % FIFO_SIZE;
		canRxfifo.count--;		
		empty_state = 0;
	}
	else {
		if (empty_state == 0){
			empty_state = 1;
			//printf("CanRX FIFO is empty, dequeue operation failed.\n");
		} 
	}

	return ret;
}






// [TX FIFO]
// CanTx FIFO Initial
void initCanTxFIFO() {

	canTxfifo.front = 0;
	canTxfifo.rear = -1;
	canTxfifo.count = 0;
}

// CanTx FIFO Enqueue
void enqueue_CanTxMsg(CanMessage_t src) {

	static uint8_t full_state;  // (0: Not Full, 1: Full)

	if (!isFull(&canTxfifo)) {
		canTxfifo.rear = (canTxfifo.rear + 1) % FIFO_SIZE;
		memcpy(&canTxfifo.arr[canTxfifo.rear], &src, sizeof(CanMessage_t));
		canTxfifo.count++;
		full_state = 0;
	}
	else {
		if (full_state == 0){
			full_state = 1;
			//printf("CanTx FIFO is full, enqueue operation failed.\n");
		}
	}
}

// CanTx FIFO Dequeue
CanMessage_t dequeue_CanTxMsg() {

	static uint8_t empty_state;  // (0: Not Empty, 1: Empty)

	CanMessage_t ret = { 0 };

	if (!isEmpty(&canTxfifo)) {
		memcpy(&ret, &canTxfifo.arr[canTxfifo.front], sizeof(CanMessage_t));
		canTxfifo.front = (canTxfifo.front + 1) % FIFO_SIZE;
		canTxfifo.count--;
		empty_state = 0;
	}
	else {
		if (empty_state == 0){
			empty_state = 1;
			//printf("CanTx FIFO is empty, dequeue operation failed.\n");
		}
	}

	return ret;
}
