#ifndef GSYS_CANBUS_MESSAGE_H
#define GSYS_CANBUS_MESSAGE_H

#include <stdint.h>
#include "string.h"

#define Standard 0x0
#define Extended 0x1

#define DataFrame    0x0
#define RemoteFrame  0x1

// CANBUS Message structure definition.
typedef struct{

	uint32_t ID;      // identifier
	uint32_t DLC;     // Data length
	uint8_t  RTR;     // 0 : Dataframe , 1 : Remoteframe  
	uint8_t  IDE;     // 0 : Standard  , 1 : Extended
	uint8_t  Data[8];

}CanMessage_t;



// Role Definition. (GIANT E-Parts)
typedef enum{

	DISPLAY = 0x0,
	REMOTE1 = 0x1,
	REMOTE2 = 0x2

}RoleDefinition_t;



// [DataFrame]
// G-system Function Group definition.  
typedef enum{

	Func_Networkmgr = 0x0,
	Func_Event      = 0x1,
	Func_Response   = 0x2,
	Func_Normal     = 0x3,

}Function_Group_t;

// G-system Node Group definition.
typedef enum{

	// std
	Node_AllNode          = 0x0,  // All Node
	Node_ServiceTool      = 0x1,
	Node_SmartGateway     = 0x2,  // UserInterface
	Node_Sensor           = 0x3,
	Node_Remote           = 0x4,
	Node_Display          = 0x5,
	Node_DriveChain       = 0x6,
	Node_YAMAHA           = 0x7,
	Node_EShifting        = 0x8,
	Node_ESuspension      = 0x9,
	Node_SMP              = 0xA,
	Node_SubEnergyPack    = 0xB,
	Node_EnergyPack       = 0xC,
	Node_PANSONIC         = 0xD,
	Node_Charger          = 0xE,
	Node_GiantApplication = 0xF,
	
	// ext
	Node_IoTDevice        = 0x10, 
	Node_Radar            = 0x11,
	Node_TailLight        = 0x12,
	Node_ExCharger        = 0x3F,

}Node_Group_t;

// G-system Data Type definition.
typedef enum{

	Typ_Active  = 0x0,
	Typ_Passive = 0x1,

}Data_Type_t;



// [RemoteFrame]
// G-system Motion Group definition.
typedef enum{

	Motion_Heartbeat      = 0x0,
	Motion_Confirmation   = 0x1,
	Motion_Active_data_1  = 0x2,
	Motion_Active_data_2  = 0x3,
	Motion_Passive_data_1 = 0x4,
	Motion_Passive_data_2 = 0x5,
	Motion_Passive_data_3 = 0x6,
	Motion_Passive_data_4 = 0x7,

}Motion_Group_t;

#endif // GSYS_CANBUS_MESSAGE_H
