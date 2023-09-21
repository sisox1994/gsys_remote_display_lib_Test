#ifndef GSYS_TX_DATA_ENCODER_H
#define GSYS_TX_DATA_ENCODER_H

#include "gsys_canbus_msg.h"


// Encodes and enqueues active data periodically based on the riding mode and role.
void ActiveDataEncoder(void);

// Encodes and prepares an Active Error CAN message based on the function group and system role.
void Active_Error(CanMessage_t* canTxMsg, uint8_t functionGroup);

// Encodes and prepares an Active Remote Command and Button Status CAN message.
void Active_RemoteCmdBtnStatus(CanMessage_t* canTxMsg, uint8_t functionGroup);





// Encodes and enqueues various types of response and active data for CAN transmission.
void ResponseDataEncoder(void);

// Function to generate a CAN message containing firmware version information in response to a passive request
static void Passive_FirmwareVersion(CanMessage_t* canTxMsg);

// Function to generate a CAN message containing hardware version information in response to a passive request
static void Passive_HardwareVersion(CanMessage_t* canTxMsg);

// Function to generate a CAN message containing picture version information in response to a passive request
static void Passive_PictureVersion(CanMessage_t* canTxMsg);

// Function to generate a CAN message containing confirmation information in response to a passive request
static void Passive_Confirmation(CanMessage_t* canTxMsg);






// Function to encode and generate a remote frame CAN message
void RemoteFrameDataEncoder(CanMessage_t* canTxMsg);

#endif // GSYS_TX_DATA_ENCODER_H
