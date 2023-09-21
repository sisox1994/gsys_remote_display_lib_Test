#ifndef GSYS_ACTIVE_DATA_H
#define GSYS_ACTIVE_DATA_H

#include <stdint.h>

#pragma pack(push)   // preserves the current alignment setting.
#pragma pack(1)      // directive aligns structure members tightly in sequential order without padding, conserving memory by avoiding unnecessary gaps.

// G-system Data structure definition. {Active Data}

// [Smart Gateway] ===========================================================================

// Data address = 0x1 RemoteControlCmd
typedef union{

	uint8_t Bytes[6];
	struct
	{
		uint8_t ast_down : 1,
				ast_up   : 1,
				sw_info  : 1,
				sw_lig   : 1,
				sw_batt  : 1,
				aslp     : 1,
				mslp     : 1,
					     : 1;
		uint8_t w_ast  : 1,
		        hbrake : 1,
			    rst    : 1,
			    Rvd    : 4,
		        ina_er : 1;
		uint8_t vthro;
		uint8_t amod : 5,     // Adjusting mode.
		        nce  : 1,
		        lce  : 1,
			    rmod : 1;     // Riding mode with power assistance.
		uint8_t rst_f   : 1,
		        rst_l   : 1,
			    rst_ot  : 1,
				rst_aac : 1,
				clb_pa  : 1,
				st_mm   : 1,
				clb_ca  : 1,
				clb_mca : 1;
		uint8_t mod_dec : 1,
		        mod_inc : 1,
			    mod_cfm : 1,
				Rvd2    : 4,
				DU11    : 1;
	}Msg;

}SG_RemoteControlCmd_t;



// Data address = 0x2  Display
typedef union{

	uint8_t Bytes[5];
	struct
	{
		uint8_t  ast   : 4,
				 Light : 2,  // Light Status. (0: Light Off, 1: Light On, 2: Low beam, 3: High beam)
				 lbatt : 1,
					   : 1;
		uint8_t  imod;
		uint16_t apar;
		uint8_t  mtqs : 4,
		         gaus : 4; 
	}Msg;

}SG_Display_t;



// Data address = 0x3   Cycling
typedef union{
	
	uint8_t Bytes[5];
	struct
	{
		uint16_t idata;
		uint8_t  idata_tm : 4,
		                  : 4;
		uint16_t rerg;          // Remaining range. (km)  0xFFFF = NULL
	}Msg;

}SG_Cycling_t;



// Data address = 0x6  RemoteDisplayData
typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  page;
		uint8_t  al_lcd : 4,    // Assistance levels for LED display.
		         al_led : 4;    // Assistance levels for LCD display.
		uint8_t  di_mod : 4,    // Display Mode.
		                : 4;
		uint8_t  sys_soc;       // System state of charge.
		uint8_t  rm1cak;        // Remote 1 CMD ack.
		uint8_t  led_ft : 1,    // LED Light Function Test.
		         rm2cak : 7;    // Remote 2 CMD ack.
		uint8_t  led_bovh : 1,  // LED blink indicates motor overheating.
		                  : 7;
	}Msg;

}SG_RemoteDisplayDataPage0_t;

typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  page;
		uint8_t  bklt_lv : 4, // Backlight Brightness.
		         d_lang  : 4; // Display Language.
		uint8_t  df_main;     // Data Field. [Main]
		uint8_t  Rvd;
		uint8_t  df_left;     // Data Field. [Left]
		uint8_t  p_idx  : 4,  // Page index.
		         u_sys  : 1,  // Unit system.    (0x0: Metric, 0x1: Imperial)
			     br_cat : 2,  // Brand category. (0x0: Giant, 0x1: Liv, 0x2: Momentum)
					    : 1;
		uint8_t  df_right;    // Data Field. [Right]
		uint8_t  rdsh_df;     // RideControl Dash (Remote 2 in 1) data field.
	}Msg;

}SG_RemoteDisplayDataPage1_t;

typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  page;
		uint16_t re_cap;  // Remaining_Capacity.
		uint16_t odo;     // Odometer. (km)
		uint16_t s_im;    // Service Interval Mileage.
	}Msg;

}SG_RemoteDisplayDataPage2_t;

typedef union{

	uint8_t Bytes[5];
	struct
	{
		uint8_t  page;
		uint16_t av_spd;  // Average Speed. (0.1 kph)
		uint16_t ma_spd;  // Maximum Speed. (0.1 kph)
	}Msg;

}SG_RemoteDisplayDataPage3_t;

typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  page;
		uint16_t cy_pow;  // Cycling Power. (0.1 watt)
		uint16_t ma_pow;  // Maximum Power. (0.1 watt)
		uint16_t av_pow;  // Average Power. (0.1 watt)
	}Msg;

}SG_RemoteDisplayDataPage4_t;

typedef union{

	uint8_t Bytes[5];
	struct
	{
		uint8_t  page;
		uint16_t ma_cde;  // Maximum Cadence. (0.1 rpm)
		uint16_t av_cde;  // Average Cadence. (0.1 rpm)
	}Msg;

}SG_RemoteDisplayDataPage5_t;



// Data address = 0x7  MoblieData
typedef union{

	uint8_t Bytes[8];
	struct
	{
		uint8_t  page;
		uint8_t  bt_cnct  : 1,   // The status of Bluetooth connectivity.
		         gps_act  : 1,   // The status of GPS activity.
		         mail_nst : 1,   // The Mail notification status.
		         sms_nst  : 1,   // The SMS notification status.
		         call_nst : 1;   // The incoming Call notification status.
		uint16_t alt_hol;        // Altitude means the height of a location. (m)
		uint8_t  tim_h   : 5,    // The current hour of the time. (hour)
		         tim_fmt : 2,    // Display of time format. (0: 12-hour , 1: 24-hour)
		         tim_en  : 1;    // Enable/Disable Time Functionality.
		uint8_t  tim_m;          // The current minute of the time. (minute)
		uint8_t  hr_v;           // Heart rate value. (bpm)
		uint8_t  mp_batt;        // The mobile phone battery percentage. (%)
	}Msg;

}SG_MoblieDataPage0_t;

typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  page;
		uint8_t  nav_ins_first : 7,     // First Navigation Instructions.
		         nav_en        : 1;   	// Enable/Disable Navigation Functionality.
		uint16_t dnav_first;            // Distance to the first navigation action. (m)
		uint8_t  nav_ins_next : 7,      // Next Navigation Instructions.
		                      : 1;
		uint16_t dnav_next;             // Distance to the next navigation action. (m)
	}Msg;

}SG_MoblieDataPage1_t;

typedef union{

	uint8_t Bytes[5];
	struct
	{
		uint8_t  page;
		uint16_t e_da;  // Estimated Distance to Arrival. EDA (0.1 km)
		uint16_t e_ta;  // Estimated Time of Arrival.     ETA (minute)
	}Msg;

}SG_MoblieDataPage2_t;

typedef union{

	uint8_t Bytes[8];
	struct
	{
		uint8_t  page;
		uint8_t  wkt_mod;        // Workout mode.
		uint64_t d_tgt   : 24,   // Distance to the target.
		         re_dtgt : 24;   // Remaining distance to the target.         
	}Msg;

}SG_MoblieDataPage3_t;

typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  page;
		uint64_t t_tgt   : 24,  // Target workout time.
		         re_ttgt : 24;  // Remaining time to the target
	}Msg;

}SG_MoblieDataPage4_t;

typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  page;
		uint16_t c_tgt;    // Target calories.
		uint16_t re_ctgt;  // Target calories remaining.
		uint16_t c_abr;    // Calories already burned.
	}Msg;

}SG_MoblieDataPage5_t;

typedef union{

	uint8_t Bytes[3];
	struct
	{
		uint8_t  page;
		uint8_t  hr_tgma;  // Maximum heart rate target. (bpm)
		uint8_t  hr_tgmi;  // Minimum heart rate target. (bpm)
	}Msg;

}SG_MoblieDataPage6_t;



// Data address = 0xF  E-Shifting
typedef union{

	uint8_t Bytes[6];
	struct
	{
		uint8_t  w_opm   : 4,  // Write operation mode.
		         cal     : 1,	
	             cae     : 1,
	             shft_r  : 1,
		         shft_en : 1;  // E-Shifting system Enable.
		uint8_t  w_arig;       // Write actual ratio of internal gear. (0.1 ratio)
		uint8_t  w_grix;       // Write gear index.
		uint8_t  w_dudc;       // DU desired cadence. (rpm)
		uint8_t  brsoc;
		uint8_t  gofs_w;       // Gear offset number.
	}Msg;

}SG_EShifting_t;






// [Drive Chain] ===========================================================================

// Data address = 0x2  Cycling data 1
typedef union{

	uint8_t Bytes[8];
	struct
	{
		uint16_t spd;    // Bike Speed. (0.1 kph)
		uint16_t trq;   
		uint16_t cde;    // Cadence. (0.1 rpm)
		uint16_t acaur;
	}Msg;

}DU_CyclingData1_t;



// Data address = 0x3   Cycling data 2
typedef union{

	uint8_t Bytes[8];
	struct
	{
		uint8_t  gshift;  
		uint8_t  rsocv;   
		uint16_t trid;    // Trip distance.  (0.1 km)
		uint16_t trit;    // Trip time.      (minute)
		uint16_t odo;
	}Msg;

}DU_CyclingData2_t;






// [Energy pack] ===========================================================================

// Data address = 0x1  Capacity
typedef union{

	uint8_t Bytes[7];
	struct
	{
		uint8_t  rosc;  // Relative state of charge. (%)
		uint16_t rc;    // remain capacity. (mAh)
		uint16_t fcc;   // full charge capacity. (mAh)
		uint16_t dc;    // design capacity. (mAh)
	}Msg;

}EnergyPack_Capacity_t;



// Data address = 0x4  Dual Battery
typedef union{

	uint8_t Bytes[4];
	struct
	{
		uint8_t d_ecode;    // Dual energy pack system error code.
		uint8_t b_status;   // Battery status.  (0x0: Non-discharge, 0x1: Discharge.)
		uint8_t b_state;    // Battery state.
		uint8_t cap_l;      // Capacity level.
	}Msg;

}EnergyPack_DualBattery_t;





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






// [Remote 1] ===========================================================================

// Data address = 0x1  RemoteControlCmd & ButtonStatus
typedef union{

	uint8_t Bytes[2];
	struct
	{
		RemoteCommandEnum rm_cmd;      // Remote 1 CMD.
		uint8_t           btn_s1 : 1,  // Button state of On/OFF.
		                  btn_s2 : 1,  // Button state of Mode_Up.
		                  btn_s3 : 1,  // Button state of Mode_Down.
		                  btn_s4 : 1,  // Button state of Walk_Assist.
		                  btn_s5 : 1,  // Button state of Light.
		                  btn_s6 : 1,  // Button state of Information.
		                  btn_s7 : 1,  // Button state of Smart_Assist.
		                  btn_s8 : 1;  
	}Msg;

}Remote1CmdButtonStatus_t;






// [Remote 2] ========================================================================

// Data address = 0x9  RemoteControlCmd & ButtonStatus
typedef union{

	uint8_t Bytes[3];
	struct
	{
		RemoteCommandEnum rm_cmd;      // Remote 2 CMD.
		uint8_t           btn_s1 : 1,  // Button state of On/OFF.
		                  btn_s2 : 1,  // Button state of Ring_L1.
		                  btn_s3 : 1,  // Button state of Ring_L2.
		                  btn_s4 : 1,  // Button state of Ring_L3.
		                  btn_s5 : 1,  // Button state of Ring_R1.
		                  btn_s6 : 1,  // Button state of Ring_R2.
		                  btn_s7 : 1,  // Button state of Ring_R3.
		                  btn_s8 : 1;
		uint8_t           conn_rl : 1, // The connection status of the "Ring_L".
		                  conn_rr : 1, // The connection status of the "Ring_R".
		                          : 6;
	}Msg;

}Remote2CmdButtonStatus_t;



#pragma pack(pop)   //restores the original alignment setting.
#endif // GSYS_ACTIVE_DATA_H
