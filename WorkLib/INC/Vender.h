/**
 * @file Vender.h
 *
 *  Vender.h controls the features enabled or disabled
 *
 *
 * @version $Revision: 75 $
 * @author JLJuang <JL.Juang@zeitecsemi.com>
 * @note Copyright (c) 2010, Zeitec Semiconductor Ltd., all rights reserved.
 * @note
*/

#ifndef __VENDER_H__
#define __VENDER_H__

/// =============================================================///
/// Feature area
/// =============================================================///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 1. Boot code Check Signature (unused)
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_CHECK_SIGNATURE                                    ///< (DEFAULT : ON), This feature enables the firmware check sum (Unfinished)

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 2. INT Pin
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_INT_PIN	  FEATURE_INT_P35

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 3. GPIO
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_GIO_ENABLE                                         ///< (DEFAULT : ON), This feature enables and disable the GPIO control
//#define FEATURE_GIO_DEBUG

//#define FEATURE_CMD_SWITCH_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 4. Debug Information Print
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_DEBUG_PRINT                                     ///< (DEFAULT : OFF), This feature print value via the GIO2, and GIO0

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 5. I2C
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_I2C_DEBUG                                       ///< (DEFAULT : OFF), This feature shows the I2C debug GPIO
#define FEATURE_ZETOUCHCMD_CLEAR_TXIDX 

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 6. ADC
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_ADC_DEBUG                                         ///< (DEFAULT : OFF), This feature shows the ADC debug GPIO
//#define FEATURE_MUTUAL_DEV_DEBUG                                  ///< (DEFAULT : OFF), This feature shows the Mutual Dev Raw data

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 7. Init-Scan
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_INIT_ISR_SCAN
//#define FEATURE_INIT_REGION_SCAN                                ///< (DEFAULT : ON), PN Code 
//#define FEATURE_INIT_REGION_SCAN_EVEN_PN_ODD_GND

#define FEATURE_INIT_SCAN
//#define FEATURE_SNE_AXIS_INIT_SCAN
#define FEATURE_ALLPOINT_SCAN

//#define FEATURE_INIT_SCAN_DEBUG                                 ///< (DEFAULT : OFF), This feature shows Init-Scan debugging information
//#define FEATURE_INIT_MOVING_AVG                                   ///< (DEFAULT : OFF), This feature enables the moving average of init-scan
#if defined(FEATURE_CLUSTER_ENABLE) && defined(FEATURE_1T2R_ARCHITECTURE)
#define FEATURE_WATER_INIT_SCAN
#define FEATURE_WATER_INIT_COORD
//#define FEATURE_WATER_INIT_SCAN_DEBUG
#endif

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 8. Mutual-Scan
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
///#define FEATURE_MUTUAL_SCAN_DEBUG                               ///< (DEFAULT : OFF), [MDEV] This feature enables the Mutual-Scan debugging information

///#define FEATURE_INITIAL_DEV_PROCESS
#define FEATURE_DRIVE_DEV_PROCESS                                   ///< (DEFAULT : ON), Drive Dev process 
#define FEATURE_SENSE_DEV_PROCESS                                   ///< (DEFAULT : OFF), Sense Dev process

#ifdef FEATURE_DRIVE_DEV_PROCESS
#define FEATURE_DRIVE_DEV_PROC_SCHMIT_TRIGGER
#define FEATURE_DRIVE_DEV_PROCESS_MA_FILTER
  #ifdef FEATURE_DRIVE_DEV_PROCESS_MA_FILTER
  #define FEATURE_DRIVE_DEV_PROCESS_MA_FILTER_LIMIT_TH
  #define FEATURE_DRIVE_DEV_PROCESS_MA_FILTER_FINGER_PROTECT
  #endif
#endif

#ifdef FEATURE_SENSE_DEV_PROCESS
#define FEATURE_SENSE_DEV_PROCESS_MA_FILTER
  #ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER
  #define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_AVG
  #define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_NEW_AVG
  #define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_DIV_BY_3
  #define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_FINGER_PROTECT_ALWAYS_ON
  #define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_NO_DEV_CUT
  #define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_PROC_PRIORITY_CTRL
  #define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_FINGER_PROTECT_INTEN_CTRL
  ///#define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_FINGER_PROTECT_INTEN_CTRL_DEBUG
  ///#define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_PROC_PRIORITY_CTRL_DEBUG
  ///#define FEATURE_SENSE_DEV_PROCESS_MA_FILTER_NEW_AVG_DEBUG
  #endif
#endif

#ifdef FEATURE_INITIAL_DEV_PROCESS
#define FEATURE_INITIAL_DEV_PROCESS_MA_FILTER
#define FEATURE_INITIAL_DEV_PROCESS_BOTH
#define FEATURE_INITIAL_DEV_PROCESS_SCALING
#endif

#define FEATURE_DEVPROC_INCLUDE_NEG
#define FEATURE_DEVCUT_NEG_VAL_NOT_PROC

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 9. Mainloop Debug
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_MAINLOOP_DEBUG                                  ///< (DEFAULT : OFF), [MDEV] This feature shows mainloop debugging information
//#define FEATURE_MAIN_LOOP_BREAK_POINT                           ///< (DEFAULT : OFF), [MDEV] This feature enablesbreak point at mainloop use MDEV
//#define FEATURE_RESET_SCAN_DEV_BUFFER                                ///< (DEFAULT : OFF), [MDEV] This feature enables clear the DEV buffer in each mainloop round

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 10. Swap the Mutual Scan DV buffer
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 11. Finger Search Debug
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_FINGER_SEARCH_DEBUG                               ///< (DEFAULT : OFF), This feature enables Finger Search Debugging information 

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 12. Report finger to host
///----------------------------------------------------------------------------------------------- ------------------------------------------------------------///
#define FEATURE_FINGER_DEBOUNCE
#define FEATURE_FINGER_UP_DEBOUNCE_ALG														///< (DEFAULT : ON) ON : Finger Up Debouncing Alg New
		
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 13. Base Tracking and ReCalibration
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_RECALIBRATION                   ///< (DEFAULT : ON),  This feature enables re-calibration function 
#define FEATURE_BASE_TRACKING                   ///< (DEFAULT : ON),  This feature enables base tracking function 

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 14. Watch Dog
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#ifndef FEATURE_MAIN_LOOP_BREAK_POINT
  #define FEATURE_WATCH_DOG                                         ///< (DEFAULT : ON),  This feature enables watch dog protection in the system
#endif ///< for FEATURE_MAIN_LOOP_BREAK_POINT

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 15.  Deep Sleep
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_DEEP_SLEEP                                         ///< (DEFAULT : ON),  This feature enables DEEP SLEEP function

#ifdef FEATURE_DEEP_SLEEP
  #ifndef FEATURE_CIRCUIT_POWER_DOWN
    #define FEATURE_CIRCUIT_POWER_DOWN 
  #endif ///< for FEATURE_CIRCUIT_POWER_DOWN
  #ifndef FEATURE_WAKE_UP  
    #define FEATURE_WAKE_UP
  #endif ///< for FEATURE_WAKE_UP  
#endif ///< for FEATURE_IDLE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 16.  IDLE
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_IDLE                                               ///< (DEFAULT : ON),  This feature enables IDLE function

#ifdef FEATURE_IDLE
  #ifndef FEATURE_CIRCUIT_POWER_DOWN
    #define FEATURE_CIRCUIT_POWER_DOWN 
  #endif ///< for FEATURE_CIRCUIT_POWER_DOWN
  #ifndef FEATURE_WAKE_UP  
    #define FEATURE_WAKE_UP
  #endif ///< for FEATURE_WAKE_UP
#endif ///< for FEATURE_IDLE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 17.  Report Data
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_REPORT_COORDINATE_FINGERS                      ///< (DEFAULT : ON), This feature reports the coordinate finger record
//#define FEATURE_WIN8_DATAFORMAT

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 18. Data Format
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_DATA_FORMAT_MUTUAL_SCAN_ADBASE                ///< (DEFAULT : ON), This feature enables the data format Mutual-Scan ADBASE Data
#define FEATURE_DATA_FORMAT_MUTUAL_SCAN_DEV                   ///< (DEFAULT : ON), This feature enables the data format Mutual-Scan Dev Data
	///#define FEATURE_MUTUAL_DEV_SHOW_INIT_DEV									/// show init dev in mutual dev

#define FEATURE_DATA_FORMAT_INIT_SCAN_ADBASE                  ///< (DEFAULT : ON), This feature enables the data format Init-Scan ADBASE Data
#define FEATURE_DATA_FORMAT_INIT_SCAN_DEV                     ///< (DEFAULT : ON), This feature enables the data format Init-Scan Dev Data

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 19.  Finger Search algorithm 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_CLUSTER_ENABLE
#ifdef FEATURE_CLUSTER_ENABLE
#define FEATURE_MERGE_CLOSE_CLUSTER_FINGER
#define FEATURE_CLUSTER_LIMIT_LOCAL_PEAKTH

#define FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
	
//#define FEATURE_CLUSTER_PEAK_MERGE_DEUG

//#define FEATURE_DEBUG_MERGE_CLOSE_CLUSTER_FINGER

//#define FEATURE_CLUSTER_DEBUG_COORD_DATA
//#define FEATURE_CLUSTER_DEBUG_ENABLE

#define FEATURE_CLUSTER_MERGE_V61
//#define FEATURE_CLUSTER_MERGE_V61_DEBUG

#define FEATURE_CLUSTER_MAXPEAK_CHECK
#define FEATURE_CLUSTER_MERGE_LOCAL_PEAK_SORT

#endif

//#define FEATURE_NINE_SQUARE_ENABLE                            ///< (DEFAULT : ON), This feature enables the nine-square algorithm
#ifdef FEATURE_NINE_SQUARE_ENABLE
#define FEATURE_ONE_FINGER_CLUSTER                            ///< (DEFAULT : OFF), This feature Enhance One Finger Algorithm
#define FEATURE_SHARP_DEV_CUT                                 ///< (DEFAULT : OFF), This feature Enhance sharp dev cut algorithm
#endif
//#define FEATURE_CLUSTER_ID_DEBUG


#define FEATURE_PALM_DETECT                                   ///< (DEFAULT : ON), This feature enables the palm detection with init-scan

//#define FEATURE_MERGE_TWO_FINGER                               ///< (DEFAULT : ON), Merge Two Finger Function 

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 20.  Key Function
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_REAL_KEY                                      ///< (DEFAULT : ON), This feature enables real key function
//#define FEATURE_DEBUG_REAL_KEY  

//#define FEATURE_VIRTUAL_KEY                                   ///< (DEFAULT : ON), This feature enables virtual key function

#if defined(FEATURE_REAL_KEY) ||defined(FEATURE_VIRTUAL_KEY)
#define FEATURE_KEY_DATAFORMAT_REPORT_NEW_VER  										///< Control the Report dataformat
#endif

#ifdef FEATURE_REAL_KEY
#define FEATURE_DATA_FORMAT_KEY_MUTUAL_SCAN_ADBASE            ///< (DEFAULT : ON), This feature enables the data format Key Mutual-Scan ADBASE Data
//#define FEATURE_DATA_FORMAT_KEY_MUTUAL_SCAN_DEV               ///< (DEFAULT : ON), This feature enables the data format Key Mutual-Scan Dev Data
#define FEATURE_DATA_FORMAT_KEY_DATA                          ///< (DEFAULT : ON), This feature enables the data format Key Mutual-Scan Dev + one valid byte Data
#endif 

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 21.  Heavy press average all
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_HEAVY_PRESS                                     ///< (DEFAULT : ON), This feature enables heavy press function
//#define FEATURE_MUTUAL_SCAN_DEV_DETECT_HEAVY_PRESS 							///< (DEFAULT : ON), This feature enables detect heavy press during mutual scan

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 22.  Software DEV filter
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 23.  Specify cut dev
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_SPECIFY_DEV                                     ///< (DEFAULT : ON), This feature enables the cut dev depending on the sense trace

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 24.  RC Trim to change frequency
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 25.  Mutual dev data moving average function
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 26.  CO-Axis Process
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_CO_AXIS_PROCESS                                 ///< (DEFAULT : ON), This feature enables the moving average function at the mutual dev data

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 27.  Charger Noise Detection
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 28.  Power Saving mode
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_POWER_SAVE_MODE                                   ///< (DEFAULT : OFF), This feature enable the power save mode to save the normal power from 17mA to 7 mA


#define FEATRUE_TURNOFF_UNUSED_ADC //Don't turn on the ADCs which are not used in run time scan
//#define FEATRUE_MCU_IDLE_IN_WAITFORSCAN ///< Need also turn on FEATURE_NEW_PERIOD_CONTROL

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 29.  TOUCH HOVER SENSOR FUNCTION
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_TOUCH_HOVER_SENSOR                   ///< (DEFAULT : ON), This feature enable the touch hover sense function
//#define FEATURE_TRACEIO_HOVER_SENSOR

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 30.  Vertical Mutual Dev Cut
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 31.  Process Coordinate with Raw Data
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#ifndef FEATURE_CLUSTER_DEBUG_ENABLE
#define FEATURE_PROCESS_COORDINATE_WITH_RAW_DATA                   ///< (DEFAULT : ON), This feature enable the Process Coordinate with Raw Data
#endif
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 32.  Coordinate shift compensation
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#if defined(FEATURE_HTYPE_DEV_RE_MAPPING) || defined(FEATURE_LTYPE_DEV_RE_MAPPING)
#define FEATURE_COOR_COMP                                      ///< (DEFAULT : OFF), This feature Coordinate shift compensation
//#endif

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 33.  Finger Schmitter Trigger
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_FINGER_SCHMIT_TRIGGER

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 34.  One Finger Cluster Algorithm
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 35.  Frequency Hopping
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_DYNAMIC_FREQ_TRAN_MODE_ON
//#define FEATURE_NOISE_DETECTION_MODE
//#define FEATURE_NOISE_DETECTION_MODE_DEBUG
#define FEATURE_HW_FREQUENCY_HOP
#define FEATURE_BOOT_FREQUENCY_HOP
#define FEATURE_DYNAMIC_FREQUENCY_HOP
//#define FEATURE_HW_FREQUENCY_HOP_DEBUG
//#define FEATURE_FREQUENCY_HOP_NOW_TONE_DEBUG
#define FEATURE_PN_VIOLATE_FIX

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 36.  Border compensation algorithm
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#ifdef FEATURE_NINE_SQUARE_ENABLE  
//#define FEATURE_BORDER_DEV                                    ///< (DEFAULT : ON), Border compensation with Dev compensate
//#define FEATURE_BORDER_DYNAMIC_DEV
#endif 

#define FEATURE_BORDER_COOR
#define FEATURE_REV_131
#define FEATURE_BORDER_DEV_INTERNAL 	
//#define  FEATURE_BORDER_WAVE_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 37. Movtion Vector Algorithm
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_COORD_MOTION_VECTOR

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 38.  Power Saving
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_QUICK_IDLE                                    ///< (DEFAULT : ON), Quick Idle

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 39.  Force Finger Up when distance too long
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_FORCE_FINGER_UP_DIST                                ///< (DEFAULT : ON), fix the smooth bug

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 40.  Region Scan
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_REGION_SCAN 															 ///< (DEFAULT : ON), PN Code

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 41. Timer
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_TIMER                                     ///< (DEFAULT : ON), timer
#define FEATURE_NEW_PERIOD_CONTROL
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 42. Dev data Type
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_16BIT_DEV                                     ///<
#ifdef FEATURE_16BIT_DEV
	#define MUTUAL_DATA_TYPE 2
#else ///< for FEATURE_16BIT_DEV
	#define MUTUAL_DATA_TYPE 1
#endif ///< for FEATURE_16BIT_DEV

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 43.  Smoothing Algorithm
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_SMOOTHING_ALGORITHM

#define FEATURE_IIR_FILTER_SMOOTHING                              ///< (DEFAULT : ON), This feature enabled IIR Filter

#define FEATURE_IIR_FILTER_SMOOTHING_RUN_1ST_3PTS

#define FEATURE_IIR_FILTER_SMOOTHING_SCALING                      ///< (DEFAULT : ON), This feature enabled IIR Filter scaling for higher SNR
///#define FEATURE_IIR_FILTER_SMOOTHING_SCALING_DEBUG
//#define FEATURE_KALMAN_FILTER_SMOOTHING 												///< (DEFAULT : OFF), This feature enabled Kalman Filter
//#define FEATURE_SMOOTHING_DBG 																	///< (DEFAULT : OFF), This feature enabled raw finger without smoothing to finger#1	
//#define FEATURE_GG_FILTER_SMOOTHING                              ///< (DEFAULT : OFF), This feature enabled GG Filter
//#define FEATURE_GG_FILTER_ENHANCE
//#define FEATURE_GG_FILTER_FIX 

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 44. Compensate Mutual Dev with Iitial Dev 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_COMP_MUT_WITH_INIT
#define FEATURE_COMP_MUT_WITH_INIT_OPTION_EN
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 45.  Power base Track after Reset
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_POWER_BASE_TRACK
#define FEATURE_REK_POWER_BASE_TRACK

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 46.  Show -Dev
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 47.  Coord Edge Limit
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_COORD_EDGE_POSITION_LOCK                                ///< Limit the Report-Coord Max/Min value

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 48.  Gesture
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_GESTURE_WAKEUP

#define REPORT_GESTURE_POINTS_LOG_METHOD

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 49  Finger Tracking Debounce
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_TRACKING_DISTANCE_LIMIT

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 50  Merge Close Finger
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#ifdef FEATURE_NINE_SQUARE_ENABLE 
#define FEATURE_MERGE_CLOSE_NINESQU_FINGER
//#define FEATURE_ADV_NINE_SQAURE
//#define FEATURE_MERGE_DEBUG_CLOSE_FINGER
//#define FEATURE_ADV_DEBUG_NINE_SQAURE

#endif
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 51  Switch Drive Sense
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_SWITCH_DRIVE_SENSE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 52  Check Sum 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_CHECK_SUM

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 53  Finger Tracking
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_ONEWAY_COORD_TRACK
#define FEATURE_SEARCH_FINGER_TOUCH_FLAG	

#define FEATURE_TRACK_PREDICT_COORD   ///< if(true) track ID use predic-coord, else use last-report-coord
//#define FEATURE_ADVANCE_COORD_TRACK
//#define FEATURE_ADVANCE_COORD_TRACK_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 54  Stack Pointer Report / 12*1024 - (stack_pointer report value) = stack used, reported by finger mode 1st-finger x/y coordinate 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_STACK_USED_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 55  Base Remainder Resume
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_BASE_AVG_REMIDER_RESUME

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 56  Drive Axis Initial Large Neg Rek flow
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#ifdef FEATURE_CLUSTER_ENABLE 
#define FEATURE_INIT_ABNORMAL_REK
#define FEATURE_MUT_ABNORMAL_REK	 
//#define FEATURE_MUT_PARTIAL_REK	
//#endif
//#define FEATURE_MUT_PARTIAL_CROSS_SET	 

//#define FEATURE_DEBUG_INIT_ABNORMAL_REK
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 57.  For Loop Copy In Interrupt
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_SENSE_AXIS_DEV_RATIO
#define FEATURE_AXIS_DEV_RATIO_ALG
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 58.  Ring Buffer For Dynamic Coordinate Data
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_RING_BUFFER
//#define FEATURE_DEBUG_RING_BUFFER

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 56.  Avoid Report Coordinate (0,0) 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_AVOID_ZERO_COORD

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 57.  TAP issue
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_AVOID_TAP_LINE
//#define FEATURE_DEBUG_AVOID_TAP_LINE
#define FEATURE_AVOID_TAP_LINE_WHEN_FINGER_UP_DEB
//#define FEATURE_AVOID_TAP_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 58. enhance decimation when move < SteadyRange
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_ENHANCE_DECIMA_STADY_RANGE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 59. H type Dev Array Remapping (Compile Batch Option)
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_HTYPE_DEV_RE_MAPPING
#ifdef FEATURE_HTYPE_DEV_RE_MAPPING
	#define FEATURE_HTYPE_DEV_RE_MAPPING_REV_153 ///< for Modification back : X*(Y-2) back to X*Y
	#define FEATURE_HTYPE_DEV_RE_MAPPING_REV_167 ///< for Modification back : X*(Y-2) back to X*Y
#endif
//#define DEBUG_HTYPE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 66. Fixxed IIR in border area
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_FIX_IIR_IN_BORDER

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 67. Raw Data Copy At TaskRoundInit
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_RAW_DATA_COPY

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 68. Extend DriveMax to (DriveMax+1)
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_MERGE_DEV_ARRAY
	//#define FEATURE_MERGE_DEV_ARRAY_DEBUG
	
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 69. Coord Shift relate to Trace-Mid-Coord
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_COOR_EXTEND_BASE_ON_DRIVE_TRACE ///<  
  //#define FEATURE_COOR_EXTEND_BASE_ON_DRIVE_TRACE_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 70. Coord Axis Shift 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_COOR_SHIFT_BASE_ON_SENSE_TRACE ///<  
// #define FEATURE_COOR_SHIFT_BASE_ON_SENSE_TRACE_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 71. Allpoint Scan Heavy Press Alg : Cut Average Dev
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_ALLPOINT_HEAVY_PRESS_CUT_AVG_ALG ///<  
 //#define FEATURE_ALLPOINT_HEAVY_PRESS_CUT_AVG_ALG_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 72. Lighting type Dev Array Remapping (Compile Batch Option)
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_LTYPE_DEV_RE_MAPPING
//#define DEBUG_HTYPE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 72.  1T2R TP (Compile Batch Option)
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_1T2R_ARCHITECTURE
#ifdef FEATURE_1T2R_ARCHITECTURE
#define FEATURE_1T2R_ARCHITECTURE_DEVPRORCESS
#define FEATURE_1T2R_ARCHITECTURE_CROSSTALK_REDUCTION
#define FEATURE_1T2R_ARCHITECTURE_FARNEAR_REDUCTION
#define FEATURE_1T2R_NEAR_FAR_NEW_EQU
#define FEATURE_1T2R_NEAR_FAR_USING_TTL_AVG
///#define FEATURE_1T2R_NEAR_FAR_NEW_EQU_DEBUG
///#define FEATURE_1T2R_NEAR_FAR_LNR_EQU
#define FEATURE_1T2R_NEAR_FAR_MA
#define FEATURE_1T2R_NEAR_FAR_MA_NEW_AVG
#define FEATURE_1T2R_NEAR_FAR_MA_RATIODEV
///#define FEATURE_1T2R_NEAR_FAR_MA_DEBUG
///#define FEATURE_1T2R_NEAR_FAR_MA_SHOW_AVG
///#define FEATURE_1T2R_NEAR_FAR_MA_SHOW_MA
///#define FEATURE_1T2R_NEAR_FAR_MA_SHOW_SLOPE
///#define FEATURE_1T2R_NEAR_FAR_COMPEN_1ST_SHOW_AVG
#define FEATURE_MA_BORDER_4PTS_3PTS_OVERLAP
///#define FEATURE_1T2R_NEAR_FAR_DEV_COMPEN
#define FEATURE_1T2R_NEAR_FAR_DEV_COMPEN_2ND
#define FEATURE_1T2R_NEAR_FAR_DEV_COMPEN_2ND_BACK_COMPEN_1ST
#define FEATURE_1T2R_NEAR_FAR_DEV_COMPEN_2ND_REV_DIR
#define FEATURE_1T2R_NEAR_FAR_DEV_COMPEN_2ND_ACCURACY_MID_AREA_CORRECT
#define FEATURE_1T2R_NEAR_FAR_DEV_COMPEN_2ND_ACCURACY_MID_AREA_CORRECT_SUBROUTINE

#define FEATURE_1T2R_NO_EDGE
#endif

//#define FEATURE_DEBUG_1T2R_ARCHITECTURE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 73. SRAM READ WRITE
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_SRAM_READ_WRITE
// #define FEATURE_SRAM_READ_WRITE_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 74. I2C command : F7 Calibration
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_I2C_CMD_F7_ENABLE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 75. WDT enable command : F8 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_I2C_CMD_F8_ENABLE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 76. Device Name command : FB 
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_I2C_CMD_FB_DEVICE_NAME

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 77. Finger Up Report IIR
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_IIR_FINGER_UP
//#define FEATURE_IIR_FINGER_UP_DEBUG
#define FEATURE_IIR_FINGER_UP_FIX_WEIGHTING

#define FEATURE_BORDER_AREA_DOUBLE            ///for IIR debounce up

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 78. ZET7100 Debug Mode
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_ZET7100_DEBUG_MODE

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 79. Sine Table from Dataflash ROM Table or from Firmware Dynamic Gen.
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_SINEGEN_WITH_ROM

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 80. Noise Rejection Fuction with ToneB Dummy Scan, Function actived when single tone work only.
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_NOISE_REJECTION

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 81. PN AD equalizer
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_PN_AD_EQUALIZER

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 82. Finger enhancement for floating
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_FLOATING_FINGER_ENHANCE
//#define FEATURE_FLOATING_FINGER_ENHANCE_DEBUG

//#define FEATURE_FLOATING_FINGER_ENHANCE_MASK_BY_WATER

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 83. Force Touch Application
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#ifdef FEATURE_FORCE_TOUCH
#define FEATURE_FORCE_TOUCH_SCAN
//#define FEATURE_FORCE_TOUCH_SCAN_DEBUG
#endif

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 84. Linearity Compensation
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_LINEARITY_COMPENSATION
///#define FEATURE_LINEARITY_COMPENSATION_DEBUG
#define FEATURE_LINEARITY_COMPENSATION_16TIMES
#define FEATURE_LINEARITY_COMPENSATION_16TIMES_SFT_HALF_INTERP

#define FEATURE_COORD_OFFSET_SHIFT_16TIMES
#define FEATURE_COORD_GAIN_SHIFT

#define FEATURE_COORD_ROUND_BEFORE_DIV16

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 85. Advance TP information Command
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_ADV_TP_INFOMATION

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 86. INT Pull High Control
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_INT_PULL_HIGH_CONTROL

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 87. Press Force Touch Application
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_POSITION_ALGORITHM
#ifdef FEATURE_PRESS_TOUCH

#undef FEATURE_NOISE_REJECTION

#undef FEATURE_TRACEIO_HOVER_SENSOR
#undef FEATURE_POSITION_ALGORITHM
#undef FEATURE_HEAVY_PRESS

#undef FEATURE_SENSE_DEV_PROCESS
#undef FEATURE_DRIVE_DEV_PROCESS
#undef FEATURE_DRIVE_DEV_PROC_SCHMIT_TRIGGER
#undef FEATURE_DRIVE_DEV_PROCESS_MA_FILTER
#undef FEATURE_DRIVE_DEV_PROCESS_MA_FILTER_LIMIT_TH
#undef FEATURE_SENSE_DEV_PROCESS_MA_FILTER
#undef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_AVG
#undef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_PROC_PRIORITY_CTRL
#undef FEATURE_INITIAL_DEV_PROCESS
#undef FEATURE_INITIAL_DEV_PROCESS_MA_FILTER
#undef FEATURE_INITIAL_DEV_PROCESS_BOTH
#undef FEATURE_INITIAL_DEV_PROCESS_SCALING
//#undef FEATURE_DEVPROC_INCLUDE_NEG

#undef FEATURE_COMP_MUT_WITH_INIT
#undef FEATURE_COMP_MUT_WITH_INIT_OPTION_EN

#undef FEATURE_NINE_SQUARE_ENABLE
#undef FEATURE_MERGE_CLOSE_NINESQU_FINGER

#undef FEATURE_CLUSTER_ENABLE
#undef FEATURE_MERGE_CLOSE_CLUSTER_FINGER
#undef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER

#undef FEATURE_CO_AXIS_PROCESS
#undef FEATURE_COORD_EDGE_POSITION_LOCK

#undef FEATURE_BORDER_DEV_INTERNAL

#undef FEATURE_GESTURE_WAKEUP

#undef FEATURE_FINGER_DEBOUNCE
#undef FEATURE_FINGER_UP_DEBOUNCE_ALG

#undef FEATURE_SMOOTHING_ALGORITHM

#undef FEATURE_BASE_TRACKING
#undef FEATURE_CLUSTER_MAXPEAK_CHECK
#undef FEATURE_WATER_INIT_SCAN
#undef FEATURE_CLUSTER_MERGE_LOCAL_PEAK_SORT
//#undef FEATURE_REPORT_COORDINATE_FINGERS
#endif

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 88. CUSTOMER PROTOCOL
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_CUSTOMER_PROTOCOL 
#ifdef FEATURE_CUSTOMER_PROTOCOL
// #define FEATURE_BM_NEW
#define NEW_I2C_PARSING_FLOW  //Synaptics protocol(Sony Template), else Atmel protocol(Mi3 Template)
//#define SPI_FLASH_WR_ENABLE //enable flash read write function
//#define SPI_API_TEST
//#define FORCE_SENSOR_PROTOCOL //[Maple] Not support now
#define FEATURE_GESTURE_PRO
#define FEATURE_GESTURE_PRO_DBG
#endif

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 89. Coord Force IIR in specific Area
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_COORD_FORCE_IIR_AREA
//#define FEATURE_COORD_FORCE_IIR_AREA_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 90. Hover
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#if defined(FEATURE_CLUSTER_ENABLE) && defined(FEATURE_1T2R_ARCHITECTURE)
#define FEATURE_HOVER
#define FEATURE_HOVER_DEBUG
#endif

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 91. Fake Force
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
#define FEATURE_FAKE_FORCE_TOUCH
//#define FEATURE_FAKE_FORCE_TOUCH_DEBUG

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 92. Sync scan
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define SYNC_SCAN // [Maple] Delevop use
#ifdef SYNC_SCAN
#define FEATURE_GIO_ENABLE
#endif

///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
/// 999. Raw Import
///-----------------------------------------------------------------------------------------------------------------------------------------------------------///
//#define FEATURE_RAW_DEV_IMPORT
//#define FEATURE_CLUSTER_MERGE_V61_DEBUG
//#define FEATURE_CLUSTER_MERGE_LOCAL_PEAK_DEBUG
//#define FEATURE_WATER_INIT_SCAN_DEBUG
//#define FEATURE_COORD_1ST_IIR_DEBUG

#ifdef FEATURE_RAW_DEV_IMPORT
#undef FEATURE_REAL_KEY
#undef FEATURE_KEY_DATAFORMAT_REPORT_NEW_VER
#undef FEATURE_DATA_FORMAT_KEY_MUTUAL_SCAN_ADBASE
#undef FEATURE_DATA_FORMAT_KEY_DATA
#undef FEATURE_SRAM_READ_WRITE

//#undef FEATURE_LINEARITY_COMPENSATION

#undef FEATURE_CUSTOMER_PROTOCOL
#undef FEATURE_NOISE_REJECTION
#undef FEATURE_TRACEIO_HOVER_SENSOR
#undef FEATURE_HEAVY_PRESS

#undef FEATURE_INITIAL_DEV_PROCESS_MA_FILTER
#undef FEATURE_INITIAL_DEV_PROCESS_BOTH
#undef FEATURE_INITIAL_DEV_PROCESS_SCALING
#undef FEATURE_COMP_MUT_WITH_INIT
#undef FEATURE_COMP_MUT_WITH_INIT_OPTION_EN
#undef FEATURE_CO_AXIS_PROCESS
#undef FEATURE_GESTURE_WAKEUP
#undef FEATURE_BORDER_DEV_INTERNAL

#undef FEATURE_DYNAMIC_FREQ_TRAN_MODE_ON
#undef FEATURE_HW_FREQUENCY_HOP
#undef FEATURE_BOOT_FREQUENCY_HOP
#undef FEATURE_DYNAMIC_FREQUENCY_HOP
#undef FEATURE_PN_VIOLATE_FIX
//#undef FEATURE_WATER_INIT_SCAN

#undef FEATURE_CLUSTER_MERGE_LOCAL_PEAK_SORT

#endif

//#define FEATURE_DATA_PTR_EXAMPLE

//#define FEATURE_EXTREME_CODESIZE // [Maple] code size reduce plan, need more test.
#ifdef FEATURE_EXTREME_CODESIZE

#undef FEATURE_INIT_ISR_SCAN
#undef FEATURE_INIT_SCAN							
#undef FEATURE_DATA_FORMAT_INIT_SCAN_ADBASE
#undef FEATURE_DATA_FORMAT_INIT_SCAN_DEV 
#undef FEATURE_PALM_DETECT
#undef FEATURE_COMP_MUT_WITH_INIT
#undef FEATURE_COMP_MUT_WITH_INIT_OPTION_EN

#undef FEATURE_COOR_COMP
#undef FEATURE_AXIS_DEV_RATIO_ALG
#undef FEATURE_NOISE_REJECTION
#endif

//#define FEATURE_EXTREME_CODESIZE2
#ifdef FEATURE_EXTREME_CODESIZE2
#undef FEATURE_REAL_KEY
#undef FEATURE_KEY_DATAFORMAT_REPORT_NEW_VER  
#undef FEATURE_DATA_FORMAT_KEY_MUTUAL_SCAN_ADBASE          

#undef FEATURE_CO_AXIS_PROCESS

#undef FEATURE_SRAM_READ_WRITE
#undef FEATURE_BORDER_DEV_INTERNAL

#undef FEATURE_DYNAMIC_FREQ_TRAN_MODE_ON
#undef FEATURE_DYNAMIC_FREQUENCY_HOP
#undef FEATURE_PN_VIOLATE_FIX

#undef FEATURE_CLUSTER_MERGE_LOCAL_PEAK_SORT
#endif

#endif ///< __VENDER_H__
