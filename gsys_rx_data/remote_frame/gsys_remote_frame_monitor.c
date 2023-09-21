#include "gsys_rx_data_decoder.h"
#include "gsys_frame_remote.h"
#include "gsys_device_configurator.h"
#include "gsys_ebike_data_collection.h"


// Function to monitor and process remote frame CAN messages
void RemoteFrameMonitor(CanMessage_t canRxMsg){

    RemoteFrame_ID_t remoteFrame = { 0 };
    remoteFrame.Id = canRxMsg.ID;         // Set the ID of the remote frame from the received CAN message

    uint8_t responseGroup;
    uint8_t requestmentGroup;
    uint8_t motionGroup;

    // Determine the groups based on the identifier type of the received CAN message
    if (canRxMsg.IDE == Standard){
        requestmentGroup = remoteFrame.std.rqgp;
        responseGroup    = remoteFrame.std.rsgp;
        motionGroup      = remoteFrame.std.mogp;
    }
    else if (canRxMsg.IDE == Extended){   
        requestmentGroup = remoteFrame.ext.rqgp;
        responseGroup    = remoteFrame.ext.rsgp;
        motionGroup      = remoteFrame.ext.mogp;
    }

    // Check if the message requests a response from this node or all nodes
    if (responseGroup == get_device_cfg()->node_of_role || responseGroup == Node_AllNode){

        switch (motionGroup){
            case Motion_Heartbeat:
                get_eBikeDataCollection()->remoteAskStatus.Ask_Heartbeat = 1;
                // printf("Heartbeat request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;
            case Motion_Confirmation:
                get_eBikeDataCollection()->remoteAskStatus.Ask_Confirmation = 1;
                // printf("Confirmation request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;

            case Motion_Active_data_1:  // Response (Display/Remote1) Active
                get_eBikeDataCollection()->remoteAskStatus.Ask_Active_data_1 = 1;
                // printf("Active_data_1 request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;
            case Motion_Active_data_2:  // Response (Remote 2) Active
                get_eBikeDataCollection()->remoteAskStatus.Ask_Active_data_2 = 1;
                // printf("Active_data_2 request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;

            case Motion_Passive_data_1: // Response (Display/Remote1) Passive
                get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_1 = 1;
                // printf("Passive_data_1 request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;
            case Motion_Passive_data_2:
                get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_2 = 1;
                // printf("Passive_data_2 request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;
            case Motion_Passive_data_3: // Response (Remote2) Passive
                get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_3 = 1;
                // printf("Passive_data_3 request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;
            case Motion_Passive_data_4:
                get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_4 = 1;
                // printf("Passive_data_4 request(0x%X) response(0x%X)\n", requestmentGroup, responseGroup);
                break;
        }
    }
}
