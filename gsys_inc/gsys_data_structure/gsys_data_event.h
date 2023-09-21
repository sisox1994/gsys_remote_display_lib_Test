#ifndef GSYS_EVENT_DATA_H
#define GSYS_EVENT_DATA_H

#include <stdint.h>

#pragma pack(push)   // preserves the current alignment setting.
#pragma pack(1)      // directive aligns structure members tightly in sequential order without padding, conserving memory by avoiding unnecessary gaps.


// [Any Node] ===========================================================================

// G-system Error Data structure definition

// Data address = 0x0, 0x8  Error
typedef union{

	uint8_t Bytes[2];
	struct
	{
		uint8_t eval : 1,   // Error value.  (1: error occurs, 0: error was gone)
		             : 7;
		uint8_t ecode;      // Error code.
	}Msg;

}EventCode_t;



// [Display Error] xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
typedef enum{

	ERR_Display_NoError                  = 0x50,
	ERR_DisplayFirmwareUpdateFailure     = 0x51,
	ERR_DisplayPCBAFailure_Flash_Error   = 0x52,
	ERR_DisplayCommunicationFailure      = 0x53,
	ERR_DisplayPCBAFailure_FontLib_Error = 0x54

}ErrCode_Display_t;


// [Remote1/Remote2 Error] xxxxxxxxxxxxxxxxxxxxxxxxxx
typedef enum{

	ERR_Remote_NoError                    = 0x40,
	ERR_RemoteFirmwareUpdateFailure       = 0x41,
	ERR_RemoteDataROMFailure              = 0x42,
	ERR_RideControlCommunicationIsInvalid = 0x43,
	ERR_RemoteFontlibFailure              = 0x44,
	ERR_RemoteChargingFunctionFailure     = 0x45

}ErrCode_Remote_t;


#pragma pack(pop)   //restores the original alignment setting.
#endif // GSYS_EVENT_DATA_H
