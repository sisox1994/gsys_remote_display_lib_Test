#include "gsys_tx_data_encoder.h"
#include "gsys_device_configurator.h"
#include "gsys_frame_remote.h"

// Function to encode and generate a remote frame CAN message
void RemoteFrameDataEncoder(CanMessage_t* canTxMsg){

    uint8_t           length = 0;           // Initialize the length of data
    RemoteFrame_ID_t  remoteFrame = { 0 };  // Define a structure to hold CAN message header information

    // Configure the remote frame header
    remoteFrame.std.mogp = Motion_Active_data_1;
    remoteFrame.std.rqgp = get_device_cfg()->node_of_role;
    remoteFrame.std.rsgp = Node_SmartGateway;

    // Configure the CanMessage_t structure
    canTxMsg->ID  = remoteFrame.Id;       // Set the CAN message ID based on the remote frame
    canTxMsg->DLC = length;               // Set the data length code
    canTxMsg->IDE = Standard;             // Set the identifier type to standard
    canTxMsg->RTR = RemoteFrame;          // Set the remote transmission request to data frame
}
