#ifndef GSYS_REMOTE_FRAME_H
#define GSYS_REMOTE_FRAME_H

#include <stdint.h>

#pragma pack(push)   // preserves the current alignment setting.
#pragma pack(1)      // directive aligns structure members tightly in sequential order without padding, conserving memory by avoiding unnecessary gaps.

// CANBUS RemoteFrame ID structure definition.
typedef union{

	uint32_t Id;
	struct
	{
		uint32_t rsgp : 4,   // Response Group
		         rqgp : 4,   // Requestment Group
		         mogp : 3,   // Motion Group
		              : 21;
	}std;
	struct
	{
		uint32_t rsgp : 6,   // Response Group
		         rqgp : 6,   // Requestment Group
		         mogp : 6,   // Motion Group
		              : 14;
	}ext;

}RemoteFrame_ID_t;

#pragma pack(pop)   //restores the original alignment setting.
#endif // GSYS_REMOTE_FRAME_H
