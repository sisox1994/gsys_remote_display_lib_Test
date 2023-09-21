#include "gsys_data_processor.h"
#include "gsys_rx_data_decoder.h"
#include "gsys_tx_data_encoder.h"
#include "gsys_canbus_fifo.h"
#include "gsys_device_configurator.h"
#include "gsys_ebike_data_collection.h"
#include "gsys_frame_data.h"
#include "gsys_frame_remote.h"

static AdjustingModeEnum m_amod = ADJUST_MODE_RESERVED;
static RidingModeEnum    m_rmod = RIDING_MODE_INACTIVE;

static CanMessage_t CanTxMsg_Buffer;

// Place this function on a 1ms ticker.
void GSystemDataProcessor(){

	static uint32_t T_cnt;

	//============= CAN RX FIFO dequeue ======================
	CanMessage_t CanRxMsg = { 0 };
	CanRxMsg = dequeue_CanRxMsg();

	// G-System CANBUS Rx Message Decode
	if (CanRxMsg.ID != 0){
		GSystemRxDecode(CanRxMsg);
	}

	SignalTimeoutMonitor(CanRxMsg);

	GSystemTxEncode();

	
	if (m_amod != get_eBikeDataCollection()->systemStatus.adjustingMode){
		m_amod = get_eBikeDataCollection()->systemStatus.adjustingMode;
		// printf("amod change -> %s(0x%X)\n", AdjustingModeStrings[m_amod],m_amod);
	}


	if (m_rmod != get_eBikeDataCollection()->systemStatus.ridingMode){
		m_rmod = get_eBikeDataCollection()->systemStatus.ridingMode;
		// printf("rmod = 0x%X\n", m_rmod);
	}

	// Monitor and acknowledge remote button commands.
	RemoteButtonCommandAckMonitor();

	// Check canRxfifo count every 2 second
	if (T_cnt % 2000 == 0){
		canRxfifo_count_monitor();
	}

	T_cnt++;
}





// CANBUS Rx Message decode to G-System Data Structure.
static void GSystemRxDecode(CanMessage_t canRxMsg){

	if (canRxMsg.RTR == RemoteFrame){
		RemoteFrameMonitor(canRxMsg);
	}
	else if (canRxMsg.RTR == DataFrame){
		DataFrameMonitor(canRxMsg);
	}

	EBikeDataPopulate();
}





// Transmits a CAN message and calls the provided callback function.
static void CanTxMsg_Transmit(CanMessage_t src, Callback callback){
	callback(src);
}

// Encodes and transmits system response and active data over CAN.
static void GSystemTxEncode() {

	// Encode system response data
	ResponseDataEncoder();

	// Encode active data
	ActiveDataEncoder();

	// Dequeue a CAN transmission message from the CAN TX FIFO
	CanMessage_t CanTxMsg = { 0 };
	CanTxMsg = dequeue_CanTxMsg();

	// Check if a valid CAN message was dequeued
	if (CanTxMsg.ID != 0) {
		// Transmit the CAN message and handle the transmission with CanTxMsg_Handler callback
		CanTxMsg_Transmit(CanTxMsg, CanTxMsg_Handler);
	}
}





#define COMMUNICATION_TIMEOUT 15  // (x100ms)
#define RESPONSE_TIMEOUT      10  // (x100ms)
#define ASK_SG_RETRY_TIMES     5  // Ask Smart Gateway active data (5x)

static uint8_t CommunicationTimeoutCnt = 0;
static uint8_t ResponseTimeoutCnt      = 0;
static uint8_t AskSmartGatewayRetryCnt = 0;

// Reset the communication timeout counter and clear communication error status.
static void ResetCommunicationTimeoutCnt(){

	CommunicationTimeoutCnt = 0;
	AskSmartGatewayRetryCnt = 0;

	// Clear Communication Error Status based on the node
	if (get_device_cfg()->node_of_role == Node_Remote){
		if (get_eBikeDataCollection()->errorStatus.DeviceErrorStatus == ERR_RideControlCommunicationIsInvalid){
			DeviceErrorStatusConfiguration(ERR_Remote_NoError);
		}
		
	}
	else if (get_device_cfg()->node_of_role == Node_Display){
		if (get_eBikeDataCollection()->errorStatus.DeviceErrorStatus == ERR_DisplayCommunicationFailure){
			DeviceErrorStatusConfiguration(ERR_Display_NoError);
		}
	}

}


// Monitor and process timeouts in the communication signals.
static void SignalTimeoutMonitor(CanMessage_t canRxMsg){

	static uint32_t T_cnt;

	if (canRxMsg.RTR == RemoteFrame){

		RemoteFrame_ID_t remoteFrame = { 0 };  // Define a structure to hold CAN message header information
		remoteFrame.Id = canRxMsg.ID;          // Set the ID of the remote frame from the received CAN message

		uint8_t responseGroup;
		uint8_t requestmentGroup;
		uint8_t motionGroup;

		// Determine the groups based on the identifier type of the received CAN message
		if (canRxMsg.IDE == Standard){
			requestmentGroup = remoteFrame.std.rqgp;
			responseGroup =    remoteFrame.std.rsgp;
			motionGroup =      remoteFrame.std.mogp;
		}
		else if (canRxMsg.IDE == Extended){
			requestmentGroup = remoteFrame.ext.rqgp;
			responseGroup =    remoteFrame.ext.rsgp;
			motionGroup =      remoteFrame.ext.mogp;
		}

		// Check if the message requests a response from this node or all nodes
		if (responseGroup == get_device_cfg()->node_of_role || responseGroup == Node_AllNode){

			if (motionGroup == Motion_Heartbeat){
				ResetCommunicationTimeoutCnt();
			}
		}

	}
	else if (canRxMsg.RTR == DataFrame){

		DataFrame_ID_t dataFrame = { 0 };      // Define a structure to hold CAN message header information
		dataFrame.Id = canRxMsg.ID;            // Set the ID of the data frame from the received CAN message

		// Standard Frame ===================================================
		if (canRxMsg.IDE == Standard){

			// ============ Data Type: (Active Data) ================
			if (dataFrame.std.dtyp == Typ_Active){

				// ====== Function Group: (Normal, Response, Event) ======
				switch (dataFrame.std.fugp){
				case Func_Event:
				case Func_Response:
				case Func_Normal:
					// ======= Node Group: [SmartGateway] =======
					if (dataFrame.std.nogp == Node_SmartGateway){
						if (dataFrame.std.addr == 0x1){							
							ResetCommunicationTimeoutCnt();
						}
					}
				}
				// =======================================================
			}

		}
		// Extended Frame ===================================================
		else if (canRxMsg.IDE == Extended){

			// ============ Data Type: (Active Data) ================
			if (dataFrame.ext.dtyp == Typ_Active){

				// ====== Function Group: (Normal, Response, Event) ======
				switch (dataFrame.ext.fugp){
				case Func_Event:
				case Func_Response:
				case Func_Normal:
					// ======= Node Group: [SmartGateway] =======
					if (dataFrame.ext.nogp == Node_SmartGateway){
						if (dataFrame.ext.addr == 0x1){							
							ResetCommunicationTimeoutCnt();
						}
					}
					break;
				};
			}
		}
	}

	// Timeout Process
	if (T_cnt % 100 == 0){ //100 ms

		// Handle response timeout
		if (CommunicationTimeoutCnt == (COMMUNICATION_TIMEOUT + 1)){
		
			if (ResponseTimeoutCnt == RESPONSE_TIMEOUT){   
				ResponseTimeoutCnt = (RESPONSE_TIMEOUT + 1);

				// Setting Device Error Status
				if (get_device_cfg()->node_of_role == Node_Remote){					
					DeviceErrorStatusConfiguration(ERR_RideControlCommunicationIsInvalid);
				}
				else if (get_device_cfg()->node_of_role == Node_Display){
					DeviceErrorStatusConfiguration(ERR_DisplayCommunicationFailure);
				}

				// Activate Riding Mode to Send Active Event Data every 50 ms.
				get_eBikeDataCollection()->systemStatus.ridingMode = RIDING_MODE_ACTIVE;  // 不太好的做法，但是先看看會有衝突嗎?
			
				// printf("Ask Response Timeout!!\n");
			}
			else if (ResponseTimeoutCnt < RESPONSE_TIMEOUT){
				ResponseTimeoutCnt++;
			}
		}

		// Handle communication timeout
		if (CommunicationTimeoutCnt == COMMUNICATION_TIMEOUT){

			// Check if the system is not in off mode
			if (get_eBikeDataCollection()->systemStatus.adjustingMode != ADJUST_MODE_OFF){
				// Check if the system is not in service mode
				if (get_eBikeDataCollection()->systemStatus.adjustingMode > ADJUST_MODE_SERVICE || get_eBikeDataCollection()->systemStatus.adjustingMode < ADJUST_MODE_DATA_COLLECTION){

					// 1.5s send remoteframe ask Smart Gateway active data (5x)
					if(AskSmartGatewayRetryCnt == ASK_SG_RETRY_TIMES){
						CommunicationTimeoutCnt = (COMMUNICATION_TIMEOUT + 1);
						ResponseTimeoutCnt = 0;
						// printf("Communication Timeout!!\n");
					}else if(AskSmartGatewayRetryCnt < ASK_SG_RETRY_TIMES){
						RemoteFrameDataEncoder(&CanTxMsg_Buffer);
						enqueue_CanTxMsg(CanTxMsg_Buffer);
						AskSmartGatewayRetryCnt++;
					}
				}
			}

		}
		else if (CommunicationTimeoutCnt < COMMUNICATION_TIMEOUT){ // Communication Timeout 1.5s

			// Check if the system is not in off mode
			if (get_eBikeDataCollection()->systemStatus.adjustingMode != ADJUST_MODE_OFF){
				// Check if the system is not in service mode
				if (get_eBikeDataCollection()->systemStatus.adjustingMode > ADJUST_MODE_SERVICE || get_eBikeDataCollection()->systemStatus.adjustingMode < ADJUST_MODE_DATA_COLLECTION){
					CommunicationTimeoutCnt++;
				}
			}

		}

	}

	T_cnt++;
}





// Monitor and acknowledge the remote button command based on the configuration role.
static void RemoteButtonCommandAckMonitor(){

	if (get_device_cfg()->role_of_gsystem == REMOTE1){
		if (get_eBikeDataCollection()->systemStatus.remoteCmdAck == get_remote1CmdBtnStatus()->Msg.rm_cmd){
			get_remote1CmdBtnStatus()->Msg.rm_cmd = REMOTE_CMD_NO_COMMAND;
		}
	}
	else if (get_device_cfg()->role_of_gsystem == REMOTE2){
		if (get_eBikeDataCollection()->systemStatus.remoteCmdAck == get_remote2CmdBtnStatus()->Msg.rm_cmd){
			get_remote2CmdBtnStatus()->Msg.rm_cmd = REMOTE_CMD_NO_COMMAND;
		}
	}

}
