#include "gsys_data_active.h"
#include "gsys_device_configurator.h"
#include "gsys_ebike_data_collection.h"
#include "gsys_rx_data_decoder.h"

// E-Bike Data Collection structure Instance define
static EBikeDataCollection_t eBikeDataCollection = { 0 };


// Returns a pointer to the eBikeDataCollection structure.
EBikeDataCollection_t *get_eBikeDataCollection() {
	return &eBikeDataCollection;
}


// Populates the E-Bike data collection structure with data received from various sources.
void EBikeDataPopulate(){

	// [System status]
	get_eBikeDataCollection()->systemStatus.ridingMode             = (RidingModeEnum)      get_SG_RemoteControlCmd()->Msg.rmod;
	get_eBikeDataCollection()->systemStatus.adjustingMode          = (AdjustingModeEnum)   get_SG_RemoteControlCmd()->Msg.amod;
	get_eBikeDataCollection()->systemStatus.displayMode            = (DisplayModeEnum)     get_SG_RemoteDisplayDataPage0()->Msg.di_mod;
	get_eBikeDataCollection()->systemStatus.displayLanguage        = (DisplayLanguageEnum) get_SG_RemoteDisplayDataPage1()->Msg.d_lang;
	get_eBikeDataCollection()->systemStatus.brandCategory          = (BrandCategoryEnum)   get_SG_RemoteDisplayDataPage1()->Msg.br_cat;
	get_eBikeDataCollection()->systemStatus.unitSystem             = (UnitSystemEnum)      get_SG_RemoteDisplayDataPage1()->Msg.u_sys;

	if (get_device_cfg()->role_of_gsystem == REMOTE1){
		get_eBikeDataCollection()->systemStatus.remoteCmdAck       = (RemoteCommandEnum) get_SG_RemoteDisplayDataPage0()->Msg.rm1cak;
	}
	else if (get_device_cfg()->role_of_gsystem == REMOTE2){
		get_eBikeDataCollection()->systemStatus.remoteCmdAck       = (RemoteCommandEnum) get_SG_RemoteDisplayDataPage0()->Msg.rm2cak;
	}

	get_eBikeDataCollection()->systemStatus.backlightBrightness    = get_SG_RemoteDisplayDataPage1()->Msg.bklt_lv;
	get_eBikeDataCollection()->systemStatus.systemStateOfCharge    = get_SG_RemoteDisplayDataPage0()->Msg.sys_soc;
	get_eBikeDataCollection()->systemStatus.odometer               = get_SG_RemoteDisplayDataPage2()->Msg.odo;
	get_eBikeDataCollection()->systemStatus.remainingCapacity      = get_SG_RemoteDisplayDataPage2()->Msg.re_cap;
	get_eBikeDataCollection()->systemStatus.serviceIntervalMileage = get_SG_RemoteDisplayDataPage2()->Msg.s_im;


	// [Assistance Status]
	get_eBikeDataCollection()->assistanceStatus.assistLevelLCD = (AssistanceLevelLCDEnum) get_SG_RemoteDisplayDataPage0()->Msg.al_lcd;
	get_eBikeDataCollection()->assistanceStatus.assistLevelLED = (AssistanceLevelLEDEnum) get_SG_RemoteDisplayDataPage0()->Msg.al_led;
	get_eBikeDataCollection()->assistanceStatus.remainingRange = get_SG_Cycling()->Msg.rerg;


	// [Riding Data]
	get_eBikeDataCollection()->ridingData.instantaneous.bikeSpeed         = get_DU_CyclingData1()->Msg.spd;
	get_eBikeDataCollection()->ridingData.instantaneous.cadence           = get_DU_CyclingData1()->Msg.cde;

	get_eBikeDataCollection()->ridingData.accumulated.tripDistance        = get_DU_CyclingData2()->Msg.trid;
	get_eBikeDataCollection()->ridingData.accumulated.tripTime            = get_DU_CyclingData2()->Msg.trit;

	get_eBikeDataCollection()->ridingData.nonInstantaneous.averageSpeed   = get_SG_RemoteDisplayDataPage3()->Msg.av_spd;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.maximumSpeed   = get_SG_RemoteDisplayDataPage3()->Msg.ma_spd;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.cyclingPower   = get_SG_RemoteDisplayDataPage4()->Msg.cy_pow;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.maximumPower   = get_SG_RemoteDisplayDataPage4()->Msg.ma_pow;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.averagePower   = get_SG_RemoteDisplayDataPage4()->Msg.av_pow;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.maximumCadence = get_SG_RemoteDisplayDataPage5()->Msg.ma_cde;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.averageCadence = get_SG_RemoteDisplayDataPage5()->Msg.av_cde;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.heartRateValue = get_SG_MoblieDataPage0()->Msg.hr_v;
	get_eBikeDataCollection()->ridingData.nonInstantaneous.altitude       = get_SG_MoblieDataPage0()->Msg.alt_hol;


	// [Status Notification]
	get_eBikeDataCollection()->statusNotification.lightStatus        = (LightStatusEnum)      get_SG_Display()->Msg.Light;
	get_eBikeDataCollection()->statusNotification.motorOverheating   = (StateStatusEnum)      get_SG_RemoteDisplayDataPage0()->Msg.led_bovh;
	get_eBikeDataCollection()->statusNotification.incomingCall       = (StateStatusEnum)      get_SG_MoblieDataPage0()->Msg.call_nst;
	get_eBikeDataCollection()->statusNotification.smsNotification    = (StateStatusEnum)      get_SG_MoblieDataPage0()->Msg.sms_nst;
	get_eBikeDataCollection()->statusNotification.mailNotification   = (StateStatusEnum)      get_SG_MoblieDataPage0()->Msg.mail_nst;
	get_eBikeDataCollection()->statusNotification.gpsActivity        = (StateStatusEnum)      get_SG_MoblieDataPage0()->Msg.gps_act;
	get_eBikeDataCollection()->statusNotification.bluetoothConnected = (ConnectionStatusEnum) get_SG_MoblieDataPage0()->Msg.bt_cnct;
	get_eBikeDataCollection()->statusNotification.phoneBattery       = get_SG_MoblieDataPage0()->Msg.mp_batt;


	// [Screen Layout]
	get_eBikeDataCollection()->screenLayout.mainDataField        = (DataFieldEnum)     get_SG_RemoteDisplayDataPage1()->Msg.df_main;
	get_eBikeDataCollection()->screenLayout.leftDataField        = (DataFieldEnum)     get_SG_RemoteDisplayDataPage1()->Msg.df_left;
	get_eBikeDataCollection()->screenLayout.rightDataField       = (DataFieldEnum)     get_SG_RemoteDisplayDataPage1()->Msg.df_right;
	get_eBikeDataCollection()->screenLayout.rideControlDashField = (RideDashFieldEnum) get_SG_RemoteDisplayDataPage1()->Msg.rdsh_df;
	get_eBikeDataCollection()->screenLayout.pageIndex            = get_SG_RemoteDisplayDataPage1()->Msg.p_idx;


	// [E-Shifting System]
	get_eBikeDataCollection()->eShiftingSystem.activity          = (StateStatusEnum)   get_SG_EShifting()->Msg.shft_en;
	get_eBikeDataCollection()->eShiftingSystem.operationMode     = (EShiftingModeEnum) get_SG_EShifting()->Msg.w_opm;
	get_eBikeDataCollection()->eShiftingSystem.internalGearRatio = get_SG_EShifting()->Msg.w_arig;
	get_eBikeDataCollection()->eShiftingSystem.gearIndex         = get_SG_EShifting()->Msg.w_grix;
	get_eBikeDataCollection()->eShiftingSystem.desiredCadence    = get_SG_EShifting()->Msg.w_dudc;
	get_eBikeDataCollection()->eShiftingSystem.gearOffsetNumber  = get_SG_EShifting()->Msg.gofs_w;


	// [Energy Pack Status]
	get_eBikeDataCollection()->energyPackStatus.relativeStateOfCharge = get_EnergyPack_Capacity()->Msg.rosc;
	get_eBikeDataCollection()->energyPackStatus.batteryState          = (BatteryStateEnum) get_EnergyPack_DualBattery()->Msg.b_state;


	// [Sub Energy Pack Status]
	get_eBikeDataCollection()->subEnergyPackStatus.relativeStateOfCharge = get_SubEnergyPack_Capacity()->Msg.rosc;
	get_eBikeDataCollection()->subEnergyPackStatus.batteryState          = (BatteryStateEnum) get_SubEnergyPack_DualBattery()->Msg.b_state;


	// [Navigation Info] 
	get_eBikeDataCollection()->navigationInfo.activity                   = (StateStatusEnum)           get_SG_MoblieDataPage1()->Msg.nav_en;
	get_eBikeDataCollection()->navigationInfo.firstInstruction           = (NavigationInstructionEnum) get_SG_MoblieDataPage1()->Msg.nav_ins_first;
	get_eBikeDataCollection()->navigationInfo.nextInstruction            = (NavigationInstructionEnum) get_SG_MoblieDataPage1()->Msg.dnav_next;
	get_eBikeDataCollection()->navigationInfo.distanceToFirstAction      = get_SG_MoblieDataPage1()->Msg.dnav_first;
	get_eBikeDataCollection()->navigationInfo.distanceToNextAction       = get_SG_MoblieDataPage1()->Msg.dnav_next;
	get_eBikeDataCollection()->navigationInfo.estimatedDistanceToArrival = get_SG_MoblieDataPage2()->Msg.e_da;
	get_eBikeDataCollection()->navigationInfo.estimatedTimeOfArrival     = get_SG_MoblieDataPage2()->Msg.e_ta;


	// [Time Info]
	get_eBikeDataCollection()->timeInfo.enable             = (EnableDisableEnum) get_SG_MoblieDataPage0()->Msg.tim_en;
	get_eBikeDataCollection()->timeInfo.displayTimeFormat  = (TimeFormatEnum)    get_SG_MoblieDataPage0()->Msg.tim_fmt;
	get_eBikeDataCollection()->timeInfo.currentHour        = get_SG_MoblieDataPage0()->Msg.tim_h;
	get_eBikeDataCollection()->timeInfo.currentMinute      = get_SG_MoblieDataPage0()->Msg.tim_m;


	// [Workout Goal]
	get_eBikeDataCollection()->workoutGoal.workoutMode               = get_SG_MoblieDataPage3()->Msg.wkt_mod;
	get_eBikeDataCollection()->workoutGoal.distanceToTarget          = get_SG_MoblieDataPage3()->Msg.d_tgt;
	get_eBikeDataCollection()->workoutGoal.remainingDistanceToTarget = get_SG_MoblieDataPage3()->Msg.re_dtgt;
	get_eBikeDataCollection()->workoutGoal.targetWorkoutTime         = get_SG_MoblieDataPage4()->Msg.t_tgt;
	get_eBikeDataCollection()->workoutGoal.remainingTimeToTarget     = get_SG_MoblieDataPage4()->Msg.re_ttgt;
	get_eBikeDataCollection()->workoutGoal.targetCalories            = get_SG_MoblieDataPage5()->Msg.c_tgt;
	get_eBikeDataCollection()->workoutGoal.remainingCaloriesToTarget = get_SG_MoblieDataPage5()->Msg.re_ctgt;
	get_eBikeDataCollection()->workoutGoal.caloriesBurned            = get_SG_MoblieDataPage5()->Msg.c_abr;
	get_eBikeDataCollection()->workoutGoal.maxHeartRateTarget        = get_SG_MoblieDataPage6()->Msg.hr_tgma;
	get_eBikeDataCollection()->workoutGoal.minHeartRateTarget        = get_SG_MoblieDataPage6()->Msg.hr_tgmi;


	// [Engineering Class]
	get_eBikeDataCollection()->engineeringClass.ledLightFunctionTest = (StateStatusEnum) get_SG_RemoteDisplayDataPage0()->Msg.led_ft;

}
