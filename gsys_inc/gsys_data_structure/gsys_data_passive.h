#ifndef GSYS_PASSIVE_DATA_H
#define GSYS_PASSIVE_DATA_H

#include <stdint.h>

#pragma pack(push)   // preserves the current alignment setting.
#pragma pack(1)      // directive aligns structure members tightly in sequential order without padding, conserving memory by avoiding unnecessary gaps.

// G-system Data structure definition. {Passive Data} 

// [Remote/Display] ===========================================================================

// Data address = 0x0, 0x8  Firmware Version
typedef union{

	uint8_t Bytes[5];
	struct
	{
		uint8_t day : 5, // Day of publication.
		            : 3;
		uint8_t month;   // Month of publication.
		uint8_t year;    // Year of publication.
		uint8_t sn;      // Firnware version serial number.
		uint8_t type;    // RC Type.
	}Msg;

}FirmwareVersion_t;



// Data address = 0x1, 0x9  Hardware Version
typedef union{

	uint8_t Bytes[4];
	struct
	{
		uint8_t  month : 4, // Month of publication.
		               : 4;
		uint8_t  year;      // Year of publication.
		uint16_t sn;        // Hardware version serial number.
	}Msg;

}HardwareVersion_t;



// Data address = 0x2  Picture Version
typedef union{

	uint8_t Bytes[8];
	struct
	{
		uint8_t  icon;
		uint8_t  navi;
		uint8_t  number;
		uint8_t  Europe;
		uint8_t  t_ch;
		uint8_t  s_ch;
		uint8_t  Japan;
		uint8_t  Korea;
	}Msg;

}PictureVersion_t;



// Data address = 0x7,0xF  Confirmation 
typedef union{

	uint8_t Bytes[1];
	struct
	{
		uint8_t cfm : 1,  // Confirmation. (1: success, 0: failure)
		            : 7;
	}Msg;

}Confirmation_t;

#pragma pack(pop)   //restores the original alignment setting.
#endif // GSYS_PASSIVE_DATA_H
