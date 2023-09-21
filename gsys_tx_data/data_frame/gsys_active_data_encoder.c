#include "gsys_tx_data_encoder.h"
#include "gsys_ebike_data_collection.h"
#include "gsys_canbus_fifo.h"
#include "gsys_device_configurator.h"
#include "gsys_frame_data.h"
#include "gsys_data_event.h"
#include "gsys_data_active.h"

// Active Data Encoder
static CanMessage_t CanTxMsg_Buffer;

// Encodes and enqueues active data periodically based on the riding mode and role.
void ActiveDataEncoder() {

	static uint32_t T_cnt;          // Time counter to regulate the periodic encoding
	uint8_t         functionGroup;  // Function group for data encoding

	// Check if the time counter is a multiple of 50
	if (T_cnt % 50 == 0) {

		// Check if the system is not in OFF mode
		if (get_eBikeDataCollection()->systemStatus.adjustingMode != ADJUST_MODE_OFF){

			// Check if the system is not in service mode
			if (get_eBikeDataCollection()->systemStatus.adjustingMode > ADJUST_MODE_SERVICE || get_eBikeDataCollection()->systemStatus.adjustingMode < ADJUST_MODE_DATA_COLLECTION){

				// Check if the system is in riding mode 1
				if (get_eBikeDataCollection()->systemStatus.ridingMode == RIDING_MODE_ACTIVE) {

					// Determine the function group based on the presence of an error.
					if (IsDeviceErrorPresent()){
						functionGroup = Func_Event;
					}
					else{
						functionGroup = Func_Normal;
					}

					// Encode and enqueue Active Error data with the determined function group
					Active_Error(&CanTxMsg_Buffer, functionGroup);
					enqueue_CanTxMsg(CanTxMsg_Buffer);

					// Check if the device configuration's node_of_role is set to Node_Remote
					if(get_device_cfg()->node_of_role == Node_Remote){
						// Encode and enqueue Active Remote Command Button Status data with the determined function group
						Active_RemoteCmdBtnStatus(&CanTxMsg_Buffer, functionGroup);
						enqueue_CanTxMsg(CanTxMsg_Buffer);
					}

				}
			}
		}
	}

	T_cnt++;  // Increment the time counter
}


// Encodes and prepares an Active Error CAN message based on the function group and system role.
void Active_Error(CanMessage_t* canTxMsg, uint8_t functionGroup) {

	DataFrame_ID_t dataFrame = { 0 };  // Structure to hold CAN message header information
	EventCode_t    eventCode = { 0 };  // Initialize event code structure
	uint8_t        length = 0;         // Initialize the length of data

	// Configure the data frame header
	dataFrame.std.fugp = functionGroup;    // Set the function group
	dataFrame.std.nogp = get_device_cfg()->node_of_role; // Set the node group based on configuration
	dataFrame.std.dtyp = Typ_Active;       // Set the data type to active

	// Determine the address based on the configuration role
	switch (get_device_cfg()->role_of_gsystem) {
	case DISPLAY:
	case REMOTE1:
		dataFrame.std.addr = 0x0;
		break;
	case REMOTE2:
		dataFrame.std.addr = 0x8;
		break;
	}

	// Populate eventCode data
	length = sizeof(eventCode.Bytes);    // Set the length to the size of eventCode.Bytes

	if (IsDeviceErrorPresent()) eventCode.Msg.eval = 0x1;  // Set evaluation bit if there is an error

	eventCode.Msg.ecode = get_eBikeDataCollection()->errorStatus.DeviceErrorStatus;  // Set the error code

	// Copy eventCode data to the CAN message data
	memcpy(canTxMsg->Data, eventCode.Bytes, length);

	// Configure the CanMessage_t structure
	canTxMsg->ID = dataFrame.Id;         // Set the CAN message ID based on the data frame
	canTxMsg->DLC = length;              // Set the data length code
	canTxMsg->IDE = Standard;            // Set the identifier type to standard
	canTxMsg->RTR = DataFrame;
}



// Encodes and prepares an Active Remote Command and Button Status CAN message.
void Active_RemoteCmdBtnStatus(CanMessage_t* canTxMsg, uint8_t functionGroup) {

	DataFrame_ID_t           dataFrame = { 0 };  // Structure to hold CAN message header information
	uint8_t                  length = 0;         // Initialize the length of data
	Remote1CmdButtonStatus_t remote1CmdBtnStatus = { 0 };
	Remote2CmdButtonStatus_t remote2CmdBtnStatus = { 0 };

	// Configure the data frame header
	dataFrame.std.fugp = functionGroup;
	dataFrame.std.nogp = get_device_cfg()->node_of_role; // Set the node group based on configuration
	dataFrame.std.dtyp = Typ_Active;       // Set the data type to active

	// Determine the address based on the configuration role
	switch (get_device_cfg()->role_of_gsystem) {
	case REMOTE1:
		dataFrame.std.addr = 0x1;       // Set the address for REMOTE1 configuration role
		break;
	case REMOTE2:
		dataFrame.std.addr = 0x9;       // Set the address for REMOTE2 configuration role
		break;
	}

	// Populate remote Command & Button Status Data based on system role
	if (get_device_cfg()->role_of_gsystem == REMOTE1) {
		length = sizeof(remote1CmdBtnStatus.Bytes);  // Set the length to the size of remote1CmdBtnStatus.Bytes
		
		// [REMOTE1] Populate the values of button states and the remote command from local_remote1CmdBtnStatus to remote1CmdBtnStatus
		remote1CmdBtnStatus.Msg.btn_s1 = get_remote1CmdBtnStatus()->Msg.btn_s1;
		remote1CmdBtnStatus.Msg.btn_s2 = get_remote1CmdBtnStatus()->Msg.btn_s2;
		remote1CmdBtnStatus.Msg.btn_s3 = get_remote1CmdBtnStatus()->Msg.btn_s3;
		remote1CmdBtnStatus.Msg.btn_s4 = get_remote1CmdBtnStatus()->Msg.btn_s4;
		remote1CmdBtnStatus.Msg.btn_s5 = get_remote1CmdBtnStatus()->Msg.btn_s5;
		remote1CmdBtnStatus.Msg.btn_s6 = get_remote1CmdBtnStatus()->Msg.btn_s6;
		remote1CmdBtnStatus.Msg.btn_s7 = get_remote1CmdBtnStatus()->Msg.btn_s7;
		remote1CmdBtnStatus.Msg.btn_s8 = get_remote1CmdBtnStatus()->Msg.btn_s8;
		remote1CmdBtnStatus.Msg.rm_cmd = get_remote1CmdBtnStatus()->Msg.rm_cmd;

		// Copy remote1CmdBtnStatus data to CAN message data
		memcpy(canTxMsg->Data, remote1CmdBtnStatus.Bytes, length);
	}
	else if (get_device_cfg()->role_of_gsystem == REMOTE2) {
		length = sizeof(remote2CmdBtnStatus.Bytes);  // Set the length to the size of remote2CmdBtnStatus.Bytes

		// [REMOTE2] Populate the values of button states and the remote command from local_remote2CmdBtnStatus to remote2CmdBtnStatus
		remote2CmdBtnStatus.Msg.btn_s1  = get_remote2CmdBtnStatus()->Msg.btn_s1;
		remote2CmdBtnStatus.Msg.btn_s2  = get_remote2CmdBtnStatus()->Msg.btn_s2;
		remote2CmdBtnStatus.Msg.btn_s3  = get_remote2CmdBtnStatus()->Msg.btn_s3;
		remote2CmdBtnStatus.Msg.btn_s4  = get_remote2CmdBtnStatus()->Msg.btn_s4;
		remote2CmdBtnStatus.Msg.btn_s5  = get_remote2CmdBtnStatus()->Msg.btn_s5;
		remote2CmdBtnStatus.Msg.btn_s6  = get_remote2CmdBtnStatus()->Msg.btn_s6;
		remote2CmdBtnStatus.Msg.btn_s7  = get_remote2CmdBtnStatus()->Msg.btn_s7;
		remote2CmdBtnStatus.Msg.btn_s8  = get_remote2CmdBtnStatus()->Msg.btn_s8;
		remote2CmdBtnStatus.Msg.rm_cmd  = get_remote2CmdBtnStatus()->Msg.rm_cmd;
		remote2CmdBtnStatus.Msg.conn_rl = get_remote2CmdBtnStatus()->Msg.conn_rl;
		remote2CmdBtnStatus.Msg.conn_rr = get_remote2CmdBtnStatus()->Msg.conn_rr;

		// Copy remote2CmdBtnStatus data to CAN message data
		memcpy(canTxMsg->Data, remote2CmdBtnStatus.Bytes, length);
	}

	// Configure the CanMessage_t structure
	canTxMsg->ID = dataFrame.Id;         // Set the CAN message ID based on the data frame
	canTxMsg->DLC = length;              // Set the data length code
	canTxMsg->IDE = Standard;            // Set the identifier type to standard
	canTxMsg->RTR = DataFrame;
}
