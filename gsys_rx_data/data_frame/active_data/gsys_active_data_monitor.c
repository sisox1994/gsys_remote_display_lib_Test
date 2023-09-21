#include "gsys_rx_data_decoder.h"


// G-System Data structure Instance define

// [Smart Gateway] ===================================================
static SG_RemoteControlCmd_t SG_RemoteControlCmd = { 0 }; // Data Address: 0x1
static SG_Display_t          SG_Display          = { 0 }; // Data Address: 0x2
static SG_Cycling_t          SG_Cycling          = { 0 }; // Data Address: 0x3       

// Data Address: 0x6
static SG_RemoteDisplayDataPage0_t SG_RemoteDisplayDataPage0 = { 0 };
static SG_RemoteDisplayDataPage1_t SG_RemoteDisplayDataPage1 = { 0 };
static SG_RemoteDisplayDataPage2_t SG_RemoteDisplayDataPage2 = { 0 };
static SG_RemoteDisplayDataPage3_t SG_RemoteDisplayDataPage3 = { 0 };
static SG_RemoteDisplayDataPage4_t SG_RemoteDisplayDataPage4 = { 0 };
static SG_RemoteDisplayDataPage5_t SG_RemoteDisplayDataPage5 = { 0 };

// Data Address: 0x7
static SG_MoblieDataPage0_t SG_MoblieDataPage0 = { 0 };
static SG_MoblieDataPage1_t SG_MoblieDataPage1 = { 0 };
static SG_MoblieDataPage2_t SG_MoblieDataPage2 = { 0 };
static SG_MoblieDataPage3_t SG_MoblieDataPage3 = { 0 };
static SG_MoblieDataPage4_t SG_MoblieDataPage4 = { 0 };
static SG_MoblieDataPage5_t SG_MoblieDataPage5 = { 0 };
static SG_MoblieDataPage6_t SG_MoblieDataPage6 = { 0 };

static SG_EShifting_t SG_EShifting;  // Data Address: 0xF

// [Drive Chain] ===================================================
static DU_CyclingData1_t DU_CyclingData1 = { 0 };  // Data Address: 0x2
static DU_CyclingData2_t DU_CyclingData2 = { 0 };  // Data Address: 0x3

// [Energy pack] ===================================================
static EnergyPack_Capacity_t    EnergyPack_Capacity    = { 0 };  // Data Address: 0x1
static EnergyPack_DualBattery_t EnergyPack_DualBattery = { 0 };  // Data Address: 0x4

// [Sub Energy pack] ===================================================
static EnergyPack_Capacity_t    SubEnergyPack_Capacity    = { 0 }; // Data Address: 0x1
static EnergyPack_DualBattery_t SubEnergyPack_DualBattery = { 0 }; // Data Address: 0x4



// Function to monitor and process active data in a received CAN message
void ActiveDataMonitor(CanMessage_t canRxMsg){

	DataFrame_ID_t dataFrame = { 0 };  // Define a structure to hold CAN message header information
	dataFrame.Id = canRxMsg.ID;        // Set the ID of the data frame from the received CAN message

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
					uint8_t Page = 0x0;
					switch (dataFrame.std.addr){

					case 0x1:
						memcpy(get_SG_RemoteControlCmd()->Bytes, canRxMsg.Data, sizeof(get_SG_RemoteControlCmd()->Bytes));
						break;
					case 0x2:
						memcpy(get_SG_Display()->Bytes, canRxMsg.Data, sizeof(get_SG_Display()->Bytes));
						break;
					case 0x3:
						memcpy(get_SG_Cycling()->Bytes, canRxMsg.Data, sizeof(get_SG_Cycling()->Bytes));
						break;
					case 0x6:
						Page = canRxMsg.Data[0];
						if (Page == 0) memcpy(get_SG_RemoteDisplayDataPage0()->Bytes, canRxMsg.Data, sizeof(SG_RemoteDisplayDataPage0));
						else if (Page == 1) memcpy(get_SG_RemoteDisplayDataPage1()->Bytes, canRxMsg.Data, sizeof(SG_RemoteDisplayDataPage1));
						else if (Page == 2) memcpy(get_SG_RemoteDisplayDataPage2()->Bytes, canRxMsg.Data, sizeof(SG_RemoteDisplayDataPage2));
						else if (Page == 3) memcpy(get_SG_RemoteDisplayDataPage3()->Bytes, canRxMsg.Data, sizeof(SG_RemoteDisplayDataPage3));
						else if (Page == 4) memcpy(get_SG_RemoteDisplayDataPage4()->Bytes, canRxMsg.Data, sizeof(SG_RemoteDisplayDataPage4));
						else if (Page == 5) memcpy(get_SG_RemoteDisplayDataPage5()->Bytes, canRxMsg.Data, sizeof(SG_RemoteDisplayDataPage5));
						break;
					case 0x7:
						Page = canRxMsg.Data[0];
						if (Page == 0) memcpy(get_SG_MoblieDataPage0()->Bytes, canRxMsg.Data, sizeof(get_SG_MoblieDataPage0()->Bytes));
						else if (Page == 1) memcpy(get_SG_MoblieDataPage1()->Bytes, canRxMsg.Data, sizeof(get_SG_MoblieDataPage1()->Bytes));
						else if (Page == 2) memcpy(get_SG_MoblieDataPage2()->Bytes, canRxMsg.Data, sizeof(get_SG_MoblieDataPage2()->Bytes));
						else if (Page == 3) memcpy(get_SG_MoblieDataPage3()->Bytes, canRxMsg.Data, sizeof(get_SG_MoblieDataPage3()->Bytes));
						else if (Page == 4) memcpy(get_SG_MoblieDataPage4()->Bytes, canRxMsg.Data, sizeof(get_SG_MoblieDataPage4()->Bytes));
						else if (Page == 5) memcpy(get_SG_MoblieDataPage5()->Bytes, canRxMsg.Data, sizeof(get_SG_MoblieDataPage5()->Bytes));
						else if (Page == 6) memcpy(get_SG_MoblieDataPage6()->Bytes, canRxMsg.Data, sizeof(get_SG_MoblieDataPage6()->Bytes));
						break;
					case 0xF:
						memcpy(get_SG_EShifting()->Bytes, canRxMsg.Data, sizeof(get_SG_EShifting()->Bytes));
						break;
					}

				}
				// ======= Node Group: [DriveChain] =======
				if (dataFrame.std.nogp == Node_DriveChain){
					switch (dataFrame.std.addr){

					case 0x2:
						memcpy(get_DU_CyclingData1()->Bytes, canRxMsg.Data, sizeof(get_DU_CyclingData1()->Bytes));
						break;
					case 0x3:
						memcpy(get_DU_CyclingData2()->Bytes, canRxMsg.Data, sizeof(get_DU_CyclingData2()->Bytes));
						break;
					}
				}
				// ======= Node Group: [EnergyPack] =======
				if (dataFrame.std.nogp == Node_EnergyPack){
					switch (dataFrame.std.addr){

					case 0x1:
						memcpy(get_EnergyPack_Capacity()->Bytes, canRxMsg.Data, sizeof(get_EnergyPack_Capacity()->Bytes));
						break;
					case 0x4:
						memcpy(get_EnergyPack_DualBattery()->Bytes, canRxMsg.Data, sizeof(get_EnergyPack_DualBattery()->Bytes));
						break;
					}
				}
				// ======= Node Group: [Sub EnergyPack] =======
				if (dataFrame.std.nogp == Node_SubEnergyPack){
					switch (dataFrame.std.addr){

					case 0x1:
						memcpy(get_SubEnergyPack_Capacity()->Bytes, canRxMsg.Data, sizeof(get_SubEnergyPack_Capacity()->Bytes));
						break;
					case 0x4:
						memcpy(get_SubEnergyPack_DualBattery()->Bytes, canRxMsg.Data, sizeof(get_SubEnergyPack_DualBattery()->Bytes));
						break;
					}
				}
				// =========================================
				break;

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
				// ======= Node Group: [Radar] =======
				if (dataFrame.ext.nogp == Node_Radar){
					//-------- TBD --------------
				}
				break;
			};
		}
	}


}





// Returns a pointer to the SG_RemoteControlCmd structure.
SG_RemoteControlCmd_t *get_SG_RemoteControlCmd() {
	return &SG_RemoteControlCmd;
}

// Returns a pointer to the SG_Display structure.
SG_Display_t *get_SG_Display() {
	return &SG_Display;
}

// Returns a pointer to the SG_Cycling structure.
SG_Cycling_t *get_SG_Cycling() {
	return &SG_Cycling;
}

// Returns a pointer to the specified SG_RemoteDisplayDataPage structure.
SG_RemoteDisplayDataPage0_t *get_SG_RemoteDisplayDataPage0() {
	return &SG_RemoteDisplayDataPage0;
}

SG_RemoteDisplayDataPage1_t *get_SG_RemoteDisplayDataPage1() {
	return &SG_RemoteDisplayDataPage1;
}

SG_RemoteDisplayDataPage2_t *get_SG_RemoteDisplayDataPage2() {
	return &SG_RemoteDisplayDataPage2;
}

SG_RemoteDisplayDataPage3_t *get_SG_RemoteDisplayDataPage3() {
	return &SG_RemoteDisplayDataPage3;
}

SG_RemoteDisplayDataPage4_t *get_SG_RemoteDisplayDataPage4() {
	return &SG_RemoteDisplayDataPage4;
}

SG_RemoteDisplayDataPage5_t *get_SG_RemoteDisplayDataPage5() {
	return &SG_RemoteDisplayDataPage5;
}

// Returns a pointer to the specified SG_MoblieDataPage structure.
SG_MoblieDataPage0_t *get_SG_MoblieDataPage0() {
	return &SG_MoblieDataPage0;
}

SG_MoblieDataPage1_t *get_SG_MoblieDataPage1() {
	return &SG_MoblieDataPage1;
}

SG_MoblieDataPage2_t *get_SG_MoblieDataPage2() {
	return &SG_MoblieDataPage2;
}

SG_MoblieDataPage3_t *get_SG_MoblieDataPage3() {
	return &SG_MoblieDataPage3;
}

SG_MoblieDataPage4_t *get_SG_MoblieDataPage4() {
	return &SG_MoblieDataPage4;
}

SG_MoblieDataPage5_t *get_SG_MoblieDataPage5() {
	return &SG_MoblieDataPage5;
}

SG_MoblieDataPage6_t *get_SG_MoblieDataPage6() {
	return &SG_MoblieDataPage6;
}

// Returns a pointer to the specified DU_CyclingData structure.
DU_CyclingData1_t *get_DU_CyclingData1() {
	return &DU_CyclingData1;
}

DU_CyclingData2_t *get_DU_CyclingData2() {
	return &DU_CyclingData2;
}

// Returns a pointer to the SG_EShifting structure.
SG_EShifting_t *get_SG_EShifting() {
	return &SG_EShifting;
}

// Returns a pointer to the specified EnergyPack structure.
EnergyPack_Capacity_t *get_EnergyPack_Capacity() {
	return &EnergyPack_Capacity;
}

EnergyPack_DualBattery_t *get_EnergyPack_DualBattery() {
	return &EnergyPack_DualBattery;
}

// Returns a pointer to the specified Sub EnergyPack structure.
EnergyPack_Capacity_t *get_SubEnergyPack_Capacity() {
	return &SubEnergyPack_Capacity;
}

EnergyPack_DualBattery_t *get_SubEnergyPack_DualBattery() {
	return &SubEnergyPack_DualBattery;
}
