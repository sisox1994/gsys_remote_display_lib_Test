#ifndef GSYS_RX_DATA_DECODER_H
#define GSYS_RX_DATA_DECODER_H


#include "gsys_canbus_msg.h"
#include "gsys_frame_data.h"
#include "gsys_data_active.h"
#include "gsys_data_event.h"


// Function to monitor and process [data frame] CAN messages
void DataFrameMonitor(CanMessage_t canRxMsg);


// Function to monitor and process [remote frame] CAN messages
void RemoteFrameMonitor(CanMessage_t canRxMsg);





// [Event Data]
// Function to monitor and process event data in a received CAN message
void EventDataMonitor(CanMessage_t canRxMsg);

// Returns a pointer to the EventCode structure.
EventCode_t *get_EventCode(void);


// [Active Data]
void ActiveDataMonitor(CanMessage_t canRxMsg);

// Returns a pointer to the SG_RemoteControlCmd structure.
SG_RemoteControlCmd_t *get_SG_RemoteControlCmd(void);

// Returns a pointer to the SG_Display structure.
SG_Display_t *get_SG_Display(void);

// Returns a pointer to the SG_Cycling structure.
SG_Cycling_t *get_SG_Cycling(void);

// Returns a pointer to the specified SG_RemoteDisplayDataPage structure.
SG_RemoteDisplayDataPage0_t *get_SG_RemoteDisplayDataPage0(void);
SG_RemoteDisplayDataPage1_t *get_SG_RemoteDisplayDataPage1(void);
SG_RemoteDisplayDataPage2_t *get_SG_RemoteDisplayDataPage2(void);
SG_RemoteDisplayDataPage3_t *get_SG_RemoteDisplayDataPage3(void);
SG_RemoteDisplayDataPage4_t *get_SG_RemoteDisplayDataPage4(void);
SG_RemoteDisplayDataPage5_t *get_SG_RemoteDisplayDataPage5(void);

// Returns a pointer to the specified SG_MoblieDataPage structure.
SG_MoblieDataPage0_t *get_SG_MoblieDataPage0(void);
SG_MoblieDataPage1_t *get_SG_MoblieDataPage1(void);
SG_MoblieDataPage2_t *get_SG_MoblieDataPage2(void);
SG_MoblieDataPage3_t *get_SG_MoblieDataPage3(void);
SG_MoblieDataPage4_t *get_SG_MoblieDataPage4(void);
SG_MoblieDataPage5_t *get_SG_MoblieDataPage5(void);
SG_MoblieDataPage6_t *get_SG_MoblieDataPage6(void);

// Returns a pointer to the specified DU_CyclingData structure.
DU_CyclingData1_t *get_DU_CyclingData1(void);
DU_CyclingData2_t *get_DU_CyclingData2(void);

// Returns a pointer to the SG_EShifting structure.
SG_EShifting_t *get_SG_EShifting(void);

// Returns a pointer to the specified EnergyPack structure.
EnergyPack_Capacity_t    *get_EnergyPack_Capacity(void);
EnergyPack_DualBattery_t *get_EnergyPack_DualBattery(void);

// Returns a pointer to the specified Sub EnergyPack structure.
EnergyPack_Capacity_t    *get_SubEnergyPack_Capacity(void);
EnergyPack_DualBattery_t *get_SubEnergyPack_DualBattery(void);


#endif // GSYS_RX_DATA_DECODER_H
