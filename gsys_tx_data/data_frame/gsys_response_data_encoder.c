#include "gsys_canbus_fifo.h"
#include "gsys_tx_data_encoder.h"
#include "gsys_ebike_data_collection.h"
#include "gsys_device_configurator.h"
#include "gsys_frame_data.h"
#include "gsys_data_passive.h"


// Response Data Encoder
static CanMessage_t CanTxMsg_Buffer;

// Encodes and enqueues various types of response and active data for CAN transmission.
void ResponseDataEncoder() {

	// Check if Heartbeat request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Heartbeat == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Heartbeat = 0;  // Clear the ask status flag

		// Encode and enqueue Passive Confirmation data
		Passive_Confirmation(&CanTxMsg_Buffer);
		enqueue_CanTxMsg(CanTxMsg_Buffer);
	}

	// Check if Confirmation request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Confirmation == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Confirmation = 0;  // Clear the ask status flag

		// Encode and enqueue Passive Confirmation data
		Passive_Confirmation(&CanTxMsg_Buffer);
		enqueue_CanTxMsg(CanTxMsg_Buffer);
	}

	// Check if Active Data 1 request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Active_data_1 == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Active_data_1 = 0;  // Clear the ask status flag

		// Encode and enqueue Active Error data with associated functionality
		if (get_device_cfg()->role_of_gsystem == REMOTE1 || get_device_cfg()->role_of_gsystem == DISPLAY) {
			Active_Error(&CanTxMsg_Buffer, Func_Response);
			enqueue_CanTxMsg(CanTxMsg_Buffer);

			if (get_device_cfg()->role_of_gsystem != DISPLAY) {
				// Encode and enqueue Active Remote Command Button Status data
				Active_RemoteCmdBtnStatus(&CanTxMsg_Buffer, Func_Response);
				enqueue_CanTxMsg(CanTxMsg_Buffer);
			}
		}
	}

	// Check if Active Data 2 request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Active_data_2 == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Active_data_2 = 0;  // Clear the ask status flag

		// Encode and enqueue Active Error data with associated functionality
		if (get_device_cfg()->role_of_gsystem == REMOTE2) {
			Active_Error(&CanTxMsg_Buffer, Func_Response);
			enqueue_CanTxMsg(CanTxMsg_Buffer);

			// Encode and enqueue Active Remote Command Button Status data
			Active_RemoteCmdBtnStatus(&CanTxMsg_Buffer, Func_Response);
			enqueue_CanTxMsg(CanTxMsg_Buffer);
		}
	}

	// Check if Passive Data 1 request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_1 == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_1 = 0;  // Clear the ask status flag

		// Encode and enqueue various Passive data including Firmware, Hardware, and Picture versions
		if (get_device_cfg()->role_of_gsystem == REMOTE1 || get_device_cfg()->role_of_gsystem == DISPLAY) {
			Passive_FirmwareVersion(&CanTxMsg_Buffer);
			enqueue_CanTxMsg(CanTxMsg_Buffer);

			Passive_HardwareVersion(&CanTxMsg_Buffer);
			enqueue_CanTxMsg(CanTxMsg_Buffer);

			Passive_PictureVersion(&CanTxMsg_Buffer);
			enqueue_CanTxMsg(CanTxMsg_Buffer);
		}
	}

	// Check if Passive Data 2 request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_2 == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_2 = 0;  // Clear the ask status flag
		// TBD: Encode and enqueue Passive Data 2
	}

	// Check if Passive Data 3 request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_3 == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_3 = 0;  // Clear the ask status flag

		// Encode and enqueue various Passive data including Firmware, Hardware, and Picture versions
		if (get_device_cfg()->role_of_gsystem == REMOTE2) {
			Passive_FirmwareVersion(&CanTxMsg_Buffer);
			enqueue_CanTxMsg(CanTxMsg_Buffer);

			Passive_HardwareVersion(&CanTxMsg_Buffer);
			enqueue_CanTxMsg(CanTxMsg_Buffer);

		}
	}

	// Check if Passive Data 4 request is pending
	if (get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_4 == 1) {
		get_eBikeDataCollection()->remoteAskStatus.Ask_Passive_data_4 = 0;  // Clear the ask status flag
		// TBD: Encode and enqueue Passive Data 4
	}
}

// Function to generate a CAN message containing firmware version information in response to a passive request
static void Passive_FirmwareVersion(CanMessage_t* canTxMsg){

    DataFrame_ID_t    dataFrame       = { 0 };  // Define a structure to hold CAN message header information
    FirmwareVersion_t firmwareVersion = { 0 };  // Define a structure to hold firmware version data
    uint8_t           length = 0;               // Initialize the length of data

    // Configure the data frame header
    dataFrame.std.fugp = Func_Response;    // Set the function group to response
    dataFrame.std.nogp = get_device_cfg()->node_of_role; // Set the node group based on configuration
    dataFrame.std.dtyp = Typ_Passive;      // Set the data type to passive

    // Determine the address based on the configuration role
    switch (get_device_cfg()->role_of_gsystem){
        case REMOTE1:
        case DISPLAY:
            dataFrame.std.addr = 0x0;       // Set the address for certain configuration roles
            break;
        case REMOTE2:
            dataFrame.std.addr = 0x8;       // Set the address for a different configuration role
            break;
    }

    // Populate firmware version data
    length = sizeof(firmwareVersion.Bytes);               // Set the length to the size of firmwareVersion.Bytes
    firmwareVersion.Msg.year  = get_device_cfg()->firmware_year;        // Set the firmware year based on configuration
    firmwareVersion.Msg.month = get_device_cfg()->firmware_month;       // Set the firmware month based on configuration
    firmwareVersion.Msg.day   = get_device_cfg()->firmware_day;         // Set the firmware day based on configuration
    firmwareVersion.Msg.sn	  = get_device_cfg()->firmware_sn;          // Set the firmware serial number based on configuration
    firmwareVersion.Msg.type  = get_device_cfg()->firmware_type;        // Set the firmware type based on configuration
    memcpy(canTxMsg->Data, firmwareVersion.Bytes, length); // Copy firmware version data to CAN message data

    // Configure the CanMessage_t structure
    canTxMsg->ID = dataFrame.Id;          // Set the CAN message ID based on the data frame
    canTxMsg->DLC = length;               // Set the data length code
    canTxMsg->IDE = Standard;             // Set the identifier type to standard
    canTxMsg->RTR = DataFrame;
}

// Function to generate a CAN message containing hardware version information in response to a passive request
static void Passive_HardwareVersion(CanMessage_t* canTxMsg){

    DataFrame_ID_t    dataFrame       = { 0 }; // Define a structure to hold CAN message header information
    HardwareVersion_t hardwareVersion = { 0 }; // Define a structure to hold hardware version data
    uint8_t           length = 0;              // Initialize the length of data

    // Configure the data frame header
    dataFrame.std.fugp = Func_Response;    // Set the function group to response
    dataFrame.std.nogp = get_device_cfg()->node_of_role; // Set the node group based on configuration
    dataFrame.std.dtyp = Typ_Passive;      // Set the data type to passive

    // Determine the address based on the configuration role
    switch (get_device_cfg()->role_of_gsystem){
        case REMOTE1:
        case DISPLAY:
            dataFrame.std.addr = 0x1;       // Set the address for certain configuration roles
            break;
        case REMOTE2:
            dataFrame.std.addr = 0x9;       // Set the address for a different configuration role
            break;
    }

    // Populate hardware version data
    length = sizeof(hardwareVersion.Bytes);               // Set the length to the size of hardwareVersion.Bytes
    hardwareVersion.Msg.year  = get_device_cfg()->hardware_year;        // Set the hardware year based on configuration
    hardwareVersion.Msg.month = get_device_cfg()->hardware_month;       // Set the hardware month based on configuration
    hardwareVersion.Msg.sn    = get_device_cfg()->hardware_sn;          // Set the hardware serial number based on configuration
    memcpy(canTxMsg->Data, hardwareVersion.Bytes, length); // Copy hardware version data to CAN message data

    // Configure the CanMessage_t structure
    canTxMsg->ID = dataFrame.Id;          // Set the CAN message ID based on the data frame
    canTxMsg->DLC = length;               // Set the data length code
    canTxMsg->IDE = Standard;             // Set the identifier type to standard
    canTxMsg->RTR = DataFrame;
}

// Function to generate a CAN message containing picture version information in response to a passive request
static void Passive_PictureVersion(CanMessage_t* canTxMsg){

    DataFrame_ID_t    dataFrame      = { 0 };  // Define a structure to hold CAN message header information
    PictureVersion_t  pictureVersion = { 0 };  // Define a structure to hold picture version data
    uint8_t           length = 0;              // Initialize the length of data

    // Configure the data frame header
    dataFrame.std.fugp = Func_Response;     // Set the function group to response
    dataFrame.std.nogp = get_device_cfg()->node_of_role;  // Set the node group based on configuration
    dataFrame.std.dtyp = Typ_Passive;       // Set the data type to passive

    // Determine the address based on the configuration role
    switch (get_device_cfg()->role_of_gsystem){
        case REMOTE1:
        case DISPLAY:
            dataFrame.std.addr = 0x2;       // Set the address for certain configuration roles
            break;
    }

    // Populate picture version data
    length = sizeof(pictureVersion.Bytes);  // Set the length to the size of pictureVersion.Bytes
    pictureVersion.Msg.icon   = 0;          // Set picture icon information
    pictureVersion.Msg.navi   = 0;          // Set picture navigation information
    pictureVersion.Msg.number = 0;          // Set picture number information
    pictureVersion.Msg.Europe = 0;          // Set picture Europe information
    pictureVersion.Msg.t_ch   = 0;          // Set picture t_ch information
    pictureVersion.Msg.s_ch   = 0;          // Set picture s_ch information
    pictureVersion.Msg.Japan  = 0;          // Set picture Japan information
    pictureVersion.Msg.Korea  = 0;          // Set picture Korea information

    memcpy(canTxMsg->Data, pictureVersion.Bytes, length); // Copy picture version data to CAN message data

    // Configure the CanMessage_t structure
    canTxMsg->ID = dataFrame.Id;          // Set the CAN message ID based on the data frame
    canTxMsg->DLC = length;               // Set the data length code
    canTxMsg->IDE = Standard;             // Set the identifier type to standard
    canTxMsg->RTR = DataFrame;
}

// Function to generate a CAN message containing confirmation information in response to a passive request
static void Passive_Confirmation(CanMessage_t* canTxMsg){

    DataFrame_ID_t    dataFrame    = { 0 };  // Define a structure to hold CAN message header information
    Confirmation_t    confirmation = { 0 };  // Define a structure to hold confirmation data
    uint8_t           length = 0;            // Initialize the length of data

    // Configure the data frame header
    dataFrame.std.fugp = Func_Response;    // Set the function group to response
    dataFrame.std.nogp = get_device_cfg()->node_of_role; // Set the node group based on configuration
    dataFrame.std.dtyp = Typ_Passive;      // Set the data type to passive

    // Determine the address based on the configuration role
    switch (get_device_cfg()->role_of_gsystem){
        case REMOTE1:
            dataFrame.std.addr = 0x7;       // Set the address for a certain configuration role
            break;
        case REMOTE2:
        case DISPLAY:
            dataFrame.std.addr = 0xF;       // Set the address for other configuration roles
            break;
    }

    // Populate confirmation data
    length = sizeof(confirmation.Bytes);   // Set the length to the size of confirmation.Bytes
    confirmation.Msg.cfm = 1;              // Set the confirmation value

    memcpy(canTxMsg->Data, confirmation.Bytes, length); // Copy confirmation data to CAN message data

    // Configure the CanMessage_t structure
    canTxMsg->ID  = dataFrame.Id;          // Set the CAN message ID based on the data frame
    canTxMsg->DLC = length;               // Set the data length code
    canTxMsg->IDE = Standard;             // Set the identifier type to standard
    canTxMsg->RTR = DataFrame;
}
