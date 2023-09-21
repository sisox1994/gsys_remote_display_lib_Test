#ifndef GSYS_DATA_FRAME_H
#define GSYS_DATA_FRAME_H

#include <stdint.h>

#pragma pack(push)   // preserves the current alignment setting.
#pragma pack(1)      // directive aligns structure members tightly in sequential order without padding, conserving memory by avoiding unnecessary gaps.

// CANBUS DataFrame ID structure definition.
typedef union{

	uint32_t Id;
	struct
	{
		uint32_t addr : 4,  // Data Address
		         dtyp : 1,  // Data Type
		         nogp : 4,  // Node Group
		         fugp : 2,  // Function Group
		              : 21;
	}std;
	struct
	{
		uint32_t addr : 6,  // Data Address
		         dtyp : 3,  // Data Type
		         nogp : 6,  // Node Group
		         fugp : 3,  // Function Group
		              : 14;
	}ext;

}DataFrame_ID_t;

#pragma pack(pop)   //restores the original alignment setting.
#endif // GSYS_DATA_FRAME_H
