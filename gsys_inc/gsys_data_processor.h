#ifndef GSYS_DATA_PROCESSOR_H
#define GSYS_DATA_PROCESSOR_H

#include "gsys_canbus_msg.h"

// CANBUS Rx Message decode to G-System Data Structure.
static void GSystemRxDecode(CanMessage_t canRxMsg);

// Place this function on a 1ms ticker.
void GSystemDataProcessor(void);

// Encodes and transmits system response and active data over CAN.
static void GSystemTxEncode(void);

// Define a Callback type, which is a function pointer with no return value, taking a CanMessage_t parameter.
typedef void(*Callback)(CanMessage_t);

// Transmit a CAN message and invoke the provided callback function.
static void CanTxMsg_Transmit(CanMessage_t src, Callback callback);

// External function declaration: Handle received CAN messages.
extern void CanTxMsg_Handler(CanMessage_t src);





// Reset the communication timeout counter and clear communication error status.
static void ResetCommunicationTimeoutCnt(void);

// Monitor and process timeouts in the communication signals.
static void SignalTimeoutMonitor(CanMessage_t canRxMsg);




// Monitor and acknowledge the remote button command based on the configuration role.
static void RemoteButtonCommandAckMonitor(void);

#endif // GSYS_DATA_PROCESSOR_H
