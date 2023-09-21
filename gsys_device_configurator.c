#include "gsys_device_configurator.h"
#include "gsys_ebike_data_collection.h"


// Define a static DeviceConfig_t variable as global configuration
// static DeviceConfig_t device_cfg;

// Initialize a static variable named local_remote1CmdBtnStatus of type Remote1CmdButtonStatus_t and set its initial value to { 0 }
static Remote1CmdButtonStatus_t remote1CmdBtnStatus_cfg = { 0 };

// Initialize another static variable named local_remote2CmdBtnStatus of type Remote2CmdButtonStatus_t and set its initial value to { 0 }
static Remote2CmdButtonStatus_t remote2CmdBtnStatus_cfg = { 0 };


// Initialize the device_cfg variable
static DeviceConfig_t device_cfg = {
    .node_of_role     = Node_Remote, // Configure the device node of the G-system.
    .role_of_gsystem  = REMOTE1,     // Configure the role of the G-system.

    // Configure the Firmware Version of this Component.
    .firmware_year    = 23,          // Year of publication.
    .firmware_month   = 8,           // Month of publication.
    .firmware_day     = 17,          // Day of publication.
    .firmware_sn      = 1,           // Firmware version serial number.
    .firmware_type    = 0x6,         // [RC Type] 0x00 RideControl, 0x01 BBSS, 0x02 Controller, 0x03 Remote CT, 0x04 Display EVO, 0x05 Remote Sport, 0x06 Remote 2in1, 0x07 Remote ON/OFF, 0x08 E-Shifting MCU1, 0x09 E-Shifting MCU2, 0x0A Display EVO 2 (GD)

    // Configure the Hardware Version of this Component.
    .hardware_year    = 23,          // Year of publication.
    .hardware_month   = 8,           // Month of publication.
    .hardware_sn      = 0,           // Hardware version serial number.
};


// Configure device settings based on the input configuration.
void DeviceConfigurator(DeviceConfig_t input){

	// Set node and system role
	get_device_cfg()->node_of_role    = input.node_of_role;
	get_device_cfg()->role_of_gsystem = input.role_of_gsystem;

	// Set firmware information
	get_device_cfg()->firmware_year   = input.firmware_year;
	get_device_cfg()->firmware_month  = input.firmware_month;
	get_device_cfg()->firmware_day    = input.firmware_day;
	get_device_cfg()->firmware_sn     = input.firmware_sn;
	get_device_cfg()->firmware_type   = input.firmware_type;

	// Set hardware information
	get_device_cfg()->hardware_year   = input.hardware_year;
	get_device_cfg()->hardware_month  = input.hardware_month;
	get_device_cfg()->hardware_sn     = input.hardware_sn;

}


// Function to retrieve a pointer to the device_cfg configuration
DeviceConfig_t *get_device_cfg() {
    return &device_cfg;
}






Remote1CmdButtonStatus_t *get_remote1CmdBtnStatus() {
	return &remote1CmdBtnStatus_cfg;
}

Remote2CmdButtonStatus_t *get_remote2CmdBtnStatus() {
	return &remote2CmdBtnStatus_cfg;
}

// [REMOTE1] Update the local_remote1CmdBtnStatus with the button states from the provided status parameter.
void SetRemote1ButtonStatus(Remote1CmdButtonStatus_t status){

	remote1CmdBtnStatus_cfg.Msg.btn_s1 = status.Msg.btn_s1;
	remote1CmdBtnStatus_cfg.Msg.btn_s2 = status.Msg.btn_s2;
	remote1CmdBtnStatus_cfg.Msg.btn_s3 = status.Msg.btn_s3;
	remote1CmdBtnStatus_cfg.Msg.btn_s4 = status.Msg.btn_s4;
	remote1CmdBtnStatus_cfg.Msg.btn_s5 = status.Msg.btn_s5;
	remote1CmdBtnStatus_cfg.Msg.btn_s6 = status.Msg.btn_s6;
	remote1CmdBtnStatus_cfg.Msg.btn_s7 = status.Msg.btn_s7;
	remote1CmdBtnStatus_cfg.Msg.btn_s8 = status.Msg.btn_s8;
}

// [REMOTE2] Update the local_remote2CmdBtnStatus with the button states from the provided status parameter.
void SetRemote2ButtonStatus(Remote2CmdButtonStatus_t status){

	remote2CmdBtnStatus_cfg.Msg.btn_s1 = status.Msg.btn_s1;
	remote2CmdBtnStatus_cfg.Msg.btn_s2 = status.Msg.btn_s2;
	remote2CmdBtnStatus_cfg.Msg.btn_s3 = status.Msg.btn_s3;
	remote2CmdBtnStatus_cfg.Msg.btn_s4 = status.Msg.btn_s4;
	remote2CmdBtnStatus_cfg.Msg.btn_s5 = status.Msg.btn_s5;
	remote2CmdBtnStatus_cfg.Msg.btn_s6 = status.Msg.btn_s6;
	remote2CmdBtnStatus_cfg.Msg.btn_s7 = status.Msg.btn_s7;
	remote2CmdBtnStatus_cfg.Msg.btn_s8 = status.Msg.btn_s8;
}

// Set the remote command for the appropriate remote system based on the configuration role.
void SetRemoteButtonCommand(RemoteCommandEnum rm_cmd){

	if (get_device_cfg()->role_of_gsystem == REMOTE1){
		remote1CmdBtnStatus_cfg.Msg.rm_cmd = rm_cmd; // Set remote command for Remote 1
	}
	else if (get_device_cfg()->role_of_gsystem == REMOTE2){
		remote2CmdBtnStatus_cfg.Msg.rm_cmd = rm_cmd; // Set remote command for Remote 2
	}

}





// Configure the device error status.
void DeviceErrorStatusConfiguration(uint8_t error){

	get_eBikeDataCollection()->errorStatus.DeviceErrorStatus = error;
}

// Check for the presence of a device error. (0: No error, 1: Error present)
uint8_t IsDeviceErrorPresent(){

	uint8_t ret = 0;

	if (get_device_cfg()->node_of_role == Node_Remote){

		if (get_eBikeDataCollection()->errorStatus.DeviceErrorStatus == ERR_Remote_NoError){
			ret = 0; // No device error is present.
		}
		else{
			ret = 1; // A device error is present.
		}
	}
	else if (get_device_cfg()->node_of_role == Node_Display){

		if (get_eBikeDataCollection()->errorStatus.DeviceErrorStatus == ERR_Display_NoError){
			ret = 0; // No device error is present.
		}
		else{
			ret = 1; // A device error is present.
		}
	}

	return ret;
}
