/**
 * @file TypeDef.h
 *
 *  TypeDef.h define variable type
 *
 *
 * @version $Revision: 72 $
 * @author JLJuang <JL.Juang@zeitecsemi.com>
 * @note Copyright (c) 2010, Zeitec Semiconductor Ltd., all rights reserved.
 * @note
*/

#ifndef __TYPEDEF_H__
#define __TYPEDEF_H__
/// =============================================================///
///  0. IC Setup 
/// =============================================================///
#ifdef FEATURE_RAW_DEV_IMPORT
#define PAD_CUT 				     (20)
#else
#define PAD_CUT 				     (0)
#endif

#include "ZET7100_Region.h"
#define PAD_MAX_NUM 				     (80-PAD_CUT)
#ifdef FEATURE_CUSTOMER_PROTOCOL 
#define CHANNEL_MAX_NUM 			(32-PAD_CUT) 	// (52-PAD_CUT)  // the Max LCM Ratio = 16:10 => 80*16/(10+16)=50; + 2 dummy
#else
#define CHANNEL_MAX_NUM 			(52-PAD_CUT)  // the Max LCM Ratio = 16:10 => 80*16/(10+16)=50; + 2 dummy
#endif

#define MAX_DRIVE_TRACE_NUM      (CHANNEL_MAX_NUM)
#define MAX_SENSE_TRACE_NUM      (CHANNEL_MAX_NUM)

#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH
#define MAX_PN_DRIVE_ROUND_NUM   (CHANNEL_MAX_NUM) 
#ifdef FEATURE_CUSTOMER_PROTOCOL 
#define MAX_DEV_ARRAY_SIZE  1024 //34*34
#define MAX_BASE_ARRAY_SIZE 1024 //32*32
#else // FEATURE_CUSTOMER_PROTOCOL
#define MAX_DEV_ARRAY_SIZE       ((PAD_MAX_NUM/2)+2	)*((PAD_MAX_NUM/2)+2	)
#define MAX_BASE_ARRAY_SIZE      ((PAD_MAX_NUM/2)	 	)*((PAD_MAX_NUM/2)		)
#endif // FEATURE_CUSTOMER_PROTOCOL
#define FORCE_BASE_ARRAY_SIZE     0
	#else
#define MAX_PN_DRIVE_ROUND_NUM   (CHANNEL_MAX_NUM/3)+1
#define MAX_DEV_ARRAY_SIZE       ((PAD_MAX_NUM/2)+2	)*((PAD_MAX_NUM/2)+2	)/3 ///< for ForceTouch Application , memory shrink to max = 40x20
#define MAX_BASE_ARRAY_SIZE      ((PAD_MAX_NUM/2)	 	)*((PAD_MAX_NUM/2)		)/3 ///< for ForceTouch Application , memory shrink to max = 40x20
#define FORCE_BASE_ARRAY_SIZE     MAX_BASE_ARRAY_SIZE
	#endif
#else // FEATURE_FORCE_TOUCH_SCAN
#define MAX_PN_DRIVE_ROUND_NUM   (CHANNEL_MAX_NUM) 
#ifdef FEATURE_CUSTOMER_PROTOCOL 
#define MAX_DEV_ARRAY_SIZE  1024 //34*34
#define MAX_BASE_ARRAY_SIZE 1024 //32*32
#else // FEATURE_CUSTOMER_PROTOCOL
#define MAX_DEV_ARRAY_SIZE       ((PAD_MAX_NUM/2)+2	)*((PAD_MAX_NUM/2)+2	)
#define MAX_BASE_ARRAY_SIZE      ((PAD_MAX_NUM/2)	 	)*((PAD_MAX_NUM/2)		)
#endif // FEATURE_CUSTOMER_PROTOCOL
#define FORCE_BASE_ARRAY_SIZE     0

#endif // FEATURE_FORCE_TOUCH_SCAN

#define AD_MAX_NUM               (16)
#define MAX_TRACE_NUM            (MAX_DRIVE_TRACE_NUM)
#define PN_MAX_NUM               (21)
#define PN_TONE_NUM              (2)
#define TRUM_OUT_NUM 	           (6)

#define KEY_MAX_NUM              (8)
#define KEY_AD_ROUND             (1)
#define FINGER_MAX							 (11)       ///< Max Finger Number for algorithm
#define FINGER_MAX_REPORT				 (10)       ///< Max Finger Number for algorithm
#define LOCAL_CLUSTER_FINGER_MAX (4)        ///< Max Finger Number for 1 cluster

#define MAX_RXSINE_TABLE_NUM		 (224)
#define MAX_RXCOEF_TABLE_NUM		 (416)
#define MAX_TXSINE_TABLE_NUM		 (1632)

///-------------------------------------------------------------------------------///
/// Freq Hopping
///-------------------------------------------------------------------------------///
#define FREQ_HOP_SET_NUM  (32)

/// =============================================================///
///  1. General type definition
/// =============================================================///
/// DWORD
typedef unsigned long        DWORD;
/// WORD
typedef unsigned short       WORD;
/// BYTE
typedef unsigned char        BOOL;
/// BYTE
typedef unsigned char        BYTE;
/// Signed byte
typedef char                 SBYTE;
/// U4
typedef unsigned long        U4;
/// U2
typedef unsigned short       U2;
/// U1
typedef unsigned char        U1;
/// I2
typedef short                I2;

typedef  long                I4;

typedef unsigned long long   QWORD;

/// =============================================================///
/// 2. Define the data flash class and sub-class
/// =============================================================///
#include "DataFlash.h"

/// Region setup 

#define MAX_GENBUF_NUM           (128)
#define MAX_GENBUF1_NUM          (128)

#define HALF_MAX_SENSE_TRACE_NUM      (MAX_SENSE_TRACE_NUM>>1)
#define HALF_MAX_DRIVE_TRACE_NUM      (MAX_DRIVE_TRACE_NUM>>1)
/// =============================================================///
/// Dev register
/// =============================================================///
typedef struct PACK RegTrnumSt
{
	int Channel[TRUM_OUT_NUM];
}RegTrnumType;
/// =============================================================///
/// Dev register
/// =============================================================///
typedef struct PACK RegDevSt
{
  BYTE bSignedDev;  
  BYTE bDev;
}RegDevType;

/// =============================================================///
/// Finger Point Type
/// =============================================================///
typedef struct PointStruct
{
  I2  x;
  I2  y;
}PointType;

/// =============================================================///
/// Finger Point Type (32 bits)
/// =============================================================///
#ifdef FEATURE_IIR_FILTER_SMOOTHING_SCALING
typedef struct Point32Struct
{
  U4  x;
  U4  y;
}Point32Type;
typedef struct Point16Struct
{
  U2  x;
  U2  y;
}Point16Type;
#endif

/// =============================================================///
/// Force Finger Point Type
/// =============================================================///
typedef struct AdvPointStruct
{
  I2  x;
  I2  y;
	#ifdef FEATURE_FORCE_TOUCH_SCAN
	BYTE  z;
	#endif
}AdvPointType;


/// =============================================================///
/// Finger Location Type
/// =============================================================///
typedef struct LocationStruct
{
  BYTE i;
  BYTE j;
}LocationType;

typedef struct LocalPeakInfoStruct
{
  BYTE i;
  BYTE j;
	#ifdef FEATURE_CLUSTER_MERGE_LOCAL_PEAK_SORT
	short sPeakDev;
	#endif
}LocalPeakInfoType;


#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
/// =============================================================///
/// Location Limit Type
/// =============================================================///
typedef struct ClusterRangeStruct
{
  SBYTE LEdge;
  SBYTE HEdge;
}ClusterRangeType;

/// =============================================================///
/// Point Relative Location Shift
/// =============================================================///
typedef struct PointShiftStruct
{
  short sDeltaX;
  short sDeltaY;
}PointShiftType;

/// =============================================================///
/// Eight Way
/// =============================================================///
typedef struct EightWayDataStruct
{
  SBYTE  sbi;	
  SBYTE  sbj;		
}EightWayDataType;
#endif

/// =============================================================///
/// AD BASE Data for Mutual Scan
/// =============================================================///
typedef struct ADBaseDataSt
{
  WORD AdBaseAlloc[MAX_BASE_ARRAY_SIZE + FORCE_BASE_ARRAY_SIZE];
}ADBaseDataType;


/// =============================================================///
/// AD BASE Data for Init Scan
/// =============================================================///
#define INIT_SCAN_ADBASE_TRACE_NUM ((MAX_DRIVE_TRACE_NUM + 1))
typedef struct InitScanDriveAdBaseSt
{
  WORD AdBaseInit[INIT_SCAN_ADBASE_TRACE_NUM];  
}InitScanDriveAdBaseType;
  
/// =============================================================///
/// For DEV BASE Data
/// =============================================================///
typedef struct InitScanDriveDevDataSt
{
  short sDev[MAX_TRACE_NUM + 2];       ///< Unsigned dev Raw data  
  short sDevAlg[MAX_TRACE_NUM + 2];
}InitScanDriveDevDataType;

/// =============================================================///
/// For Init Scan Drive Axis Drive and Sense Axise Sense 
/// =============================================================///
typedef struct InitScanSenseAdBaseSt
{
  WORD AdBaseInit[INIT_SCAN_ADBASE_TRACE_NUM];
}InitScanSenseAdBaseType;

typedef struct InitScanSenseDevDataSt
{
	short sDev[MAX_TRACE_NUM + 2];
	short sDevAlg[MAX_TRACE_NUM + 2];
}InitScanSenseDevDataType;	

typedef struct InitScanHoverDevDataSt
{
	BYTE bDev[MAX_TRACE_NUM + 2];
}InitScanHoverDevDataType;

/// =============================================================///
/// For Mutual Scan Dev Data
/// =============================================================///
typedef struct MutualScanDevDataSt
{
  BYTE bFound[MAX_DRIVE_TRACE_NUM + 2];
  short sDevAlloc[MAX_DEV_ARRAY_SIZE];       ///< Raw data
  short *sDev[MAX_DRIVE_TRACE_NUM + 2];
  short *sRawDev[MAX_DRIVE_TRACE_NUM + 2];  
#ifdef FEATURE_MUTUAL_SCAN_DEV_DETECT_HEAVY_PRESS
	BYTE bHeavyPressIndexByMutual;
#endif ///< for FEATURE_MUTUAL_SCAN_DEV_DETECT_HEAVY_PRESS
	BYTE bSenFound[MAX_TRACE_NUM+2];
}MutualScanDevDataType;

/// =============================================================///
/// For Key Data
/// =============================================================///
#ifdef FEATURE_REAL_KEY 
typedef struct KeyCtrlSt
{
  WORD wKeyAdBase[KEY_MAX_NUM]; 
	BYTE bKeyDevData[KEY_MAX_NUM];
	BYTE bKeyValidByte; 
}KeyCtrlType;
#endif

#ifdef FEATURE_VIRTUAL_KEY 
typedef struct KeyCtrlSt
{
  WORD wKeyAdBase[KEY_MAX_NUM]; 
	BYTE bKeyDevData[KEY_MAX_NUM];
	BYTE bKeyValidByte; 
}KeyCtrlType;
#endif
/// =============================================================///
/// For Finger Search Data
/// =============================================================///
#ifdef FEATURE_NINE_SQUARE_ENABLE
typedef struct SearchFingerRecordStruct
{
  BYTE bFingerI;	
	BYTE bFingerJ;
  BYTE bFingerRightDownI;	
	BYTE bFingerRightDownJ;
	#ifdef FEATURE_ADV_NINE_SQAURE
	BYTE bSize;
	#endif
	#ifdef FEATURE_SEARCH_FINGER_TOUCH_FLAG
	BYTE bTouch;
	#endif
	I2	 iCoordinateX;
	I2	 iCoordinateY;
	#ifdef FEATURE_FINGER_SCHMIT_TRIGGER
	WORD wFingerFoundWeight;
	//WORD wFingerWeightSchmit;
	#endif	
}SearchFingerRecordType;
#endif ///< for FEATURE_NINE_SQUARE_ENABLE

#ifdef FEATURE_CLUSTER_ENABLE   
typedef struct ClusterStructrue
{
	#ifdef FEATURE_MERGE_CLOSE_CLUSTER_FINGER
	PointType ptRawCoordinate;
	#endif ///< for FEATURE_MERGE_CLOSE_CLUSTER_FINGER
	BYTE bClusterStatus;
	BYTE bClusterID;
	BYTE bClusterSize;
	BYTE bClusterLeft;
	BYTE bClusterRight;
	BYTE bClusterDown;
	BYTE bClusterUp;
	WORD wClusterWeight;
	#ifdef FEATURE_CLUSTER_LIMIT_LOCAL_PEAKTH
	short wClusterMaxPeakDev;
	#endif		
	U4   dwClusterWeightXU;
	U4   dwClusterWeightYU;
} ClusterStructrueType;
#ifdef FEATURE_MERGE_CLOSE_CLUSTER_FINGER
typedef struct ClusterTrackCoordinateStruct
{
	PointType ptSearchTrackCoord;	
	
	BYTE bStatus;
	BYTE bRootClusterID;			///< the source of cluster data structure ID

	///BYTE bStatus1;

	#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
	BYTE bClusterSize;
	
	BYTE bInitClusterSize;
	BYTE bMergeDebounce;
	BYTE bExistDebounce;
	//BYTE bPeakCnts;
	BYTE bFakeDivideDebounce;
	PointShiftType SubPointShift[4];
	#endif

	#ifdef FEATURE_CLUSTER_MERGE_V61
	BYTE bStateMode;
	BYTE bInitMulPeakCnt; ///< initial 3 round Multi-Peak cnt
		#ifdef FEATURE_CLUSTER_MERGE_V61_DEBUG	
		BYTE bProjectPeak;
		BYTE bClusterSizeChangeRatio;
		BYTE bMergeProjectPeak;
		BYTE bStateRecord;
		#endif
	#endif
	
	#ifdef FEATURE_CLUSTER_PEAK_MERGE_DEUG
	WORD wClusterPeakAvgDebug;
	WORD wMergeTHDebug;
	WORD wVellyAvgDevDebug;	
	WORD wSizeChangeDebug;	
	#endif
}ClusterTrackCoordinateType;

#endif
#endif


/// =============================================================///
/// For Coordinate Point data
/// =============================================================///
#ifdef FEATURE_KALMAN_FILTER_SMOOTHING
typedef struct KFilterDataSt
{
  long mp;
  I2 preDataX;
  I2 preDataY;    
} KFilterDataType;
#endif ///< for FEATURE_KALMAN_FILTER_SMOOTHING

#if defined(FEATURE_MERGE_CLOSE_CLUSTER_FINGER) || defined(FEATURE_MERGE_CLOSE_NINESQU_FINGER)
typedef struct MergeIDCombinationStruct
{
	BYTE bStstus;	
	BYTE bDebounceCnt;	
}MergeIDCombinationType;
#endif

#ifdef FEATURE_MERGE_CLOSE_NINESQU_FINGER
typedef struct TrackCoordinateStruct
{
	BYTE bStatus;
	BYTE bMergeDebounce;
	PointType ptSearchTrackCoord;
	AdvPointType ptReportTrackCoord;
	LocationType XYStart;
	LocationType XYEnd;
}TrackCoordinateType;
#endif 

typedef struct FingerCoordinateRecordStruct
{
		#ifdef FEATURE_TRACK_PREDICT_COORD
		WORD	wPredictedCoordinateX;
		WORD	wPredictedCoordinateY;
		#endif ///< for FEATURE_TRACK_PREDICT_COORD

    #ifdef FEATURE_IIR_FILTER_SMOOTHING_SCALING
    WORD  wLsb16LastPtX;
    WORD  wLsb16LastPtY;
    #endif
		
		WORD	wLastDistance[REC_DISTANECE_LEN];
		BYTE	bDistRecIdx;
		#ifdef FEATURE_DEBUG_AVOID_TAP_LINE
		WORD	wAccelerate;
		#endif
		BYTE	bFingerDebounce;				 ///< The finger shall keep visible 	for #N	frames then it would be treated as a	finger click (Finger down )
		BYTE	bFingerUpState; 				 ///< The finger shall keep invisible for #N	frame then it would be treated as a  finger leave (Finger up )	
		BYTE	bFingerDown;
	
		BYTE	bIIRWeight;
		
		WORD wFingerStatus;
	
		///---------------------------------------------///
		///  Points queue
		///---------------------------------------------/// 
		BYTE cRawPointIdx;
		BYTE cExePointIdx;
		BYTE cPointCnt;  
		AdvPointType ptCoordinate;  
		PointType ptExePoints[EXE_POINT_LEN]; 	 
		PointType ptRawPoints[RAW_POINT_LEN];	
	#ifdef FEATURE_COORD_EDGE_POSITION_LOCK
		PointType ptBorderLockedCoord;  
	#endif ///< for FEATURE_COORD_EDGE_POSITION_LOCK		
	
	#ifdef FEATURE_KALMAN_FILTER_SMOOTHING
		KFilterDataType kData;
	#endif ///< for FEATURE_KALMAN_FILTER_SMOOTHING
}FingerCoordinateRecordType;

/// =============================================================///
/// Dynamic Mode
/// =============================================================///
typedef struct PACK PointDataStruct
{
  BYTE bXYHighByte;
  BYTE bXLowByte;
  BYTE bYLowByte;    
  BYTE bZLowByte;  
}PointDataType;

typedef struct PACK DynamicDataStruct
{
  BYTE bPacketId;
  WORD wValid;
  PointDataType point[I2C_FINGER_BUFFER_NUM];
  BYTE bKeyStatus;
}DynamicDataType;

/// =============================================================///
/// Focal Data Type Mode
/// =============================================================///
#define MAX_FOCAL_FINGER_NUM        (5)

typedef struct FocalPointDataStruct
{
  BYTE bXHighByte;
  BYTE bXLowByte;
  BYTE bYHighByte;
  BYTE bYLowByte;    
  WORD wDummy;    
}FocalPointDataType;

typedef struct FocalDataStruct
{
  BYTE bDeviceMode;
  BYTE bGestId;
  BYTE bTdStatus;
  FocalPointDataType point[MAX_FOCAL_FINGER_NUM];
}FocalDataType;

/// =============================================================///
/// Virtual Key
/// =============================================================///
typedef struct VirtualKeyStruct
{
  WORD x; ///< Left of key
  WORD y; ///< Top of key
  BYTE w; ///< width of key;  
  BYTE h; ///< height of key;  
}VirtualKeyType;

/// =============================================================///
/// Collect Dev
/// =============================================================///
typedef struct PACK DevCollectSetupStruct
{
  BYTE bTotal;
  BYTE bPow;  
  //BYTE bNoCut;
}DevCollectSetupType;

/// =============================================================///
/// Hopping R/C Trim setup
/// =============================================================///
#ifdef FEATURE_HW_FREQUENCY_HOP
typedef struct HopDataStruct
{
	WORD wRawADBase;
	WORD wADDeltaAccumulator;
	WORD wADDeltaSumation;
	WORD wADDeltaHistory[HISTORY_SAVE_NUM];
	BYTE bToneA;	
} HopDataType;

typedef struct HopSortDataStruct
{
	BYTE bHopID;
	WORD wHopData;
} HopSortDataType;



#endif
#ifdef FEATURE_TRIM_FREQ_HOP
typedef struct HopDataStruct
{
	WORD wRawAD[AD_MAX_NUM];
	WORD wADDeltaAccumulator;
	WORD wADDeltaSumation;	
	#ifdef FEATURE_DYNAMIC_FREQ_HOP
	WORD wADDeltaHistory[DYNAMIC_HOP_HISTORY_SAVE_ROUND];
	#endif ///< for FEATURE_DYNAMIC_FREQ_HOP
	#ifdef FEATURE_DEBUG_TRIM_FREQ_HOP
	WORD wDebugAD[AD_MAX_NUM];
	#endif
} HopDataType;

typedef struct HopSortDataStruct
{
	BYTE bHopID;
	WORD wHopData;

} HopSortDataType;
#endif ///< for FEATURE_TRIM_FREQ_HOP

#ifdef FEATURE_DYNAMIC_FREQ_HOP
typedef struct DynamicFrequencySet
{
	WORD wADOPT4;
	WORD wTXOPT3;

} DynamicFrequencySetDataType;
#endif ///< for FEATURE_DYNAMIC_FREQ_HOP

/// =============================================================///
/// Region PN Scan Data strucurt for ZET7100
/// =============================================================///
typedef struct PACK SubRegionDataStruct
{
  BYTE bRegionTraceNum; 					///< Trace numbers in a region
  BYTE bRegionTrace[PN_MAX_NUM]; 	///< Trace IDs
  BYTE bRow[PN_MAX_NUM]; 					///< Trace row position 
  #ifdef FEATURE_PN_VIOLATE_FIX 
  DWORD dwEnPad; 									///< Trace row is 1:enable/0:disable
  #endif
  DWORD dwTrumReg[TRUM_OUT_NUM]; 						///< TRNUM_OUT0 ~ TRNUM_OUT5

}SubRegionDataType;

typedef struct PACK RegionDataStruct
{
  BYTE bToneNum; ///< Tone numbers in this Round
  SubRegionDataType ToneData[PN_TONE_NUM];
  
}RegionDataType;

typedef struct PACK ProtocoalDataStruct
{
  WORD Data; ///< 
}ProtocoalDataType;

/// =============================================================///
/// GPIO Register define for ZET6275
/// =============================================================///
typedef struct GpioSt
{
  unsigned bit0:1;
  unsigned bit1:1;
  unsigned bit2:1;
  unsigned bit3:1;
  unsigned bit4:1;
  unsigned bit5:1;
  unsigned bit6:1;
  unsigned bit7:1;
  unsigned unsued:24;
}GpioType;

/// ============================================================================================================================///
/// ZetVar
/// ============================================================================================================================///
#define MAX_RX_BUF_LEN    20 //  (10)
typedef struct GlobalVarSt
{
  ///----------------------------------------------------------------------------------------------------------------------------///
  /// I:  Data Buffers
  ///----------------------------------------------------------------------------------------------------------------------------///
  ADBaseDataType  MutualScanAdBase;                               /// XDATA[500]
  InitScanDriveAdBaseType  InitScanDriveAdBase;                   /// EVEN: XDATA[980], ODD: XDATA[9B0] 
  InitScanDriveDevDataType   InitScanDriveDevData;                /// XDATA[9E0]  

  MutualScanDevDataType MutualScanDevData[2];
	
	#ifdef FEATURE_PROCESS_COORDINATE_WITH_RAW_DATA
  short MutualScanRawDevData[MAX_DEV_ARRAY_SIZE];
	#endif ///< for FEATURE_PROCESS_COORDINATE_WITH_RAW_DATA

	#ifdef FEATURE_FORCE_TOUCH_SCAN

		#ifdef FEATURE_FAKE_FORCE_TOUCH

		#else
	MutualScanDevDataType ForceScanDevData[2];
	short ForceMutualScanRawDevData[MAX_DEV_ARRAY_SIZE];
  WORD *ForceAdBaseRound[MAX_TRACE_NUM]; 
	//ADBaseDataType  ForceScanAdBase;     
	short ForceScanRawDevData[MAX_DEV_ARRAY_SIZE];
		#endif
	#endif
	
  WORD *AdBaseRound[MAX_TRACE_NUM];  
	///< XDATA[0x500]
	#ifdef FEATURE_PNCODE_NOISE_DETECT
  WORD AdBaseRoundForNoiseDetect[MAX_TRACE_NUM];           ///< For PN code noise detect, The Value maybe same the each ADC Offset value
  #endif ///< for FEATURE_PNCODE_NOISE_DETECT

	#ifdef FEATURE_NINE_SQUARE_ENABLE
	SearchFingerRecordType SearchFingerRecord[FINGER_MAX];          ///< XDATA[0x1118] 
	#endif
	
	#ifdef FEATURE_CLUSTER_ENABLE  
	//BYTE ClusterIDData[(MAX_TRACE_NUM +2)*(CLUSTER_ID_ARRAY_NUM)];
	BYTE ClusterIDArray[CLUSTER_ID_ARRAY_NUM][(MAX_TRACE_NUM +2)];
	ClusterStructrueType ClusterData[MAX_CLUSTER_SUPPORT];	
	DWORD ClusterSchmitSwitch[MAX_TRACE_NUM];
	
	#ifdef FEATURE_MUT_PARTIAL_REK
	DWORD BaseUpdateControl[MAX_TRACE_NUM];
	#endif
	#ifdef FEATURE_MUT_PARTIAL_CROSS_SET
	DWORD BaseUpdateCross[MAX_TRACE_NUM];
	#endif

	#ifdef FEATURE_CLUSTER_DEBUG_ENABLE
	short ClusterMatrixData[(MAX_TRACE_NUM +2)*(MAX_SENSE_TRACE_NUM +2)];
	short *ClusterMatrix[MAX_TRACE_NUM +2];
	#endif


	#ifdef FEATURE_CLUSTER_MERGE_V61_DEBUG	
	short ClusterMatrixData[(MAX_TRACE_NUM +2)*(MAX_SENSE_TRACE_NUM +2)];
	short *ClusterMatrix[MAX_TRACE_NUM +2];
	#endif


	#ifdef FEATURE_MERGE_CLOSE_CLUSTER_FINGER
	
	#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
	AdvPointType 						RemainCoordinateRecord[FINGER_MAX_REPORT];
	LocalPeakInfoType				ClusterPeakLocation[FINGER_MAX_REPORT]; ///< 1 Cluster max support 10 peak inside
	#endif
	ClusterTrackCoordinateType  TrackCoordinateRecord[FINGER_MAX_REPORT];	
	#endif	
	#endif ///< for FEATURE_CLUSTER_ENABLE

	#ifdef FEATURE_ADV_NINE_SQAURE
	BYTE NineSquClusterIDData[(MAX_TRACE_NUM +2)*(CLUSTER_ID_ARRAY_NUM)];
	BYTE *NineSquClusterIDArray[CLUSTER_ID_ARRAY_NUM];
	#endif ///< for FEATURE_ADV_NINE_SQAURE
	
	FingerCoordinateRecordType FingerCoordinateRecord[FINGER_MAX_REPORT];  ///< XDATA[0x119C]

	#ifdef FEATURE_MERGE_CLOSE_NINESQU_FINGER
	TrackCoordinateType  TrackCoordinateRecord[FINGER_MAX_REPORT];  
	MergeIDCombinationType MergeIDStatus[FINGER_10_COMBINATION_NUMBER];  ///< 45 = C(10,2) = 10!/8!*2!
	#endif ///< for FEATURE_MERGE_CLOSE_NINESQU_FINGER

	//----------------------------//
	// HW Frequency Hop data stucture
	//----------------------------//	
	#ifdef FEATURE_TRIM_FREQ_HOP
	HopDataType	HopData[FREQ_HOP_SET_NUM];
	HopSortDataType	HopSortData[FREQ_HOP_SORT_NUM];	
	#endif ///< for FEATURE_TRIM_FREQ_HOP
	
	#ifdef FEATURE_DYNAMIC_FREQ_HOP
	DynamicFrequencySetDataType DynamicADTXSet[DYNAMIC_FREQ_SET_NUM];
	WORD DynamicHopCurrentRawAD[AD_MAX_NUM];     
	#endif ///< for FEATURE_DYNAMIC_FREQ_HOP

	#ifdef FEATURE_HW_FREQUENCY_HOP
	HopDataType HopData[FREQ_HOP_SET_NUM];
	HopSortDataType	HopSortData[FREQ_HOP_SORT_NUM];	
	#endif

	#ifdef FEATURE_BASE_AVG_REMIDER_RESUME
	BYTE *BaseRemider[MAX_TRACE_NUM];
	#endif

	#ifdef FEATURE_CLUSTER_MERGE_V61
	short ProjectDev[MAX_TRACE_NUM];
	#endif
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///   Init Scan Test Buffer
  ///----------------------------------------------------------------------------------------------------------------------------///
  InitScanSenseAdBaseType   InitScanSenseAdBase;
  InitScanSenseDevDataType  InitScanSenseDevData; 
	#ifdef FEATURE_TOUCH_HOVER_SENSOR
  InitScanSenseAdBaseType   InitScanHoverAdBase;
  InitScanSenseDevDataType  InitScanHoverDevData;
	#endif ///< for FEATURE_TOUCH_HOVER_SENSOR

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///   B2 Command Buffer
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE bB2Buf[B2_BUF_LEN];  
	
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///   f9 Command Buffer
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE bF9Buf[F9_BUF_LEN];  

	///----------------------------------------------------------------------------------------------------------------------------///
  ///   fb Command Buffer
  ///----------------------------------------------------------------------------------------------------------------------------///
  #ifdef FEATURE_I2C_CMD_FB_DEVICE_NAME
	BYTE bFBBuf[FB_BUF_LEN];  
	#endif
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///  II:  Control Values 
  ///----------------------------------------------------------------------------------------------------------------------------///

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    1. Sense Axis Save Control
  ///----------------------------------------------------------------------------------------------------------------------------///

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    2. Drive Axis Save Control
  ///----------------------------------------------------------------------------------------------------------------------------///	
	
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    3. System  Mode
  ///----------------------------------------------------------------------------------------------------------------------------///
  WORD wSysMode;
  WORD wSysMode2;  
  WORD wTestMode;
  WORD wAlgoStatus;
	WORD wAlgoStatus2;
	BYTE bBaseTrackingTimer;
	BYTE bCalibrationCtrl;
	char *CompileDeviceName;
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    4. Maximum Trace Numbers
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE bSenseMax;
  BYTE bDriveMax;
	BYTE bDriveMaxAlg;
	BYTE bSenseMaxAlg;
	
	WORD wDriveAxisInterpolation16;
	WORD wSenseAxisInterpolation16;
	
	#ifdef FEATURE_FORCE_TOUCH_SCAN
		#ifdef FEATURE_FAKE_FORCE_TOUCH
	
		#else
  BYTE bForceSenseMax;
  BYTE bForceDriveMax;
		#endif
	#endif
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    5:  Cut DEV
  ///----------------------------------------------------------------------------------------------------------------------------///
  //WORD wCutDevRegionScan;
  //WORD wCutDevInitScan;
  
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    6. Scan Control Methods 
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE bScanMethod;
  BYTE bScanADCtrl;

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    7. Mutual Scan Control Queue
  ///----------------------------------------------------------------------------------------------------------------------------///
  

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    8: SRAM Access Control
  ///----------------------------------------------------------------------------------------------------------------------------///
  U4 dwSramAddr;
  
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    9: I2C 
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE *pI2CData;  
  BYTE bI2CCmd;
  BYTE bI2CRxBuf[MAX_RX_BUF_LEN];     ///< Current Received TP command

  BYTE bI2cRxLen;                     ///< Data length which is needed to be transferred
  WORD wI2cTxLen;                     ///< Data length which is needed to be transferred

	BYTE bI2cIntLowTimeOutDefault;      ///< INT low wait timing Counter

  WORD wI2cTxIdx;                     ///< I2C TX Buffer Idx

  WORD wI2cRxIdx;                     ///< I2C RX Buffer Idx

  BYTE bI2cStatus;                    ///< I2C Status

  BYTE bIntLowTimeout;                ///< for the int low timeout protection

	BYTE bVenCmd;                       ///< Command Mode 

	BYTE bI2cByteNumber;                ///< I2C Dynamic Byte Nuumber

	BYTE bI2cData;                   	 ///< I2C Data
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    10. Key Control
  ///----------------------------------------------------------------------------------------------------------------------------///
  #ifdef FEATURE_REAL_KEY 
  KeyCtrlType KeyCtrl;
  BYTE bKeyMax;
	BYTE bKeyDebounce[KEY_MAX_NUM];
	BYTE bKeyReleaseCnt;
	BYTE bKeyLastStatus;
	BYTE bKeyLockStatus;
	BYTE bKeyLockRelease;	
	#endif ///< for FEATURE_REAL_KEY
#ifdef FEATURE_VIRTUAL_KEY 
KeyCtrlType KeyCtrl;
BYTE bKeyMax;
 BYTE bKeyDebounce[KEY_MAX_NUM];
 BYTE bKeyReleaseCnt;
 BYTE bKeyLastStatus;
 BYTE bKeyLockStatus;
 BYTE bKeyLockRelease; 


#endif ///< for FEATURE_VIRTUAL_KEY
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    11. Dynamic Data
  ///----------------------------------------------------------------------------------------------------------------------------///
  DynamicDataType dynamicData[REPORT_BUFFER_NUM];

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    12. Dynamic Data
  ///----------------------------------------------------------------------------------------------------------------------------///

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    13. Data Transfer
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE *pCurReportData;
  BYTE pCurReportIdx;
  
	BYTE bDataIn;                       ///< 1 : threre is at least one finger or one key down ; 0 : No key or finger done ;  2 : One Finger Up Reporting
  BYTE bTranType;                     ///< Data Format Type      

  BYTE bFingerUpRpCnt;                ///< Finger up report count   

  BYTE bMTKFormatEnable;              ///< N-byte packet transfer           
  BYTE bMTKPacketSize;                ///< N-byte packet transfer  (Default: 8 byte) 
	#ifdef FEATURE_RING_BUFFER
	BYTE bAlgRingBufCnt;              ///< Ring buffer
	BYTE bRingBufFlag;	              ///< Ring buffer
	BYTE bI2CRingBufCnt;              ///< Ring buffer	
	#ifdef FEATURE_DEBUG_RING_BUFFER
	BYTE bFrameCnt;              ///< Ring buffer	
	#endif
	#endif

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    14. Algorithm Data
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE bPalmState;                    ///< 0: No Palm  >0: Palm on TP
  #ifdef FEATURE_ADV_NINE_SQAURE
	BYTE bSearchIDFound;  
	#endif
	BYTE bFingerCountsFound;
	BYTE bFingerCountsFoundLast; 
	#ifdef FEATURE_FINGER_UP_DEBOUNCE_ALG
	BYTE bFingerReportCounts;
	#endif ///< for FEATURE_FINGER_UP_DEBOUNCE_ALG

  WORD wFingerTH;                     ///< Finger search threshold for normal and charger mode
  BYTE bFingerSlop;
	BYTE bFingerVellySlop;

  /// Debounce count
  BYTE bDebounceCnt;            ///< For single finger down debounce 
  BYTE bDebounceCntTwo;         ///< For 2 fingers down debounce   
  BYTE bDebounceCntMulti;       ///< For >3 fingers down debounce 

  /// Finger up debounce count
  BYTE bFingerUpMultiDebounceCnt;            ///< For multi finger up debounce count

	/// IIR add one point
	#ifdef FEATURE_IIR_FINGER_UP
	BYTE bFingerUpEn;
	BYTE bFingerUpOneDebounceCnt;
	#endif

	BYTE bADC0Gain;
	#ifdef FEATURE_FORCE_TOUCH_SCAN
		#ifdef FEATURE_FAKE_FORCE_TOUCH

		#else
	BYTE bForceADC0Gain;	
		#endif
	#endif
	
  /// Finger weight
  WORD wFingerWeight;
	WORD wFingerSchmitWeight;
	WORD wClusterDevSchmtOff;	
	WORD wClusterDevSchmtOn;	
#ifdef FEATURE_MERGE_TWO_FINGER
	/// Merge Finger
	BYTE  bMergeStateNow;
	BYTE  bMergeStatePre;
	SBYTE sbMergeStateCounter;
	
	BYTE  bDistHugeTH;        ///< HugeTH > LongTH > SmallTH > NanoTH 
	BYTE  bDistLargeTH;       ///< LongTH
	BYTE  bDistSmallTH;       ///< SmallTH
	BYTE  bDistNanoTH;        ///< NanoTH
	
	BYTE  bMergeFingerEn;
	SBYTE sbPositiveMerge;
	SBYTE sbNegativeMerge;
#endif ///< for FEATURE_MERGE_TWO_FINGER
#ifdef FEATURE_INIT_SCAN_DEVDETECT_HEAVY_PRESS
	//BYTE bHeavyPressDetectSwitchGainHappen;
	//BYTE bHeavyPressDetectReportFingerFrozen;
	//BYTE bHeavyPressDetectReportFingerFrozenLast;	
	BYTE bHeavyPressDetectInOutCnt;	
#endif  ///< for FEATURE_INIT_SCAN_DEVDETECT_HEAVY_PRESS
#ifdef FEATURE_MERGE_DEBUG_CLOSE_FINGER
	BYTE bDebugMergeCnt;
	BYTE bDebugMergeIndex;
	WORD wReportCnts;
	BYTE bDebugMesg1[10];
	BYTE bDebugMesg2[10];
	BYTE bDebugMesg3[10];	
#endif

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    15. Virtual Key
  ///----------------------------------------------------------------------------------------------------------------------------///
#ifdef FEATURE_VIRTUAL_KEY
  VirtualKeyType const code *pVirtualKey[VIRTUAL_KEY_MAX_NUM];
  ///-------------------------------------------------------------///
  /// BIT#0 : 1 --> Key#0 (Search) pressed, 0 --> Key#0 released 
  /// BIT#1 : 1 --> Key#1 (Back)   pressed, 0 --> Key#1 released
  /// BIT#2 : 1 --> Key#2 (Home)   pressed, 0 --> Key#2 released
  /// BIT#3 : 1 --> Key#3 (Value)  pressed, 0 --> Key#3 released  
  ///-------------------------------------------------------------///  
  BYTE bVirtualKeyValidByte; 
	BYTE bVirtualKeyDeboucneCnt; 
  BYTE bVirtualKeyEnable;
#endif ///< for FEATURE_VIRTUAL_KEY

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    17. Re-Calibration
  ///----------------------------------------------------------------------------------------------------------------------------///
  BYTE bReCalDetNum;
	BYTE bReCalDetCnt;
	BYTE bKeyReCalDetCnt;


  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    18. Power Saving mode
  ///----------------------------------------------------------------------------------------------------------------------------///  
  BYTE bNoFingerRoundCount;

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    19. Hover
  ///----------------------------------------------------------------------------------------------------------------------------///  
  #ifdef FEATURE_TOUCH_HOVER_SENSOR 
	BYTE bHoverFingerDownInZone;
	BYTE bHoverFingerDownInScanZone;
	BYTE bHoverCheckTraceStart;
	BYTE bHoverCheckTraceEnd;	
	BYTE bHoverAxisMax;
	BYTE bHoverFingerUpDebounceCnt;
	#endif ///< for FEATURE_TOUCH_HOVER_SENSOR
	
	#if defined(FEATURE_TOUCH_HOVER_SENSOR) || defined(FEATURE_TRACEIO_HOVER_SENSOR)
	BYTE bHoverEnterCount;
  BYTE bHoverReleaseCount;
	#endif

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    20. Frequency Hopping
  ///----------------------------------------------------------------------------------------------------------------------------/// 
	#ifdef FEATURE_DYNAMIC_FREQ_HOP
	BYTE bDynamicScanCnt;
	BYTE bDynamicFreqSetCnt;
	BYTE bDynamicRoundCnt;
	BYTE bDynamicCurrentID;	
	BYTE bDynamicNewBetterID;	
	BYTE bDynamicFreqStatus;
	BYTE bDynamicCurrentIDBadCnt;
	BYTE bDynamicFreqSetNum;
	BYTE bDynamicHistoryCnt;	
	BYTE bDynamicScanNum;
	BYTE bDynamicADDivder;
	WORD wDynamicCurrentDelta;	
	#ifdef FEATURE_DEBUG_DYNAMIC_FREQ_HOP
	WORD wDynamicHopRank;
	#endif ///< for FEATURE_DEBUG_DYNAMIC_FREQ_HOP
	#endif ///< for FEATURE_DYNAMIC_FREQ_HOP

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    21. SW Dev Collect Value
  ///----------------------------------------------------------------------------------------------------------------------------/// 
#ifdef FEATURE_DEV_COLLECT  
	BYTE bSWDevCollectValue;
#endif ///< for FEATURE_DEV_COLLECT
	BYTE bCoAxisExecuteMdoe;

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    22. Trace 
  ///----------------------------------------------------------------------------------------------------------------------------/// 

	///----------------------------------------------------------------------------------------------------------------------------///
	/// 	 23. PD smooth
	///----------------------------------------------------------------------------------------------------------------------------/// 
#ifdef FEATURE_GG_FILTER_SMOOTHING
	BYTE bPDsmoothiGJ;
	BYTE bPDsmoothiGA;
	BYTE bPDsmoothiGB;
#endif ///< for FEATURE_GG_FILTER_SMOOTHING  

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    23. Region Scan
  ///----------------------------------------------------------------------------------------------------------------------------/// 
#ifdef FEATURE_REGION_SCAN
	BYTE bDriveRegionId;                   ///<
	BYTE bSenseGroupId;                   ///<
	BYTE bADStrAmpIntCnt;                   ///<
#endif ///< for FEATURE_REGION_SCAN
	BYTE bRegionScanQueueLen; 							 ///<

	///----------------------------------------------------------------------------------------------------------------------------///
	/// 	 24. Border Dynamic Comp Dev
	///----------------------------------------------------------------------------------------------------------------------------///	
#ifdef FEATURE_BORDER_DEV
	WORD wBorderDriFarWeightUpper;
	WORD wBorderDriFarWeightLower;	
	WORD wBorderSenFarWeightUpper;
	WORD wBorderSenFarWeightLower;		
#endif ///< for FEATURE_BORDER_DYNAMIC_DEV

  ///----------------------------------------------------------------------------------------------------------------------------///
  /// General purpose buffer, the two item shall be the last two buffer
  ///----------------------------------------------------------------------------------------------------------------------------///
  WORD wDevProcShmit[MAX_DRIVE_TRACE_NUM];
#ifdef FEATURE_DRIVE_DEV_PROC_SCHMIT_TRIGGER
	DWORD dwDriDevProcShmit[MAX_DRIVE_TRACE_NUM];
#endif ///< for FEATURE_DRIVE_DEV_PROC_SCHMIT_TRIGGER
 	//BYTE bGenBuf1[MAX_GENBUF1_NUM];
	BYTE bGenBuf1[(HALF_MAX_DRIVE_TRACE_NUM+2)*4*2];
	

  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    28. Power Base Tracking 
  ///----------------------------------------------------------------------------------------------------------------------------/// 
	BYTE bBaseTrackPeriod;
	#ifdef FEATURE_POWER_BASE_TRACK
	WORD wFrameCntUnStableState;
	#endif	///< for FEATURE_POWER_BASE_TRACK
	#ifdef FEATURE_REK_POWER_BASE_TRACK
	WORD wFrameCntReKUnStableState;
	#endif ///< for FEATURE_POWER_BASE_TRACK
	#ifdef FEATURE_INIT_ABNORMAL_REK
	WORD wAfterReKCnts;
	WORD wAfterReKNumMax;
	BYTE bAfterReKInitNegTimes;
	#ifdef FEATURE_DEBUG_INIT_ABNORMAL_REK
	BYTE bReKCnt1;
	BYTE bReKCnt2;
	BYTE bReKCnt3;	
	BYTE bReKCnt4;	
	#endif
	#endif ///< for FEATURE_INIT_ABNORMAL_REK
	#ifdef FEATURE_MUT_ABNORMAL_REK
	BYTE bNegFingerFoundFrameCnt;
	BYTE bNegFingerMutRekDebounce;
	#endif
  ///----------------------------------------------------------------------------------------------------------------------------///
  ///    29. Gesture 
  ///----------------------------------------------------------------------------------------------------------------------------/// 
#ifdef FEATURE_GESTURE_WAKEUP
	BYTE bGestureStatus;
	BYTE bGestureCount;	
	WORD wGestureStratCoordX;
	WORD wGestureStratCoordY;
#endif ///< for FEATURE_GESTURE_WAKEUP
#ifdef FEATURE_GESTURE_PRO
	BYTE bVector[MAX_GESTURE_MAX];
	BYTE bReportGestureId;
	BYTE bGestureId;
	BYTE bGestureStatus2;
	BYTE bGestureCount2;
	BYTE bMultiFinger;
	WORD wGestureStratCoordXEnd;
	WORD wGestureStratCoordYEnd;	
	WORD wGestureStratCoordXStart;
	WORD wGestureStratCoordYStart;
	BYTE bTimeToDoubleclick;
	BYTE bUpKey;
#endif
	///----------------------------------------------------------------------------------------------------------------------------///
 	///		30. Check Sum
	///----------------------------------------------------------------------------------------------------------------------------/// 
	#ifdef FEATURE_CHECK_SUM
	BYTE bROMCheckSum ;
	#endif 

	///----------------------------------------------------------------------------------------------------------------------------///
 	///	Finger Tracking DataBuffer
	///----------------------------------------------------------------------------------------------------------------------------/// 
	#ifdef FEATURE_ADVANCE_COORD_TRACK
	WORD wMDistData[MAX_TRACK_NUM][MAX_TRACK_NUM];
	BYTE bRowCover[MAX_TRACK_NUM];
	BYTE bColCover[MAX_TRACK_NUM];
	BYTE bMask[MAX_TRACK_NUM][MAX_TRACK_NUM];
	BYTE bRowArrayStep5[MAX_TRACK_NUM];	
	BYTE bColArrayStep5[MAX_TRACK_NUM];
	BYTE bReportFingerIdx[MAX_TRACK_NUM];
	BYTE bRow;
	BYTE bCol;
	BYTE bRowStar;
	BYTE bColStar;	
	BYTE bRowTrackNum;
	BYTE bColFoundNum;		
	BYTE bPathCnt;
	WORD wSearchFingerIsTracked;
	#endif

	///----------------------------------------------------------------------------------------------------------------------------///
 	///		31. Stack Pointer Min
	///----------------------------------------------------------------------------------------------------------------------------/// 
	#ifdef FEATURE_STACK_USED_DEBUG
	DWORD dwStackPointerMin;
	#endif ///< for FEATURE_STACK_USED_DEBUG
	
	///----------------------------------------------------------------------------------------------------------------------------///
	/// 	32. Cluster
	///----------------------------------------------------------------------------------------------------------------------------/// 
	#ifdef FEATURE_CLUSTER_ENABLE 
	#endif ///< for FEATURE_CLUSTER_ENABLE

	///----------------------------------------------------------------------------------------------------------------------------///
	/// 	33. Merge Close Finger
	///----------------------------------------------------------------------------------------------------------------------------/// 
	#if defined(FEATURE_OLD_MERGE_CLOSE_CLUSTER_FINGER) || defined(FEATURE_MERGE_CLOSE_NINESQU_FINGER)
	WORD wMergeDist;
	WORD wDividDist;	
	#endif ///< for FEATURE_MERGE_CLOSE_NINESQU_FINGER

	#ifdef FEATURE_DEBUG_MERGE_CLOSE_CLUSTER_FINGER
	WORD wDistLength;
	#endif
	///----------------------------------------------------------------------------------------------------------------------------///
	/// 	32. Initial ISR Scan
	///----------------------------------------------------------------------------------------------------------------------------/// 
	#ifdef FEATURE_INIT_ISR_SCAN
	BYTE bInitISRScanIdx;
	#endif ///<for FEATURE_INIT_ISR_SCAN

	#ifdef FEATURE_INITIAL_DEV_PROCESS_SCALING
	BYTE bInitMovAvgScalerDen;
	#endif
	
	///----------------------------------------------------------------------------------------------------------------------------///
	/// 	34. Green Mode Counter
	///----------------------------------------------------------------------------------------------------------------------------/// 
	WORD wGreenModeCountVaule;
	WORD wGreenModeCounter;
	BYTE bTimerStatus;
	BYTE bTimerTrimCounter;			///< Every IC-Chip different, Low frequence-OSC count 2^12 => X-period , High frequence-OSC count 3000 => Y-period , bTimerTrimCounter = X-period / Y-period
	BYTE bTimerCounter;
	///----------------------------------------------------------------------------------------------------------------------------///
	///  Border Coordinate Compensation
	///----------------------------------------------------------------------------------------------------------------------------///
	#ifdef FEATURE_BORDER_COOR
	WORD wSenseAxisBorderCompNearNum;
	WORD wSenseAxisBorderCompFarNum;
	WORD wSenseAxisBorderCompNearFarDen;
	WORD wDriveAxisBorderCompNearNum;
	WORD wDriveAxisBorderCompFarNum;
	WORD wDriveAxisBorderCompNearFarDen;
	BYTE bSenseAxisInterpolation;
	BYTE bDriveAxisInterpolation;
	#endif ///< for FEATURE_BORDER_COOR

	WORD wSenseAxisBorderHitCompNearNum;
	WORD wSenseAxisBorderHitCompFarNum;
	WORD wDriveAxisBorderHitCompNearNum;
	WORD wDriveAxisBorderHitCompFarNum;

	#ifdef FEATURE_DEBUG_AVOID_TAP_LINE	
	WORD wDistTap;
	PointType  pA;
	PointType  pB;
	#endif
	#ifdef FEATURE_AVOID_TAP_DEBUG
	WORD wRoundCnt;
	WORD wRaw2RawDist;
	WORD wRaw2RawDist2;
	WORD wRaw2RawDist3;
	WORD wDist;
	WORD wDist2;
	WORD wDist3;
	#endif

	#ifdef FEATURE_GG_FILTER_FIX
	WORD wRaw2RawDist;
	BYTE bInterpolationAvg ;
	#endif
	#ifdef FEATURE_CLUSTER_ID_DEBUG
	BYTE bIDmarker ;
	BYTE bIDNumMax ;
	#endif

	#ifdef FEATURE_ENHANCE_DECIMA_STADY_RANGE
	BYTE bEnhanceSteadyDebounce ;
	#endif
	
	///----------------------------------------------------------------------------------------------------------------------------///
	///  ReK reference
	///----------------------------------------------------------------------------------------------------------------------------///
	BYTE NFingerCnts ;
	BYTE PFingerCnts ;
	short NFingerMaxDevSum;
	short PFingerMaxDevSum;	
	WORD wContinueReKStopCnt;
	BYTE bReKWithFingerCnt;

	#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
	BYTE bClusterPeakCnt;
	BYTE bClusterMergeRatio;
	BYTE bClusterDividRatio;
	BYTE bClusterSizeDecRatio;
	BYTE bClusterSizeIncRatio;	
	//BYTE bClusterPeakSourrend[CLUSTER_SQUARE];
	//ClusterRangeType ClusterPeakEdgeI;
	//ClusterRangeType ClusterPeakEdgeJ;	
	#endif
	
	#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER_DEBUG
	BYTE bTotalClusterCnt;
	#endif
	
	#ifdef FEATURE_CMD_SWITCH_DEBUG
	BYTE bDebugCtrl;
	#endif
	
	#if defined(FEATURE_COOR_EXTEND_BASE_ON_DRIVE_TRACE_DEBUG) || defined(FEATURE_COOR_SHIFT_BASE_ON_SENSE_TRACE_DEBUG)
	BYTE bSenseAxisChannelIDX;
	BYTE bDriveAxisChannelIDX;
	WORD wCoordORG;
	WORD wCoordNEW;
	WORD wChannelMidPt;
	WORD wChannelMidH;
	WORD wChannelMidL;
	#endif

	#ifdef FEATURE_ALLPOINT_HEAVY_PRESS_CUT_AVG_ALG
	WORD wAllPointDevAvg;
	#endif
	#ifdef FEATURE_ALLPOINT_HEAVY_PRESS_CUT_AVG_ALG_DEBUG
	WORD wAllPointDevAvgDebug;
	WORD wAllPointDevAvgDebug2;
	#endif

	///----------------------------------------------------------------------------------------------------------------------------///
	///  Floating Finger Enhancement Algorithm
	///----------------------------------------------------------------------------------------------------------------------------///
  #ifdef FEATURE_FLOATING_FINGER_ENHANCE
  ///short sAvgTtl;
  #ifdef FEATURE_FLOATING_FINGER_ENHANCE_DEBUG
  BYTE  bPeakFlagArr[MAX_TRACE_NUM];
  short sPosAvgTtlFinalArr[MAX_TRACE_NUM];
  short sPosSumTtlFinalArr[MAX_TRACE_NUM];
  short sPosDataMaxArr[MAX_TRACE_NUM];
  short sRatioPosSumTtlPosDataMax[MAX_TRACE_NUM];
  short sPosAvgTtlArr[MAX_TRACE_NUM];
  short sNegDevAvg[MAX_TRACE_NUM];
  #endif
  #endif
	
	///----------------------------------------------------------------------------------------------------------------------------///
	///  1T2R Dev Compensation Algorithm
	///----------------------------------------------------------------------------------------------------------------------------///
	#ifdef FEATURE_1T2R_ARCHITECTURE_FARNEAR_REDUCTION
	WORD *p1T2RRawDevSum[2];
	WORD *p1T2RAlgDevSum[2];
	BYTE b1T2RMAEn;
  #ifdef FEATURE_1T2R_NEAR_FAR_NEW_EQU_DEBUG
	WORD wCrsTlkEstArrEven[MAX_TRACE_NUM];
	WORD wCrsTlkEstArrOdd[MAX_TRACE_NUM];
	BYTE bRatioContriArr[MAX_TRACE_NUM];
	BYTE bRatioArr[MAX_TRACE_NUM];
	WORD wNFLargeBEven;
	WORD wNFLargeBOdd;
  #endif
  #ifdef FEATURE_1T2R_NEAR_FAR_MA_DEBUG
  BYTE bRatioTrace[MAX_TRACE_NUM];
  #endif

  ///#ifdef FEATURE_1T2R_NEAR_FAR_MA_SHOW_AVG
  short sSumArrEven[MAX_TRACE_NUM];
  short sSumArrOdd[MAX_TRACE_NUM];
  short sAvgEvenTtl;
  short sAvgOddTtl;
  ///#endif

  ///#ifdef FEATURE_1T2R_NEAR_FAR_COMPEN_1ST_SHOW_AVG
  WORD wSumArrEven1st[MAX_TRACE_NUM];
  WORD wSumArrOdd1st[MAX_TRACE_NUM];
  ///#endif

  #ifdef FEATURE_1T2R_NEAR_FAR_MA_SHOW_MA
  short sMAArrEven[MAX_TRACE_NUM];
  short sMAArrOdd[MAX_TRACE_NUM];
  #endif

	#ifdef FEATURE_1T2R_NEAR_FAR_MA_SHOW_SLOPE
	short sSlopeArr[MAX_TRACE_NUM];
	#endif
  
	#endif

	BYTE PnDecodeADNum;
	WORD wTXCtrlBackup[4];

	#ifdef FEATURE_NOISE_DETECTION_MODE
	WORD wFFTArray[32];
	#endif

	//FrequecnyHopToneType HopTone[MAX_HOP_NUM];
	BYTE bNowToneID;	///< Tone B setup
	BYTE bGoodToneID;	///< Tone B setup
	BYTE bDynamicFreqHopScanCnt;
	BYTE bDynamicFreqHopRoundCnt;
	BYTE bDynamicFreqStatus;
	BYTE bDynamicHistoryCnt;
	BYTE bDynamicCurrentIDBadCnt;
  BYTE bDynamicHopDataOutSel;

	#ifdef FEATURE_NOISE_REJECTION
	BYTE bNoiseRejEn;
	#endif

	#ifdef FEATURE_CLUSTER_PEAK_MERGE_DEUG
	WORD wClusterPeakFlowDebug;
	WORD wClusterWeightDebug;
	WORD wClusterWeightDebug2;
	BYTE bTrackClusterCntsDEBUG ;	
	BYTE bClusterDEBUG;
	BYTE bFingerCntDEBUG;
	#endif

	#ifdef FEATURE_ZET7100_DEBUG_MODE
	BYTE bScanDebugMode;
	#endif
	
	#ifdef FEATURE_CLUSTER_MERGE_V61_DEBUG	
	BYTE bTotalClusterCntDebug;
	WORD bPeakVellyTH;
	WORD bPeakVellyDev;
	#endif

	#ifdef FEATURE_LINEARITY_COMPENSATION_DEBUG
	int iCoordinate;
	int iCoordinate16;
	WORD wAxisInterpolation16;
	int iInterpolation16Div2;
	int iBias16;
	int iCoordinate16Virtual;
	int iCompenTerm16;
	#endif

  #ifdef FEATURE_LINEARITY_COMPENSATION
  #ifdef FEATURE_LINEARITY_COMPENSATION_16TIMES
	int iDriveAxisNearStart16;
	int iDriveAxisFarStart16;	
	int iSenseAxisNearStart16;
	int iSenseAxisFarStart16;	
	#endif
	#endif

	#ifdef FEATURE_COORD_GAIN_SHIFT
	I2 iSenAxisReportGain;
	I2 iDriAxisReportGain;
	I2 iSenAxisResX16D2;
	I2 iDriAxisResX16D2;
	#endif

	#ifdef FEATURE_RAW_DEV_IMPORT
	WORD wImportCnt;	
	BYTE bImportFlowCtrl;	
	#endif
		
	#ifdef FEATURE_WATER_INIT_SCAN
	BYTE bWaterStatus;
	BYTE bWaterDetectCnt;
	BYTE bWaterNoInitCnt;
	WORD wWaterBaseTrackDebounce;
	#ifdef FEATURE_WATER_INIT_SCAN_DEBUG
	int bWaterDebug;	
	int bWaterInitSum;	
	#endif
	#endif
	BYTE bMaxFingerSupport;

	#ifdef FEATURE_IIR_FINGER_UP_DEBUG
	BYTE bFingerStatusDebug;
	BYTE bFingerProcessDebug;
	#endif
  //add for Zetouch mode & Customer mode swtching
	BYTE bWorkingState;

	#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER
	#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_FINGER_PROTECT_INTEN_CTRL
	BYTE bSenDevProcIntenCtrlAvgTtl;
	BYTE bSenDevProcIntenCtrlAvgLcl;
	#endif
	#endif

	#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_NEW_AVG_DEBUG
	short sAvg[20];
	#endif

	#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_PROC_PRIORITY_CTRL_DEBUG
	BYTE bAlg_Func_Ctrl;
	#endif

	#ifdef FEATURE_IIR_FILTER_SMOOTHING_SCALING_DEBUG
	U2 wLastExePointXLsb16;
	U2 wLastExePointYLsb16;
	#endif
	
	BYTE NoReportCnt;

#ifdef FEATURE_HOVER
	BYTE bHoverInDebounce;
	BYTE bHoverOutDebounce;
	WORD wHoverLastCoordinateY;
	WORD wHoverLastCoordinateX;
#endif 

	#ifdef FEATURE_COORD_FORCE_IIR_AREA_DEBUG
	BYTE bIIRAreaCnt;
	#endif	
#ifdef FEATURE_FAKE_FORCE_TOUCH   
	WORD wLastNormalizedSum[MAX_CLUSTER_SUPPORT];
#endif	
}GlobalVarType;

#ifdef FEATURE_CUSTOMER_PROTOCOL

#ifdef NEW_I2C_PARSING_FLOW

typedef struct PACK I2CCmdStructure
{
  BYTE const code *Cmdkey;
	//BYTE CmdSize;
  void (*CmdHF)(); 
} I2CCmdType;


typedef struct CustomerVarSt
{
	BYTE bCustomerBuf[CUSTOMER_BUF_LEN]; 
 // BYTE bWorkingState;
	BYTE bWorkingSubState;

	BYTE bCustomCmd0000Cnt;
  BYTE bCustomCmd0102Cnt;
	BYTE bCustomCmd5801Cnt;
	BYTE bCustomCmd5901Cnt;

	BYTE bCustomCmd00eeCnt;
	BYTE bCustomCmd05Cnt;
	BYTE bCustomCmd04Cnt;
	BYTE bCustomCmd03Cnt;
	BYTE bCustomCmd1eCnt;
	BYTE bCustomCmd0eCnt;
	BYTE bCustomCmd6501Cnt;
	BYTE bCustomCmd6801Cnt;
	BYTE bCustomCmd6801nnCnt;
	
	BYTE bI2CKeepSendflag;
	//BYTE bCustomCmdD801Cnt;

	BYTE bCustomCmd5901WakeupCnt;
	//BYTE bCustomCmdE201Cnt;

  BYTE bCustomReportCnt; 

	BYTE bWakeUpFlag;
	BYTE bCustomerUpgradeFlag;


	BYTE bLastCustomCmdBuf[8]; 
	BYTE bINTtriggerCnt;
	BYTE bCustomerReSendCNT;	
  BYTE bCustomerReportFingerCNT;
	BYTE bCustomerLastReportFingerCNT;
  WORD wCustomerLastValidPoint;

  BYTE bCustomerKeyReportFlag;
	BYTE bCustomerKeyValidByte;

	BYTE bTimerINTtrigger;

	BYTE bDebugBuf[16]; 
	//BYTE bDoubleBufferIdx;

	BYTE bDoubleBufferStoreIdx;
	BYTE bDoubleBufferSendIdx;

  BYTE bDoubleBuffer[2][80];
	BYTE bcntBuffer[2][2];
}CustomerVarType;


#else


typedef struct CustomerVarSt
{
	BYTE bCustomerBuf[CUSTOMER_BUF_LEN]; 
 // BYTE bWorkingState;
	BYTE bWorkingSubState;

	BYTE bCustomCmd0000Cnt;
  BYTE bCustomCmd0102Cnt;
	BYTE bCustomCmd5801Cnt;
	BYTE bCustomCmd5901Cnt;

	BYTE bCustomCmd6501Cnt;
	BYTE bCustomCmd6801Cnt;
	BYTE bCustomCmd6801nnCnt;
	
	BYTE bI2CKeepSendflag;
	//BYTE bCustomCmdD801Cnt;

	BYTE bCustomCmd5901WakeupCnt;
	//BYTE bCustomCmdE201Cnt;

  BYTE bCustomReportCnt; 

	BYTE bWakeUpFlag;
	BYTE bCustomerUpgradeFlag;


	BYTE bLastCustomCmdBuf[8]; 
	BYTE bINTtriggerCnt;
	BYTE bCustomerReSendCNT;	
  BYTE bCustomerReportFingerCNT;
	BYTE bCustomerLastReportFingerCNT;
  WORD wCustomerLastValidPoint;

	BYTE bTimerINTtrigger;	
 	
	BYTE bDebugBuf[16]; 
	
	BYTE bDoubleBufferIdx;
	BYTE bDoubleBuffer[2][91];
  BYTE bCustomerKeyReportFlag[2];
	BYTE bCustomerKeyValidByte[2];
}CustomerVarType;
#endif

#ifdef FORCE_SENSOR_PROTOCOL
typedef struct CustomerForceSensorVarSt
{  
	 BYTE bDoubleBufferStoreIdx;
	 BYTE bDoubleBufferSendIdx;
	 BYTE	bCmdRemapEnableFlag;
	 BYTE bCmdPatternCheckEnableFlag;
   BYTE bCustomerForceSensorBuf[CUSTOMER_FORCESENSOR_BUF_LEN];
   //WORD wCustomerForceSensorAdBase[2][MAX_BASE_ARRAY_SIZE];  //DoubleBuffer 
   WORD wCustomerForceSensorAdBase[2][12*8];  //DoubleBuffer 
} CustomerForceSensorVarType;
#endif

#endif



typedef struct GlobalVarParaSt
{
	BYTE bCmdPara[512];
} GlobalVarParaType;


#endif ///< __TYPEDEF_H__

