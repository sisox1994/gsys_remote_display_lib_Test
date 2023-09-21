#ifndef GSYS_DEVICE_CONFIGURATOR_H
#define GSYS_DEVICE_CONFIGURATOR_H

#include "gsys_canbus_msg.h"
#include "gsys_data_active.h"
#include "gsys_data_event.h"

// Definition of the Device Configuration structure
typedef struct {
    Node_Group_t      node_of_role;       // Node configuration for the role
    RoleDefinition_t  role_of_gsystem;    // Role configuration for the G-system

    uint8_t           firmware_year;      // Year of the firmware publication
    uint8_t           firmware_month;     // Month of the firmware publication
    uint8_t           firmware_day;       // Day of the firmware publication
    uint8_t           firmware_sn;        // Firmware version serial number
    uint8_t           firmware_type;      // Firmware type identifier

    uint8_t           hardware_year;      // Year of the hardware publication
    uint8_t           hardware_month;     // Month of the hardware publication
    uint8_t           hardware_sn;        // Hardware version serial number
} DeviceConfig_t;


// Function to configure the device using a DeviceConfig_t input
void DeviceConfigurator(DeviceConfig_t input);

// Function to retrieve a pointer to the device_cfg configuration
DeviceConfig_t *get_device_cfg(void);


Remote1CmdButtonStatus_t *get_remote1CmdBtnStatus(void);
Remote2CmdButtonStatus_t *get_remote2CmdBtnStatus(void);

// [REMOTE1] Update the local_remote1CmdBtnStatus with the button states from the provided status parameter.
void SetRemote1ButtonStatus(Remote1CmdButtonStatus_t status);

// [REMOTE2] Update the local_remote2CmdBtnStatus with the button states from the provided status parameter.
void SetRemote2ButtonStatus(Remote2CmdButtonStatus_t status);

// Set the remote command for the appropriate remote system based on the configuration role.
void SetRemoteButtonCommand(RemoteCommandEnum rm_cmd);





// Configure the device error status.
void DeviceErrorStatusConfiguration(uint8_t error);

// Check for the presence of a device error. (0: No error, 1: Error present)
uint8_t IsDeviceErrorPresent(void);

#endif // GSYS_DEVICE_CONFIGURATOR_H
