#ifndef GSYS_EBIKE_DATA_COLLECTION_H
#define GSYS_EBIKE_DATA_COLLECTION_H

#include <stdint.h>

#pragma pack(push)   // preserves the current alignment setting.
#pragma pack(1)      // directive aligns structure members tightly in sequential order without padding, conserving memory by avoiding unnecessary gaps.


// E-Bike Data Collection structure definition.

// [System status] =============================================================

// RidingModeEnum defines different Riding modes.
typedef enum {
	RIDING_MODE_INACTIVE = 0x0,   
	RIDING_MODE_ACTIVE   = 0x1  
} RidingModeEnum;

// AdjustingModeEnum defines different Adjusting modes.
typedef enum {
    ADJUST_MODE_RESERVED                     = 0x00,
    ADJUST_MODE_SELF_DETECTION               = 0x01,
    ADJUST_MODE_ASSISTANCE                   = 0x02,
    ADJUST_MODE_UNIT_EVENT                   = 0x03,
    ADJUST_MODE_LANGUAGE_EVENT               = 0x04,
    ADJUST_MODE_CALIBRATION_EVENT            = 0x05,
    ADJUST_MODE_DATA_COLLECTION              = 0x06,
    ADJUST_MODE_DIAGNOSTIC                   = 0x07,
    ADJUST_MODE_UPDATE                       = 0x08,
    ADJUST_MODE_SPEEDY_CHECK                 = 0x09,
    ADJUST_MODE_SERVICE                      = 0x0A,
    ADJUST_MODE_CHECK                        = 0x0B,
    ADJUST_MODE_OFF                          = 0x0C,
    ADJUST_MODE_ERROR                        = 0x0D,
    ADJUST_MODE_SPEED_LIMITATION             = 0x0E,
    ADJUST_MODE_SETTING_FRAME_NUMBER         = 0x0F,
    ADJUST_MODE_SETTING_WHEEL_CIRCUMFERENCE  = 0x10,
    ADJUST_MODE_SETTING_DERAILLEUR_SYSTEM    = 0x11,
    ADJUST_MODE_RESERVED_START               = 0x12,
    ADJUST_MODE_RESERVED_END                 = 0x1F
} AdjustingModeEnum;


static const char *AdjustingModeStrings[] = {
	"RESERVED",
	"SELF_DETECTION",              // 0x00
	"ASSISTANCE",                  // 0x01
	"UNIT_EVENT",                  // 0x02
	"LANGUAGE_EVENT",              // 0x03
	"CALIBRATION_EVENT",           // 0x04
	"DATA_COLLECTION",             // 0x05
	"DIAGNOSTIC",                  // 0x06
	"UPDATE",                      // 0x07
	"SPEEDY_CHECK",                // 0x08
	"SERVICE",                     // 0x09
	"CHECK",                       // 0x0A
	"OFF",                         // 0x0B
	"ERROR",                       // 0x0C
	"SPEED_LIMITATION",            // 0x0D
	"SETTING_FRAME_NUMBER",        // 0x0E
	"SETTING_WHEEL_CIRCUMFERENCE", // 0x0F
	"SETTING_DERAILLEUR_SYSTEM",   // 0x10
	"RESERVED_START",              // 0x11
	"RESERVED_01",                 // 0x12
	"RESERVED_02",                 // 0x13
	"RESERVED_03",                 // 0x14
	"RESERVED_04",                 // 0x15
	"RESERVED_05",                 // 0x16
	"RESERVED_06",                 // 0x17
	"RESERVED_07",                 // 0x18
	"RESERVED_08",                 // 0x19
	"RESERVED_09",                 // 0x1A
	"RESERVED_10",                 // 0x1B
	"RESERVED_11",                 // 0x1C
	"RESERVED_12",                 // 0x1D
	"RESERVED_13",                 // 0x1E
	"RESERVED_END"                 // 0x1F
};

// DisplayModeEnum defines different display modes.
typedef enum {
    DISPLAY_MODE_NULL                        = 0x00, // Display according to 'amod'.
    DISPLAY_MODE_WALK_ASSISTANCE             = 0x01, // Show the string 'Walk assist' or scroll the LED.
    DISPLAY_MODE_SHUTTING_DOWN               = 0x02, // Show the string 'See You' or blink the LED.
    DISPLAY_MODE_SHUTDOWN                    = 0x03, // Turn off all LED and LCD.
    DISPLAY_MODE_RESERVED_1                  = 0x04, // Reserved.
    DISPLAY_MODE_RESERVED_2                  = 0x05, // Reserved.
    DISPLAY_MODE_MANUAL_AUTO_SWITCHING       = 0x06, // Manual/Automatic Switching Mode.
    DISPLAY_MODE_SETTING_AUTO_SHIFT_CADENCE  = 0x07, // Setting auto-shift cadence.
    DISPLAY_MODE_MANUAL_SHIFT                = 0x08, // Manual shift mode.
    DISPLAY_MODE_SHIFTING_CALIBRATION        = 0x09, // Shifting calibration mode.
    DISPLAY_MODE_CHARGE                      = 0x0A  // Charge mode.
} DisplayModeEnum;

// DisplayLanguageEnum defines different display languages.
typedef enum {
    DISPLAY_LANGUAGE_ENGLISH              = 0x00, // English
    DISPLAY_LANGUAGE_FRENCH               = 0x01, // French
    DISPLAY_LANGUAGE_GERMAN               = 0x02, // German
    DISPLAY_LANGUAGE_DUTCH                = 0x03, // Dutch
    DISPLAY_LANGUAGE_SPANISH              = 0x04, // Spanish
    DISPLAY_LANGUAGE_ITALIAN              = 0x05, // Italian
    DISPLAY_LANGUAGE_TRADITIONAL_CHINESE  = 0x06, // Traditional Chinese
    DISPLAY_LANGUAGE_SIMPLIFIED_CHINESE   = 0x07, // Simplified Chinese
    DISPLAY_LANGUAGE_JAPANESE             = 0x08, // Japanese
    DISPLAY_LANGUAGE_KOREAN               = 0x09, // Korean
    DISPLAY_LANGUAGE_POLISH               = 0x0A  // Polish
} DisplayLanguageEnum;

// BrandCategoryEnum defines different brand categories.
typedef enum {
    BRAND_CATEGORY_GIANT      = 0x00, // Giant
    BRAND_CATEGORY_LIV        = 0x01, // Liv
    BRAND_CATEGORY_MOMENTUM   = 0x02  // Momentum
} BrandCategoryEnum;

// UnitSystemEnum defines different unit systems.
typedef enum {
    UNIT_SYSTEM_METRIC   = 0x00, // Metric
    UNIT_SYSTEM_IMPERIAL = 0x01  // Imperial
} UnitSystemEnum;

#ifndef __RemoteCommandEnum__
#define __RemoteCommandEnum__

// RemoteCommandEnum defines different remote commands.
typedef enum {
    REMOTE_CMD_NO_COMMAND                         = 0x00, // No command
    REMOTE_CMD_SWITCH_BATTERY_RESERVED            = 0x01, // Switch Battery (reserved)
    REMOTE_CMD_TOGGLE_LIGHT_STATE                 = 0x02, // Toggle Light State
    REMOTE_CMD_TOGGLE_DISPLAY_DATA                = 0x03, // Toggle Display Data
    REMOTE_CMD_POWER_ASSIST_MODE_INCREASE         = 0x04, // Power Assist Mode [Increase]
    REMOTE_CMD_SWITCH_PREVIOUS_PAGE_DISPLAY       = 0x05, // Switch back to the previous page's display data
    REMOTE_CMD_RESET_SHOW                         = 0x06, // Reset (Show what to reset)
    REMOTE_CMD_NO_COMMAND_2                       = 0x07, // No command
    REMOTE_CMD_BRAKE_RESERVED                     = 0x08, // Brake (reserved)
    REMOTE_CMD_ENTER_WALK_ASSIST_MODE             = 0x09, // Enter Walk Assist Mode
    REMOTE_CMD_MANUAL_CRANK_ANGLE_CALIB_RESERVED  = 0x0A, // Manual Crank Angle Calibration (reserved)
    REMOTE_CMD_MEME_SLOPE_CALIB_RESERVED          = 0x0B, // MEME/Slope Calibration (reserved)
    REMOTE_CMD_SMART_ASSIST                       = 0x0C, // Smart Assist
    REMOTE_CMD_POWER_OFF                          = 0x0D, // Power Off
    REMOTE_CMD_ON_OFF_SPEED_LIMIT                 = 0x0E, // On/Off Speed Limit
    REMOTE_CMD_EXECUTE_WALK_ASSIST                = 0x0F, // Execute Walk Assist
    REMOTE_CMD_TOGGLE_DISPLAY_UNITS               = 0x10, // Toggle Display Units
    REMOTE_CMD_SWITCH_BACKLIGHT_BRIGHTNESS        = 0x11, // Switch Backlight Brightness
    REMOTE_CMD_POWER_ASSIST_MODE_DECREASE         = 0x12, // Power Assist Mode [Decrease]
    REMOTE_CMD_POWER_ASSIST_MODE_CYCLE_UP         = 0x13, // Power Assist Mode [Cycle Up]
    REMOTE_CMD_SHIFTING_GEARS_INCREASE            = 0x14, // Shifting gears [Increase]
    REMOTE_CMD_SHIFTING_GEARS_DECREASE            = 0x15, // Shifting gears [Decrease]
    REMOTE_CMD_CALIBRATING_GEARS_RESERVED         = 0x16, // Calibrating the gears (reserved)
    REMOTE_CMD_MANUAL_AUTO_SWITCHING_CYCLE_UP     = 0x17, // Manual/Automatic Switching [Cycle Up]
    REMOTE_CMD_MANUAL_AUTO_SWITCHING_CYCLE_DOWN   = 0x18, // Manual/Automatic Switching [Cycle Down]
    REMOTE_CMD_AUTO_SHIFTING_TARGET_CADENCE_INC   = 0x19, // Auto-shifting target cadence [Increase]
    REMOTE_CMD_AUTO_SHIFTING_TARGET_CADENCE_DEC   = 0x1A, // Auto-shifting target cadence [Decrease]
    REMOTE_CMD_GEAR_CALIBRATION_INCREASE          = 0x1B, // Gear Calibration [Increase]
    REMOTE_CMD_GEAR_CALIBRATION_DECREASE          = 0x1C  // Gear Calibration [Decrease]
} RemoteCommandEnum;

#endif // __RemoteCommandEnum__


/**
* SystemStatus_t is a structure that represents the system status with various parameters.
* It encapsulates information about riding mode, adjusting mode, display mode, display language,
* brand category, unit system, remote command acknowledgment, backlight brightness, system state of charge,
* and odometer reading.
*/
typedef struct {
	RidingModeEnum       ridingMode;
	AdjustingModeEnum    adjustingMode;
	DisplayModeEnum      displayMode;
	DisplayLanguageEnum  displayLanguage;
	BrandCategoryEnum    brandCategory;
	UnitSystemEnum       unitSystem;
	RemoteCommandEnum    remoteCmdAck;
	uint8_t              backlightBrightness;     // Lv1~Lv10
	uint8_t              systemStateOfCharge;     // System state of charge.  0~100 (%)
	uint16_t             odometer;                // Odometer 0~65535 (km)
	uint16_t             remainingCapacity;       // 0~65535  TBD
	uint16_t             serviceIntervalMileage;  // 0~65535  TBD
} SystemStatus_t;





// [Assistance Status] =============================================================

// AssistanceLevelEnum defines different assistance levels for LED display.
typedef enum {
    ASSIST_LEVEL_OFF           = 0x00, // Turn off all assist LEDs.
    ASSIST_LEVEL_LED1          = 0x01, // Turn on assist LED1.
    ASSIST_LEVEL_LED1_TO_LED2  = 0x02, // Turn on assist LED1 to LED2.
    ASSIST_LEVEL_LED1_TO_LED3  = 0x03, // Turn on assist LED1 to LED3.
    ASSIST_LEVEL_LED1_TO_LED4  = 0x04, // Turn on assist LED1 to LED4.
    ASSIST_LEVEL_LED1_TO_LED5  = 0x05, // Turn on assist LED1 to LED5.
    ASSIST_LEVEL_LED3          = 0x06  // Turn on assist LED3.
} AssistanceLevelLEDEnum;

// AssistanceLevelLCDEnum defines different assistance levels for LCD display.
typedef enum {
    ASSIST_LEVEL_LCD_OFF     = 0x00, // Off
    ASSIST_LEVEL_LCD_ECO     = 0x01, // Eco
    ASSIST_LEVEL_LCD_TOUR    = 0x02, // Tour
    ASSIST_LEVEL_LCD_ACTIVE  = 0x03, // Active
    ASSIST_LEVEL_LCD_SPORT   = 0x04, // Sport
    ASSIST_LEVEL_LCD_POWER   = 0x05, // Power
    ASSIST_LEVEL_LCD_AUTO    = 0x06  // Auto
} AssistanceLevelLCDEnum;

/**
* AssistanceStatus_t is a structure that represents the assistance status of an E-Bike.
* It encapsulates information about the assistance levels for LED and LCD displays,
* as well as the remaining range that the E-Bike can travel based on its current battery status,
* Remaining Range 0~65535 (km) , value set to 0xFFFF when Assistance turn OFF.
*/
typedef struct {
	AssistanceLevelLEDEnum   assistLevelLED;     // Assistance level for LED display.
	AssistanceLevelLCDEnum   assistLevelLCD;     // Assistance level for LCD display.
	uint16_t                 remainingRange;     // Estimated remaining range in kilometers that the E-Bike can travel based on its current battery status.
} AssistanceStatus_t;





// [Riding Data] =============================================================

/**
* RidingData_t is a structure that represents various types of riding data for an E-Bike.
* It encapsulates real-time, accumulated, and non-real-time data related to the bike's performance and rider metrics.
*/
typedef struct {
	struct {
		uint16_t bikeSpeed;            // Bike speed in 0.1 kilometers per hour (kph)
		uint16_t cadence;              // Cadence in 0.1 revolutions per minute (rpm)
	} instantaneous;

	struct {
		uint16_t tripDistance;        // Trip distance in 0.1 kilometers (km).
		uint16_t tripTime;            // Trip time in minutes.
	} accumulated;

	struct {
		uint16_t averageSpeed;         // Average speed in 0.1 kph.
		uint16_t maximumSpeed;         // Maximum speed in 0.1 kph. 
		uint16_t cyclingPower;         // Cycling power in 0.1 watts.
		uint16_t maximumPower;         // Maximum power in 0.1 watts.
		uint16_t averagePower;         // Average power in 0.1 watts.
		uint16_t maximumCadence;       // Maximum cadence in 0.1 rpm.
		uint16_t averageCadence;       // Average cadence in 0.1 rpm.
		uint8_t  heartRateValue;       // Heart rate value in beats per minute. (bpm)
		uint16_t altitude;             // Altitude in meters.
	} nonInstantaneous;

} RidingData_t;






// [Status Notification] =============================================================

// LightStatusEnum defines different light status modes for an E-Bike's lighting system.
typedef enum {
    LIGHT_OFF              = 0x0, // Light off.
    LIGHT_NORMAL_ON        = 0x1, // Normal light on.
    LIGHT_LOW_BEAM         = 0x2, // Speed pedelec light low beam (近光燈).
    LIGHT_HIGH_BEAM        = 0x3  // Speed pedelec light high beam (遠光燈).
} LightStatusEnum;

#ifndef __StateStatusEnum__
#define __StateStatusEnum__

// StateStatusEnum defines different state status modes (Active/Inactive).
typedef enum {
    STATE_INACTIVE = 0x0,  // Inactive state.
    STATE_ACTIVE   = 0x1,  // Active state.
} StateStatusEnum;

#endif // __StateStatusEnum__

// ConnectionStatusEnum defines different connection status modes (Disconnected/Connected).
typedef enum {    
    CONNECTION_DISCONNECTED = 0x0,  // Disconnected state.
    CONNECTION_CONNECTED    = 0x1   // Connected state.
} ConnectionStatusEnum;

/**
* StatusNotification_t is a structure that represents various status notifications for an E-Bike's system.
* It encapsulates information about different system status indications and notifications.
*/
typedef struct {
	LightStatusEnum         lightStatus;          // Light status.
	StateStatusEnum         motorOverheating;     // Motor overheating status indicated by LED blink (Active :LED5 blinking in orange color).
	StateStatusEnum         incomingCall;         // Incoming call notification status (Inactive/Active).
	StateStatusEnum         smsNotification;      // SMS notification status (Inactive/Active).
	StateStatusEnum         mailNotification;     // Mail notification status (Inactive/Active).
	StateStatusEnum         gpsActivity;          // GPS activity status (Inactive/Active).
	ConnectionStatusEnum    bluetoothConnected;   // Bluetooth connectivity status (Disconnected/Connected).
	uint8_t                 phoneBattery;         // Mobile phone battery percentage (0~100%).
} StatusNotification_t;





// [Screen Layout] =============================================================

// DataFieldEnum defines different data fields for an E-Bike's display.
typedef enum {
    DATA_FIELD_CLOCK                       = 0x01, // Clock.
    DATA_FIELD_CALORIES                    = 0x02, // Calories.
    DATA_FIELD_ELEVATION                   = 0x03, // Elevation.
    DATA_FIELD_PHONE_BATTERY               = 0x04, // Phone Battery.
    DATA_FIELD_ESTIMATED_ARRIVAL_TIME      = 0x05, // Estimated time of arrival.
    DATA_FIELD_ESTIMATED_ARRIVAL_DISTANCE  = 0x06, // Estimated distance of arrival.
    DATA_FIELD_TURN                        = 0x07, // Turn.
    DATA_FIELD_TRIP_TIME                   = 0x10, // Trip time.
    DATA_FIELD_TRIP_DISTANCE               = 0x11, // Trip distance.
    DATA_FIELD_SPEED                       = 0x12, // Speed.
    DATA_FIELD_AVG_SPEED                   = 0x13, // AVG Speed.
    DATA_FIELD_CADENCE                     = 0x14, // Cadence.
    DATA_FIELD_AVG_CADENCE                 = 0x15, // AVG Cadence.
    DATA_FIELD_POWER                       = 0x16, // Power.
    DATA_FIELD_AVG_POWER                   = 0x17, // AVG Power.
    DATA_FIELD_BATTERY_LEVEL               = 0x18, // Battery Level.
    DATA_FIELD_BATTERY_MAIN                = 0x19, // Battery main.
    DATA_FIELD_BATTERY_SUB                 = 0x1A, // Battery sub.
    DATA_FIELD_REMAIN_RANGE                = 0x1B, // Remain Range.
    DATA_FIELD_ODO                         = 0x1C, // ODO.
    DATA_FIELD_SERVICE_INTERVAL            = 0x1D, // Service interval.
    DATA_FIELD_ASSIST_MODE                 = 0x1E, // Assist mode.
    DATA_FIELD_HEART_RATE                  = 0x1F, // Heart rate.
    DATA_FIELD_MAX_SPEED                   = 0x20, // Max Speed.
    DATA_FIELD_MAX_POWER                   = 0x21, // Max power.
    DATA_FIELD_MAX_CADENCE                 = 0x22, // Max Cadence.
    DATA_FIELD_SHIFT_SWITCH                = 0x23, // Shift switch.
    DATA_FIELD_SHIFT_AUTO_MODE_CADENCE     = 0x24, // Shift auto mode cadence.
    DATA_FIELD_SHIFT_CAL_MODE              = 0x25  // Shift cal mode.
} DataFieldEnum;

// RideDashFieldEnum defines different data fields for RideDash (Remote 2 in 1) on an E-Bike's display.
typedef enum {
    RIDE_DASH_FIELD_SPEED        = 0x00, // Speed.
    RIDE_DASH_FIELD_REMAIN_RANGE = 0x01, // Remain Range.
    RIDE_DASH_FIELD_DISTANCE     = 0x02, // Distance.
    RIDE_DASH_FIELD_TRIP_TIME    = 0x03, // Trip Time.
    RIDE_DASH_FIELD_AVG_SPEED    = 0x04, // Avg Speed.
    RIDE_DASH_FIELD_MAX_SPEED    = 0x05, // Max Speed.
    RIDE_DASH_FIELD_HEART_RATE   = 0x06, // Heart Rate.
    RIDE_DASH_FIELD_CADENCE      = 0x07, // Cadence.
    RIDE_DASH_FIELD_ODO          = 0x08, // ODO.
    RIDE_DASH_FIELD_E_SHIFTING   = 0x09  // E-Shifting.
} RideDashFieldEnum;

/**
* ScreenLayout_t is a structure that represents the screen layout configuration for an E-Bike's display.
* It encapsulates information about different data fields and their arrangement on the screen.
*/
typedef struct {
	DataFieldEnum       mainDataField;          // Main Data Field.
	DataFieldEnum       leftDataField;          // Left Data Field.
	DataFieldEnum       rightDataField;         // Right Data Field.	
	RideDashFieldEnum   rideControlDashField;   // RideControl Dash data field.
	uint8_t             pageIndex;              // Page index.  0x00~0x03
} ScreenLayout_t;





// [E-Shifting System] =============================================================

#ifndef __StateStatusEnum__
#define __StateStatusEnum__

// StateStatusEnum defines different state status modes (Active/Inactive).
typedef enum {
    STATE_INACTIVE = 0x0,  // Inactive state.
    STATE_ACTIVE   = 0x1,  // Active state.
} StateStatusEnum;

#endif // __StateStatusEnum__

// EShiftingModeEnum defines different operation modes for the E-Shifting System on an E-Bike.
typedef enum {
    E_SHIFTING_MODE_INACTIVE        = 0x0, // Inactive mode (Low power consumption mode).
    E_SHIFTING_MODE_AUTO_SHIFTING   = 0x1, // Auto-shifting mode (Cadence control mode).
    E_SHIFTING_MODE_MANUAL_SHIFTING = 0x2 // Manual-shifting mode (Ratio control mode).
} EShiftingModeEnum;

// EShiftingSystem_t defines the attributes related to the E-Shifting System on an E-Bike.

typedef struct {
	StateStatusEnum     activity;           // E-Shifting System activity (Inactive/Active).
	EShiftingModeEnum   operationMode;      // E-Shifting Operation Mode (Inactive/Auto-shifting/Manual-shifting).
	uint8_t             internalGearRatio;  // Ratio of internal gear (0 ~ 25.4 ratio).  0x00 ~ 0xFE: 0 ~ 25.4 ratio.  0xFF: In ‘w_grix’ control mode or auto-shifting (Cadencecontrol mode).
	uint8_t             gearIndex;          // Gear index (1 ~ 9 for Enviolo, 1 ~ 10 for Tektro).
	uint8_t             desiredCadence;     // DU desired cadence (0 ~ 254 rpm).
	uint8_t             gearOffsetNumber;   // Gear offset number (1 ~ 21).
} EShiftingSystem_t;





// [Energy Pack Status] =============================================================

// BatteryStateEnum defines different states of a battery.
typedef enum {
	STATE_C = 0x00, // Battery state C (D-FET on and C-FET on)
	STATE_F = 0x01, // Battery state F (D-FET on and C-FET off)
	STATE_D = 0x02  // Battery state D (D-FET off and C-FET off)
} BatteryStateEnum;

// EnergypackStatus_t defines the status of an energy pack.
typedef struct {
	uint8_t           relativeStateOfCharge;   // Relative state of charge. Range: 0~100 (%)
	BatteryStateEnum  batteryState;            // Battery state as per BatteryStateEnum definitions.
} EnergypackStatus_t;





// [Navigation Info] =============================================================

#ifndef __StateStatusEnum__
#define __StateStatusEnum__

// StateStatusEnum defines different state status modes (Active/Inactive).
typedef enum {
    STATE_INACTIVE = 0x0,  // Inactive state.
    STATE_ACTIVE   = 0x1,  // Active state.
} StateStatusEnum;

#endif // __StateStatusEnum__

// NavigationInstructionEnum defines the various navigation instructions and their corresponding codes.
typedef enum {
    NAV_STRAIGHT                = 0x01, // Continue straight
    NAV_GO_STRAIGHT             = 0x02, // Go straight
    NAV_START_ROUTE             = 0x03, // Start route
    NAV_ROUTE_FINISHED          = 0x04, // Route finished
    NAV_MERGE                   = 0x05, // Merge onto another road
    NAV_FORK_LEFT               = 0x06, // Fork left
    NAV_RAMP_LEFT               = 0x07, // Take a ramp left
    NAV_SLIGHT_LEFT             = 0x08, // Take a slight left turn
    NAV_TURN_LEFT               = 0x09, // Turn left */
    NAV_SHARP_LEFT              = 0x0A, // Make a sharp left turn
    NAV_UTURN_LEFT              = 0x0B, // Make a U-turn to the left
    NAV_KEEP_LEFT               = 0x0C, // Keep left
    NAV_FORK_RIGHT              = 0x0D, // Fork right
    NAV_RAMP_RIGHT              = 0x0E, // Take a ramp right
    NAV_SLIGHT_RIGHT            = 0x0F, // Take a slight right turn
    NAV_UTURN_RIGHT             = 0x10, // Make a U-turn to the right
    NAV_SHARP_RIGHT             = 0x11, // Make a sharp right turn
    NAV_TURN_RIGHT              = 0x12, // Turn right
    NAV_KEEP_RIGHT              = 0x13, // Keep right
    NAV_FERRY                   = 0x14, // Take a ferry
    NAV_FERRY_TRAIN             = 0x15, // Take a ferry train
    NAV_ROUNDABOUT_LEFT         = 0x16, // Take the left exit of a roundabout
    NAV_ROUNDABOUT_RIGHT        = 0x17, // Take the right exit of a roundabout
    NAV_ROUNDABOUT_CCW_EXIT_1_1 = 0x18, // Take the first counter-clockwise exit of a roundabout (1 of 1)
    NAV_ROUNDABOUT_CCW_EXIT_1_2 = 0x19, // Take the first counter-clockwise exit of a roundabout (1 of 2)
    NAV_ROUNDABOUT_CCW_EXIT_1_3 = 0x1A, // Take the first counter-clockwise exit of a roundabout (1 of 3)
    NAV_ROUNDABOUT_CCW_EXIT_2_2 = 0x1B, // Take the second counter-clockwise exit of a roundabout (2 of 2)
    NAV_ROUNDABOUT_CCW_EXIT_2_3 = 0x1C, // Take the second counter-clockwise exit of a roundabout (2 of 3)
    NAV_ROUNDABOUT_CCW_EXIT_3_3 = 0x1D, // Take the third counter-clockwise exit of a roundabout (3 of 3)
    NAV_ROUNDABOUT_CW_EXIT_1_1  = 0x1E, // Take the first clockwise exit of a roundabout (1 of 1)
    NAV_ROUNDABOUT_CW_EXIT_1_2  = 0x1F, // Take the first clockwise exit of a roundabout (1 of 2)
    NAV_ROUNDABOUT_CW_EXIT_1_3  = 0x20, // Take the first clockwise exit of a roundabout (1 of 3)
    NAV_ROUNDABOUT_CW_EXIT_2_2  = 0x21, // Take the second clockwise exit of a roundabout (2 of 2)
    NAV_ROUNDABOUT_CW_EXIT_2_3  = 0x22, // Take the second clockwise exit of a roundabout (2 of 3)
    NAV_ROUNDABOUT_CW_EXIT_3_3  = 0x23, // Take the third clockwise exit of a roundabout (3 of 3)
    NAV_ROUNDABOUT_FALLBACK     = 0x24, // Roundabout fallback
    NAV_OUT_OF_ROUTE            = 0x25  // Out of route
} NavigationInstructionEnum;

// NavigationInfo_t defines the structure for holding navigation-related information.

typedef struct {
	StateStatusEnum            activity;                    // Navigation functionality (Inactive/Active).
	NavigationInstructionEnum  firstInstruction;            // First navigation instruction code
	NavigationInstructionEnum  nextInstruction;             // Next navigation instruction code
	uint16_t                   distanceToFirstAction;       // Distance to the first navigation action in meters (0~65535 m)
	uint16_t                   distanceToNextAction;        // Distance to the next navigation action in meters (0~65535 m)
	uint16_t                   estimatedDistanceToArrival;  // Estimated Distance to Arrival in 0.1 kilometers (0~65535 * 0.1 km)
	uint16_t                   estimatedTimeOfArrival;      // Estimated Time of Arrival in minutes (0~65535 minutes)
} NavigationInfo_t;





// [Time Info] =============================================================

// EnableDisableEnum defines different enable/disable modes.
typedef enum {
	ENUM_DISABLE = 0x0,  // Disable.
	ENUM_ENABLE  = 0x1,  // Enable.
} EnableDisableEnum;


// TimeFormatEnum defines different time display formats.
typedef enum {
	TIME_FORMAT_12_HOUR = 0x0,  // 12-hour time format.
	TIME_FORMAT_24_HOUR = 0x1,  // 24-hour time format.
} TimeFormatEnum;


// TimeInfo_t defines the structure for holding time-related information.
typedef struct {
	EnableDisableEnum  enable;              // Enable/Disable Time Functionality. 0x0 Disable, 0x1 Enable.
	TimeFormatEnum     displayTimeFormat;   // Display of time format. 0x0 12-hour, 0x1 24-hour.
	uint8_t            currentHour;         // The current hour of the time. Range: 0~23 (hour).
	uint8_t            currentMinute;       // The current minute of the time. Range: 0~59 (minute).
} TimeInfo_t;





// [Workout Goal] =============================================================

// WorkoutGoal_t defines the structure for holding workout goal-related information.
typedef struct {
	uint8_t        workoutMode;                  // Workout mode (TBD).
	uint32_t       distanceToTarget;             // Distance to the target. Range: 0~16777215 (TBD).
	uint32_t       remainingDistanceToTarget;    // Remaining distance to the target. Range: 0~16777215 (TBD).
	uint32_t       targetWorkoutTime;            // Target workout time. Range: 0~16777215 (TBD).
	uint32_t       remainingTimeToTarget;        // Remaining time to the target. Range: 0~16777215 (TBD).
	uint16_t       targetCalories;               // Target calories. Range: 0~65535 (TBD).
	uint16_t       remainingCaloriesToTarget;    // Remaining calories to the target. Range: 0~65535 (TBD).
	uint16_t       caloriesBurned;               // Calories already burned. Range: 0~65535 (TBD).
	uint8_t        maxHeartRateTarget;           // Maximum heart rate target. Range: 0~255 (TBD).
	uint8_t        minHeartRateTarget;           // Minimum heart rate target. Range: 0~255 (TBD).
} WorkoutGoal_t;





// [Engineering Class] =============================================================

#ifndef __StateStatusEnum__
#define __StateStatusEnum__

// StateStatusEnum defines different state status modes (Active/Inactive).
typedef enum {
	STATE_INACTIVE = 0x0,  // Inactive state.
	STATE_ACTIVE = 0x1,  // Active state.
} StateStatusEnum;

#endif // __StateStatusEnum__

// EngineeringClass_t defines the structure for holding engineering-related information.
typedef struct {
	StateStatusEnum ledLightFunctionTest; // LED Light Function Test status (Active/Inactive).

} EngineeringClass_t;





// G-system Error Status definition
typedef struct{

	uint32_t ERRS_Speed_Sensor_Warning  : 1,
	         ERRS_Smart_Gateway_Warning : 1,
	         ERRS_Motor_Overheat        : 1,
	         ERRS_RideControl_Warning   : 1,
	         ERRS_COMM_Warning          : 1,
	         ERRS_SyncDrive_Warning     : 1,
	         ERRS_SyncDrive_Error       : 1,
	         ERRS_EnergyPak_Warning     : 1,
			 ERRS_E_SHIFT_Warning       : 1,
			                            : 23;

	uint8_t  DeviceErrorStatus;

}ErrorStatus_t;





// G-system Remote Ask Status definition
typedef struct{
	uint32_t Ask_Heartbeat      : 1,
	         Ask_Confirmation   : 1,
	         Ask_Active_data_1  : 1,
	         Ask_Active_data_2  : 1,
	         Ask_Passive_data_1 : 1,
	         Ask_Passive_data_2 : 1,
	         Ask_Passive_data_3 : 1,
	         Ask_Passive_data_4 : 1,
	                            : 24;
}RemoteAskStatus_t;





/**
* @brief Structure to hold various types of data collected from an E-Bike's different components.
*/
typedef struct {
	SystemStatus_t        systemStatus;         // System status information.
	AssistanceStatus_t    assistanceStatus;     // Assistance status information.
	RidingData_t          ridingData;           // Riding data information.
	StatusNotification_t  statusNotification;   // Status notification information.
	ScreenLayout_t        screenLayout;         // Screen layout configuration.
	EShiftingSystem_t     eShiftingSystem;      // E-Shifting system information.
	EnergypackStatus_t    energyPackStatus;     // Energy pack status information.
	EnergypackStatus_t    subEnergyPackStatus;  // Sub Energy pack status information.
	NavigationInfo_t      navigationInfo;       // Navigation information.
	TimeInfo_t            timeInfo;             // Time information.
	WorkoutGoal_t         workoutGoal;          // Workout goal information.
	EngineeringClass_t    engineeringClass;     // Engineering class information.
	ErrorStatus_t         errorStatus;          // System Error Status
	RemoteAskStatus_t     remoteAskStatus;      // Ask from othe Nodes Status
} EBikeDataCollection_t;






// Populates the E-Bike data collection structure with data received from various sources.
void EBikeDataPopulate(void);

// Returns a pointer to the eBikeDataCollection structure.
EBikeDataCollection_t *get_eBikeDataCollection(void);



#pragma pack(pop)   //restores the original alignment setting.
#endif // GSYS_EBIKE_DATA_COLLECTION_H
