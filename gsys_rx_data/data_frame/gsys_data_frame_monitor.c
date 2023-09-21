#include "gsys_rx_data_decoder.h"


// Function to monitor and process CAN data frame messages
void DataFrameMonitor(CanMessage_t canRxMsg){

	EventDataMonitor(canRxMsg);    // Call the function to monitor and process event data in the received message
	ActiveDataMonitor(canRxMsg);   // Call the function to monitor and process active data in the received message

}
