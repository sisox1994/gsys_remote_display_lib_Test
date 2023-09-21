#include "gsys_rx_data_decoder.h"
#include "gsys_ebike_data_collection.h"

// G-system Error Data structure Instance define
static EventCode_t EventCode = { 0 };  // Data Address: 0x0,0x8


// Returns a pointer to the EventCode structure.
EventCode_t *get_EventCode() {
	return &EventCode;
}

// Function to monitor and process event data in a received CAN message
void EventDataMonitor(CanMessage_t canRxMsg){

	DataFrame_ID_t dataFrame = { 0 };   // Define a structure to hold CAN message header information
	dataFrame.Id = canRxMsg.ID;         // Set the ID of the data frame from the received CAN message

	// Standard Frame
	if (canRxMsg.IDE == Standard){

		// ========= Data Type: (Active Data) ================
		if (dataFrame.std.dtyp == Typ_Active){

			// ===== Function Group: (Event) {Error Message} ===============
			if (dataFrame.std.fugp == Func_Event){

				uint8_t eval = canRxMsg.Data[0];

				if (eval){
					if (dataFrame.std.addr == 0x0 || dataFrame.std.addr == 0x8){ // Data Address: 0x0, 0x8

						memcpy(EventCode.Bytes, canRxMsg.Data, sizeof(EventCode.Bytes));

						switch (EventCode.Msg.ecode){
						case 0x69:
							get_eBikeDataCollection()->errorStatus.ERRS_Speed_Sensor_Warning = 1;
							// printf("ERR_Speed_Sensor_Warning\n");
							break;
						case 0x2A:
						case 0x29:
							get_eBikeDataCollection()->errorStatus.ERRS_Smart_Gateway_Warning = 1;
							// printf("ERR_Smart_Gateway_Warning\n");
							break;
						case 0x65:
						case 0xF4:
						case 0xF7:
							get_eBikeDataCollection()->errorStatus.ERRS_Motor_Overheat = 1;
							// printf("ERR_Motor_Overheat\n");
							break;
						case 0x51:
						case 0x41:
							get_eBikeDataCollection()->errorStatus.ERRS_RideControl_Warning = 1;
							// printf("ERR_RideControl_Warning\n");
							break;
						case 0x24:
						case 0x43:
						case 0x53:
							get_eBikeDataCollection()->errorStatus.ERRS_COMM_Warning = 1;
							// printf("ERR_COMM_Warning\n");
							break;
						case 0x21:
						case 0x31:
						case 0x33:
						case 0x34:
						case 0x35:
						case 0x36:
						case 0x37:
						case 0x38:
						case 0x39:
						case 0x61:
						case 0x62:
						case 0x63:
						case 0x64:
						case 0x66:
						case 0x67:
						case 0x68:
						case 0x2E:
						case 0x3A:
						case 0x3B:
						case 0x3C:
						case 0x3D:
						case 0x3E:
						case 0x3F:
						case 0x6B:
						case 0x6C:
						case 0x6D:
						case 0x6E:
						case 0x6F:
						case 0xFC:
							get_eBikeDataCollection()->errorStatus.ERRS_SyncDrive_Warning = 1;
							// printf("ERR_SyncDrive_Warning\n");
							break;
						case 0x6A:
							get_eBikeDataCollection()->errorStatus.ERRS_SyncDrive_Error = 1;
							// printf("ERR_SyncDrive_Error\n");
							break;
						case 0x72:
						case 0x73:
						case 0xC1:
						case 0xC2:
						case 0xC3:
						case 0xC4:
						case 0xC5:
						case 0xC6:
						case 0xC7:
						case 0xC8:
						case 0xCA:
						case 0xCB:
						case 0xCC:
						case 0xCE:
						case 0xCF:
							get_eBikeDataCollection()->errorStatus.ERRS_EnergyPak_Warning = 1;
							// printf("ERR_EnergyPak_Warning\n");
							break;
						case 0x81:
						case 0x82:
						case 0x83:
						case 0x84:
						case 0x85:
						case 0x86:
							get_eBikeDataCollection()->errorStatus.ERRS_E_SHIFT_Warning = 1;
							// printf("ERR_E_SHIFT_Warning\n");
							break;
						}
					}
				}
			}
		}

	}
	// Extended Frame
	else if (canRxMsg.IDE == Extended){

	}

}
