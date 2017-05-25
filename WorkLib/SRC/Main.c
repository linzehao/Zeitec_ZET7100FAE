/**
 * @file Main.c
 *
 *  main code and main loop
 *
 *
 * @version $Revision: 75 $
 * @author JLJuang <JL.Juang@zeitecsemi.com>
 * @note Copyright (c) 2010, Zeitec Semiconductor Ltd., all rights reserved.
 * @note
*/
#include"ZetDEF.h"

///---------------------------------------------------------------------------///
/// Registers
///---------------------------------------------------------------------------///
REGISTERS RegTrnumType RegTrumA __attribute__((section(".REG_TRUMA0")));     ///< _at_ 0x194004
REGISTERS RegTrnumType RegTrumB __attribute__((section(".REG_TRUMB0")));     ///< _at_ 0x194024

#ifndef FEATURE_MCU_LIB_ENABLE
REGISTERS GpioType RegGpio             __attribute__((section(".REG_GPIO")));        ///< _at_ 0x18C040
#endif

///---------------------------------------------------------------------------///
/// ZetVar
///---------------------------------------------------------------------------///
//lobalVarType  volatile   xdata  ZetVar __attribute__((section(".MEM_ZETVAR"))) ;
GlobalVarType volatile xdata ZetVar ;
GlobalVarParaType volatile xdata ZetVarPara __attribute__((section(".MEM_ZETVARPARA"))) ;

int volatile BreakPoint = 1;

BYTE volatile xdata INTPortReg;
BYTE volatile xdata INTPinBit; 

///---------------------------------------------------------------------------///
/// Main Loop Control
///---------------------------------------------------------------------------///
WORD volatile data LoopIdx;

///---------------------------------------------------------------------------///
/// General purpose buffer
///---------------------------------------------------------------------------///
BYTE volatile xdata *pGenBuf;    ///< General Purpose Buffer Pointer , it point to the AlgorithmDataPtr->bDevAlloc
BYTE volatile xdata *pGenBuf1;    ///< General Purpose Buffer Pointer1 , it point to the cluster buffer

///---------------------------------------------------------------------------///
/// Mutual Dev Buffer
///---------------------------------------------------------------------------///
MutualScanDevDataType volatile xdata  *AlgorithmDataPtr;
MutualScanDevDataType volatile xdata  *ScanLatchDataPtr;

#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
MutualScanDevDataType volatile xdata  *ForceAlgorithmDataPtr;
MutualScanDevDataType volatile xdata  *ForceScanLatchDataPtr;
	#endif
#endif

RegTrnumType volatile xdata *Trum[2];
///---------------------------------------------------------------------------///
/// DEV Collect
///---------------------------------------------------------------------------///
#ifdef FEATURE_DEV_COLLECT
BYTE volatile data DevCollectMode;
BYTE volatile xdata bDevCount;
//WORD volatile xdata DevSum[MAX_SENSE_TRACE_NUM + 2];
//BYTE volatile xdata DevMax[MAX_SENSE_TRACE_NUM + 2];
//BYTE volatile xdata DevMax2[MAX_SENSE_TRACE_NUM + 2];
//BYTE volatile xdata DevMin[MAX_SENSE_TRACE_NUM + 2];
BYTE volatile data DevCollectCount;
BYTE volatile data DevCollect2Pow;  
#endif ///< for FEATURE_DEV_COLLECT

///---------------------------------------------------------------------------///
/// Distance Calculation
///---------------------------------------------------------------------------///
WORD volatile data wNowCoordinateX;
WORD volatile data wNowCoordinateY;
WORD volatile data wLastCoordinateX;
WORD volatile data wLastCoordinateY;

///---------------------------------------------------------------------------///
/// NOISE_REJECTION
///---------------------------------------------------------------------------///
#ifdef FEATURE_NOISE_REJECTION
WORD volatile data wNoiseMax;
#endif

/**
 * @brief CommandVarInit
 *
 *  Command-Changeable Variable initialization
 *
 * @return NULL
 *
 */
void CommandVarInit(void)
{
	SYSSetVarNormal();

	//initial value decided by data flash parameter
	#ifdef FEATURE_CUSTOMER_PROTOCOL
	ZetVar.bWorkingState=ZetDF.cFormatCtrl.scDataCtrl.bDefaultProtocolVendor;
	#else
	ZetVar.bWorkingState=1;
  #endif

  ZetVar.wTestMode						= TP_TEST_NONE;
	ZetVar.wSysMode							= 0;
	ZetVar.wSysMode2						= 0;  	
	#ifdef FEATURE_PRESS_TOUCH 
	ZetVar.bTranType						= TRAN_TYPE_FORCE_C1C2_BASE;
	#else
  ZetVar.bTranType						= ZetDF.cFormatCtrl.scDataCtrl.bTranType;	
	#endif
  ZetVar.bDriveMax = ZetDF.cGlobalData.scPanelInformation.bDriveAxisMax;
  ZetVar.bSenseMax = ZetDF.cGlobalData.scPanelInformation.bSenseAxisMax;
	ZetVar.wFingerSchmitWeight=	ZetDF.cFinger.scNormal.wFingerWeightSchmit;
	#ifdef FEATURE_1T2R_ARCHITECTURE

	if((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE)  == TP_TYPE_1T2R	)
	{
		ZetVar.bDriveMaxAlg = ZetVar.bDriveMax<<1; ///< Drive Axis Num x 2		
		ZetVar.bSenseMaxAlg = ZetVar.bSenseMax>>1; ///< Sense Axis Num / 2			
	}
	#ifdef FEATURE_1T2R_NO_EDGE
	else if((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE) == TP_TYPE_1T2R_NO_EDGE)
	{
		ZetVar.bDriveMaxAlg = (ZetVar.bDriveMax<<1) - 2; ///< Drive Axis Num x 2	 without header/last row
		ZetVar.bSenseMaxAlg = ZetVar.bSenseMax>>1; 		 ///< Sense Axis Num / 2		
	}
	#endif	
	else if((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE)  == TP_TYPE_1T2R_REVERSE) 
	{
		ZetVar.bDriveMaxAlg = ZetVar.bDriveMax<<1; ///< Drive Axis Num x 2		
		ZetVar.bSenseMaxAlg = ZetVar.bSenseMax>>1; ///< Sense Axis Num / 2	
	}
	else	
	#endif	
	{
		ZetVar.bDriveMaxAlg = ZetVar.bDriveMax;
		ZetVar.bSenseMaxAlg = ZetVar.bSenseMax;
	}	

	#ifdef FEATURE_FORCE_TOUCH_SCAN
		#ifdef FEATURE_FAKE_FORCE_TOUCH

		#else
  ZetVar.bForceSenseMax = ZetDF.cGlobalData.scForceTouchInformation.bFSenseAxisMax;
  ZetVar.bForceDriveMax = ZetDF.cGlobalData.scForceTouchInformation.bFDriveAxisMax;
		#endif
	#endif
	ZetVar.CompileDeviceName = ICDEVICENAME ;
}

#ifdef FEATURE_HW_FREQUENCY_HOP
void HopFrequecnyToneSetup(void)
{
	int data i;
	BYTE data bFreqHopNum;
	BYTE data bFreqHopStart;
	BYTE data bFreqHopDelta;

	bFreqHopStart = ZetDF.cSYSFreqHop.scFreqHop.bFreqMulND1;
	bFreqHopDelta = ZetDF.cSYSFreqHop.scFreqHop.bFreqMulDiff1;
	bFreqHopNum 	= ZetDF.cSYSFreqHop.scFreqHop.bFreqHopSetNum;	

	ZetVar.bNowToneID	 = ZetDF.cSYSFreqHop.scFreqHop.bFreqHopCurrentID;
	ZetVar.bGoodToneID = ZetVar.bNowToneID;
	for(i=0;i<bFreqHopNum;i++)
	{
		ZetVar.HopData[i].bToneA = bFreqHopStart + bFreqHopDelta*i;
	}
}
#endif

/**
 * @brief MainInit
 *
 *  Main function initialization
 *
 * @return NULL
 *
 */
void VarInit(void)
{
  int   data i;
	#ifdef FEATURE_CLUSTER_MERGE_V61_DEBUG
	short xdata *ptr1;
	#endif
  ///BYTE  data j;  
	#ifdef FEATURE_MERGE_TWO_FINGER
	BYTE  data bSenseAxisInterpolation;
	BYTE  data bDriveAxisInterpolation;
	#endif ///< for FEATURE_MERGE_TWO_FINGER

  ///-------------------------------------------------------------------------------///
  /// 1. Set the allocation buffer
  ///-------------------------------------------------------------------------------///  
  pGenBuf  = (BYTE xdata *)&ZetVar.MutualScanDevData[0].sDevAlloc[0];	
  pGenBuf1 = (BYTE xdata *)&ZetVar.bGenBuf1[0];		

	for(i=0;i<TRUM_OUT_NUM;i++)
	{
		Trum[0]	=	(RegTrnumType xdata *)&RegTrumA;
		Trum[1]	=	(RegTrnumType xdata *)&RegTrumB;
	}
  ///-------------------------------------------------------------------------------///
	/// 2. System Mode setup Init
  ///-------------------------------------------------------------------------------///
  ZetVar.wAlgoStatus = 0;
  ZetVar.wAlgoStatus2= 0;
	ZetVar.bBaseTrackingTimer = 0;

	ZetVar.bCalibrationCtrl = 0;
  /// Check the Key support
  #ifdef FEATURE_REAL_KEY
  if(ZetDF.cKeyCtrl.scKeyDriveTrace.bKeySupport == TRUE)
  {
    ZetVar.wSysMode |= SYS_MODE_KEY_SUPPORTED;    
  }
	#endif

	ZetVar.wSysMode 		|= SYS_MODE_FORCE_ALL_POINT_SCAN; 
	ZetVar.wAlgoStatus 	|= ALG_INIT_ABNORMAL_MUT_ALL_SCAN;		
 	
	#ifdef FEATURE_SNE_AXIS_INIT_SCAN
	if(ZetDF.cGlobalData.scPanelInformation.bEnableInitScan & SENSE_AXIS_INIT_SCAN)
	{
		ZetVar.wSysMode |=  SYS_MODE_INIT_SCAN_EN_SEN_AXIS; 
	}
	#endif

	#ifdef FEATURE_INIT_REGION_SCAN
	if(ZetDF.cGlobalData.scPanelInformation.bEnableInitScan & DRIVE_AXIS_INIT_PN_SCAN)
	{
		ZetVar.wSysMode2 |=  SYS_MODE2_INIT_PN_SCAN_EN; 
	}
	#endif 

	if(ZetDF.cAlgoPage.scAlgoData.bAlgFuncCtrl & FUN_RAW_DATA_VIEW)
	{
		ZetVar.wSysMode2 |= SYS_MODE2_RAW_MUTUAL_DEV; 
	}

	///-----------------------------------------------------------------------------------------///
	/// 4. PAD Register Initial
	///-----------------------------------------------------------------------------------------///
	PAD_SEL = (volatile unsigned char *)REG32_TR_SEL_OUT_OUT0;

  ///-------------------------------------------------------------------------------///
	/// 6.Load the Drive and Sense Max 
  ///-------------------------------------------------------------------------------/// 
	#ifdef FEATURE_MERGE_DEV_ARRAY
	if(ZetDF.cAlgoPage.scAlgoData.bAlgFuncCtrl & FUN_MERGE_DEV)
	{
		ZetVar.bDriveMaxAlg = ZetVar.bDriveMaxAlg + 1;
	}
	#endif
	
	#ifdef FEATURE_HTYPE_DEV_RE_MAPPING_REV_153 
	if((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE)  == TP_TYPE_H)
	{
		if(ZetDF.cFormatCtrl.scDataCtrl.bTPTypeSub & TP_TYPE_H_AXIS)
		{	
			ZetVar.wDriveAxisInterpolation16 = ((WORD)(ZetDF.cGlobalData.scPanelInformation.wDriAxisRes<<4))/(ZetVar.bDriveMaxAlg);
			ZetVar.wSenseAxisInterpolation16 = ((WORD)(ZetDF.cGlobalData.scPanelInformation.wSenAxisRes<<4))/(ZetVar.bSenseMaxAlg-1);
		}
		else
		{
			ZetVar.wDriveAxisInterpolation16 = ((WORD)(ZetDF.cGlobalData.scPanelInformation.wDriAxisRes<<4))/(ZetVar.bDriveMaxAlg-1);
			ZetVar.wSenseAxisInterpolation16 = ((WORD)(ZetDF.cGlobalData.scPanelInformation.wSenAxisRes<<4))/(ZetVar.bSenseMaxAlg);				
		}
	}
	else
	#endif
	{
		ZetVar.wDriveAxisInterpolation16 = ((WORD)(ZetDF.cGlobalData.scPanelInformation.wDriAxisRes<<4))/(ZetVar.bDriveMaxAlg);
		ZetVar.wSenseAxisInterpolation16 = ((WORD)(ZetDF.cGlobalData.scPanelInformation.wSenAxisRes<<4))/ZetVar.bSenseMaxAlg;
	}
	
	//ZetDF.cGlobalData.scPanelInformation.wDriAxisInterp
	//ZetDF.cGlobalData.scPanelInformation.wSenAxisInterp

  ///-----------------------------------------------------------------------------------------///
  /// 9. Mutual Scan DEV Buffer pointer init
  ///-----------------------------------------------------------------------------------------///
  MSMutualScanDevDataInit();  
	#ifdef FEATURE_FORCE_TOUCH_SCAN
		#ifdef FEATURE_FAKE_FORCE_TOUCH

		#else	
	MSForceScanDevDataInit();
		#endif
	#endif
  ///-----------------------------------------------------------------------------------------///
  /// 10. Virtual Key Init
  ///-----------------------------------------------------------------------------------------///
#ifdef FEATURE_VIRTUAL_KEY  
  ZetVar.pVirtualKey[0] = (VirtualKeyType const code *)&ZetDF.cKeyCtrl.scVirtualKey.wKey0X;
  ZetVar.pVirtualKey[1] = (VirtualKeyType const code *)&ZetDF.cKeyCtrl.scVirtualKey.wKey1X;
  ZetVar.pVirtualKey[2] = (VirtualKeyType const code *)&ZetDF.cKeyCtrl.scVirtualKey.wKey2X;
  ZetVar.pVirtualKey[3] = (VirtualKeyType const code *)&ZetDF.cKeyCtrl.scVirtualKey.wKey3X;
  ZetVar.bVirtualKeyValidByte = 0x00;
  ZetVar.bVirtualKeyEnable =  ZetDF.cKeyCtrl.scVirtualKey.bVKeyEnable;
#endif ///< for FEATURE_VIRTUAL_KEY  

  ///-------------------------------------------------------------------------------///
	/// 11.  ADBASE data pointer init
  ///-------------------------------------------------------------------------------///
  #ifdef FEATURE_SWITCH_DRIVE_SENSE
	ADBasePtrInit();
	#else ///< for FEATURE_SWITCH_DRIVE_SENSE
  j = ZetVar.bSenseMaxAlg;
	for(i=0;i<ZetVar.bDriveMaxAlg;i++)
	{	
		ZetVar.AdBaseRound[i] = (WORD *)(&ZetVar.MutualScanAdBase.AdBaseAlloc[i*j]);
	}
	#endif ///< for FEATURE_SWITCH_DRIVE_SENSE

  ///-------------------------------------------------------------------------------///
  /// 12. Key Control
  ///-------------------------------------------------------------------------------///
  /// Make all keys invalid
  #ifdef FEATURE_REAL_KEY
  ZetVar.KeyCtrl.bKeyValidByte = 0x00;
	ZetVar.bKeyReleaseCnt = ZetDF.cKeyCtrl.scAlgoKeyTh.bKeyReleaseCnt;
	ZetVar.bKeyLastStatus = 0;
	ZetVar.bKeyLockStatus = 0;
	ZetVar.bKeyLockRelease = TRUE;
	#endif ///< for FEATURE_REAL_KEY 
  #ifdef FEATURE_VIRTUAL_KEY
	ZetVar.KeyCtrl.bKeyValidByte = 0x00;
	ZetVar.bKeyReleaseCnt = ZetDF.cKeyCtrl.scAlgoKeyTh.bKeyReleaseCnt;
	ZetVar.bKeyLastStatus = 0;
	ZetVar.bKeyLockStatus = 0;
	ZetVar.bKeyLockRelease = TRUE;
	#endif ///< for FEATURE_VIRTUAL_KEY 
  ///-------------------------------------------------------------------------------///
  /// 13. Algorithm  : Mutual-Scan / Init-Scan Cut DEV Init ==> For normal and charger mode
  ///-------------------------------------------------------------------------------///
  //ZetVar.wCutDevRegionScan = (WORD)((WORD)ZetDF.cDevCut.scDevCut.bMutDevCut  <<( ZetDF.cMutualAnalog.scMutualNormal.bRegDGDCTRL4 & (0x0F)));
	

	///-------------------------------------------------------------------------------///
  /// 14. Frequency Trim Hop
  ///-------------------------------------------------------------------------------///  
  #ifdef FEATURE_TRIM_FREQ_HOP
	MSHopDataInitialization();
	#endif ///< for FEATURE_FREQ_HOP_ALG
	
  ///-------------------------------------------------------------------------------///
	/// Dynamic Frequency initialization
  ///-------------------------------------------------------------------------------/// 
	#ifdef FEATURE_DYNAMIC_FREQ_HOP		
	ZetVar.bDynamicScanCnt		= 0;
	ZetVar.bDynamicFreqSetCnt = 0;
	ZetVar.bDynamicFreqStatus = 0;
	ZetVar.bDynamicCurrentID	=	0;
	ZetVar.bDynamicNewBetterID= 0;
	ZetVar.bDynamicRoundCnt		=	0;
	ZetVar.bDynamicCurrentIDBadCnt=	0;
	ZetVar.bDynamicFreqSetNum =	ZetDF.cSYSFreqHop.scDynamicHop.bDynamicHopFreqSetNum;
	ZetVar.bDynamicHistoryCnt	=	0;
	ZetVar.wDynamicCurrentDelta=0;
	DynamicFreqSetInitialization();
	#endif ///< for FEATURE_DYNAMIC_FREQ_HOP

	
  ///-----------------------------------------------------------------------------------------///
  /// 15. Algorithm  : Palm State Init
  ///-----------------------------------------------------------------------------------------///
  ZetVar.bPalmState = PALM_STATE_LEVEL_0;
  ///-----------------------------------------------------------------------------------------///
  /// 16. Algorithm Status Init
  ///-----------------------------------------------------------------------------------------///
	ZetVar.wAllPointDevAvg = 0;
  ZetVar.bNegFingerMutRekDebounce = 0;
  ZetVar.NFingerCnts      = 0;
  ZetVar.PFingerCnts      = 0;
	#ifdef FEATURE_FINGER_UP_DEBOUNCE_ALG
  ZetVar.bFingerReportCounts = 0;	
	#endif
	ZetVar.bFingerCountsFound	=	0;
  ZetVar.bFingerCountsFoundLast =	0;
	
	for(i=0;i<REPORT_BUFFER_NUM;i++)
	{
		ZetVar.dynamicData[i].wValid	= 0;
	}

	#ifdef FEATURE_INIT_SCAN_DEVDETECT_HEAVY_PRESS	
	ZetVar.bHeavyPressDetectInOutCnt = 0;
	#endif ///< for FEATURE_INIT_SCAN_DEVDETECT_HEAVY_PRESS	 

	///-----------------------------------------------------------------------------------------///
  /// 17. Data Format Init
  ///-----------------------------------------------------------------------------------------///
  ZetVar.pCurReportIdx = 0;
  ZetVar.pCurReportData = (BYTE xdata *)&ZetVar.dynamicData[ZetVar.pCurReportIdx]; 
  ZetVar.bDataIn  = FALSE;
  
  ZetVar.bIntLowTimeout = ZetVar.bI2cIntLowTimeOutDefault;

  /// Transfer Type


  /// Packet mode
  ZetVar.bMTKFormatEnable = ZetDF.cFormatCtrl.scDataCtrl.bMTKFormatEnable; 
  ZetVar.bMTKPacketSize = ZetDF.cFormatCtrl.scDataCtrl.bMTKPacketSize; 

	#ifdef FEATURE_RING_BUFFER
	ZetVar.bAlgRingBufCnt = 0;
	ZetVar.bI2CRingBufCnt = 0;
	ZetVar.bRingBufFlag		=	0;
	#ifdef FEATURE_DEBUG_RING_BUFFER
	ZetVar.bFrameCnt		=	0;
	#endif	
	#endif ///< for FEATURE_RING_BUFFER

  ///-----------------------------------------------------------------------------------------///
  /// 19. For Init-Scan Dev mode init
  ///-----------------------------------------------------------------------------------------///
  for(i = 0 ; i < (MAX_TRACE_NUM + 2) ; i++)
  {
    ZetVar.InitScanSenseDevData.sDev[i] = 0x00; 
		ZetVar.InitScanDriveDevData.sDev[i] = 0x00; 
  }

  ///-------------------------------------------------------------------------------///
  /// 22. Debounce Count
  ///-------------------------------------------------------------------------------///
  /// Finger down debounce count
  SYSSetDebounceNormal();

  /// IIR add one point
  /// Finger up debounce count
  #ifdef FEATURE_IIR_FINGER_UP
  if(ZetDF.cFinger.scNormal.bFingerUpEnable & FINGER_UP_MV_BIT1)
  {
    ZetVar.bFingerUpEn = 3;
    ZetVar.bFingerUpOneDebounceCnt = 0;
    ZetVar.bFingerUpMultiDebounceCnt = 0;
  }
  else
  {
    ZetVar.bFingerUpEn = ZetDF.cFinger.scNormal.bFingerUpEnable;
    ZetVar.bFingerUpOneDebounceCnt = ZetDF.cFinger.scNormal.bDebounceUpCnt;
    ZetVar.bFingerUpMultiDebounceCnt = ZetDF.cFinger.scNormal.bDebounceUpCntMulti;
  }
  #else
  ZetVar.bFingerUpMultiDebounceCnt = ZetDF.cFinger.scNormal.bDebounceUpCntMulti;
  #endif
  
  ///-------------------------------------------------------------------------------///
  /// 23. Finger weight for finger search
  ///-------------------------------------------------------------------------------///
  
  ///-------------------------------------------------------------------------------///
  /// 24. Dev Collect
  ///-------------------------------------------------------------------------------///  
#ifdef FEATURE_DEV_COLLECT 
	DevCollectMode = 0x00;
#endif ///< for FEATURE_DEV_COLLECT

  ///-------------------------------------------------------------------------------///
  /// 25. Re-calibration detect count
  ///-------------------------------------------------------------------------------/// 
  ZetVar.bReCalDetNum = ZetDF.cAlgoPage.scAlgoData.bReCalDetCnt;
	ZetVar.bReCalDetCnt	= ZetDF.cAlgoPage.scAlgoData.bReCalDetCnt;		  	
	ZetVar.bKeyReCalDetCnt = ZetDF.cAlgoPage.scAlgoData.bReCalDetCnt;

  ///-------------------------------------------------------------------------------///
  /// 26. No finger round count
  ///-------------------------------------------------------------------------------///    
  ZetVar.bNoFingerRoundCount = 0;
 
  ///----------------------------------------------------------------------------------------------------------------------------///
  /// 27. Hover Stable Count
  ///----------------------------------------------------------------------------------------------------------------------------///  
	#ifdef FEATURE_TOUCH_HOVER_SENSOR
  ZetVar.bHoverEnterCount =  0;
	ZetVar.bHoverFingerUpDebounceCnt = 0;
  ZetVar.bHoverReleaseCount = 0;
	ZetVar.bHoverFingerDownInZone = 0;
	ZetVar.bHoverFingerDownInScanZone = 0;
	if(ZetDF.cHover.scHoverCtrl.bRangeHoverDirection == HOVER_SCAN_TRACE_START_FROM_START)	
	{
		ZetVar.bHoverCheckTraceStart = 1;
		ZetVar.bHoverCheckTraceEnd	 = ZetDF.cHover.scHoverCtrl.bRangeHoverTraceNum;		
	}
	else
	{
		if(ZetDF.cHover.scHoverCtrl.bHoverScanAxisSelection == HOVER_SCAN_USE_SENSE_AXIS)
		{
			ZetVar.bHoverCheckTraceStart = ZetVar.bSenseMaxAlg - ZetDF.cHover.scHoverCtrl.bRangeHoverTraceNum + 1;
			ZetVar.bHoverCheckTraceEnd	 = ZetVar.bSenseMaxAlg;
		}
		else
		{
			ZetVar.bHoverCheckTraceStart = ZetVar.bDriveMaxAlg - ZetDF.cHover.scHoverCtrl.bRangeHoverTraceNum + 1;
			ZetVar.bHoverCheckTraceEnd	 = ZetVar.bDriveMaxAlg;
		}
	}	
	
	if(ZetDF.cHover.scHoverCtrl.bHoverScanAxisSelection == HOVER_SCAN_USE_SENSE_AXIS)
	{
		ZetVar.bHoverAxisMax				 = ZetVar.bSenseMaxAlg;
	}
	else
	{
		ZetVar.bHoverAxisMax				 = ZetVar.bDriveMaxAlg;		
	}
	#endif ///< for FEATURE_TOUCH_HOVER_SENSOR

	///----------------------------------------------------------------------------------------------------------------------------///
  /// 28. ADC CTRL0 Value Change
  ///----------------------------------------------------------------------------------------------------------------------------///  

	///----------------------------------------------------------------------------------------------------------------------------///
  /// 29. PHSEL for ZETA FPC open / short test
  ///----------------------------------------------------------------------------------------------------------------------------///  

	///----------------------------------------------------------------------------------------------------------------------------///
  /// 30. Sense Val Change 
  ///----------------------------------------------------------------------------------------------------------------------------///  	

	///-----------------------------------------------------------------------------------------///
	/// 31. Re-Calibration / Base-Tracking Total enable/disable Control
  ///-----------------------------------------------------------------------------------------///	
	if(ZetDF.cAlgoPage.scAlgoData.bEnableReCalibration == TRUE)
	{
		ZetVar.bCalibrationCtrl |= BASE_TRACK_RECALIBRAION_TOTAL_CTRL;
	}
	
	///----------------------------------------------------------------------------------------------------------------------------///
  /// 31.CoAxisCheck process execute check
  ///----------------------------------------------------------------------------------------------------------------------------///  	
	#ifdef FEATURE_DEV_COLLECT
	ZetVar.bCoAxisExecuteMdoe = 0;
	if(CoAxisExecuteCheckForNormal()== TRUE)
	{
		ZetVar.bCoAxisExecuteMdoe |= COAXIS_CHECK_EXECUTE_NORMAL_ENABLE;
	}
	if(CoAxisExecuteCheckForCharger()== TRUE)
	{
		ZetVar.bCoAxisExecuteMdoe |= COAXIS_CHECK_EXECUTE_CHARGER_ENABLE;
	}
	#endif ///< FOR FEATURE_DEV_COLLECT
	
  ///----------------------------------------------------------------------------------------------------------------------------///
  /// 32.Initial Coordinate Data
  ///----------------------------------------------------------------------------------------------------------------------------///  	
	for (i=0; i<FINGER_MAX;i++)
  {
    ///-----------------------------------------------------///
    ///  Search Finger Init
    ///-----------------------------------------------------///
  #ifdef FEATURE_NINE_SQUARE_ENABLE
		#ifdef FEATURE_SEARCH_FINGER_TOUCH_FLAG
		ZetVar.SearchFingerRecord[i].bTouch 								= FALSE;
		#endif
				
		#ifdef FEATURE_FINGER_SCHMIT_TRIGGER
		ZetVar.SearchFingerRecord[i].wFingerFoundWeight 		=	0;
		#endif ///< for FEATURE_FINGER_SCHMIT_TRIGGER 		
	#endif ///< for FEATURE_NINE_SQUARE_ENABLE

		if(i<FINGER_MAX_REPORT)
		{
			ZetVar.FingerCoordinateRecord[i].wFingerStatus = 0;
			ZetVar.FingerCoordinateRecord[i].bFingerDown 				= FINGER_UP;
			ZetVar.FingerCoordinateRecord[i].bIIRWeight 				= 0;
			ZetVar.FingerCoordinateRecord[i].bFingerDebounce = 0;
			ZetVar.FingerCoordinateRecord[i].bFingerUpState = 0;
			#ifdef FEATURE_MERGE_CLOSE_NINESQU_FINGER
			ZetVar.TrackCoordinateRecord[i].bStatus 				= 0;
			ZetVar.TrackCoordinateRecord[i].bMergeDebounce	= 0;
      #ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER	
			ZetVar.TrackCoordinateRecord[i].bExistDebounce	= 0;	
      #endif
			#endif
			#ifdef FEATURE_MERGE_CLOSE_CLUSTER_FINGER
			ZetVar.TrackCoordinateRecord[i].bStatus 				= 0;	
			ZetVar.TrackCoordinateRecord[i].bRootClusterID  = 0;	
			#endif	
			#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
			ZetVar.TrackCoordinateRecord[i].bMergeDebounce	= 0;
			ZetVar.TrackCoordinateRecord[i].bFakeDivideDebounce = 0;
			//ZetVar.TrackCoordinateRecord[i].bPeakCnts				= 0;
			#endif			
		}
	}	

	for( i = 0 ; i < (MAX_TRACE_NUM+2); i++)
  {
    ZetVar.MutualScanDevData[0].bFound[i]    = MUTUAL_SCAN_NONE;
    ZetVar.MutualScanDevData[0].bSenFound[i] = MUTUAL_SCAN_NONE;
    ZetVar.MutualScanDevData[1].bFound[i]    = MUTUAL_SCAN_NONE;
    ZetVar.MutualScanDevData[1].bSenFound[i] = MUTUAL_SCAN_NONE;    

		#ifdef FEATURE_FORCE_TOUCH_SCAN
			#ifdef FEATURE_FAKE_FORCE_TOUCH
			
			#else
		ZetVar.ForceScanDevData[0].bFound[i] 	 	 = MUTUAL_SCAN_NONE;
		ZetVar.ForceScanDevData[0].bSenFound[i]  = MUTUAL_SCAN_NONE;
		ZetVar.ForceScanDevData[1].bFound[i] 	 	 = MUTUAL_SCAN_NONE;
		ZetVar.ForceScanDevData[1].bSenFound[i]  = MUTUAL_SCAN_NONE;
			#endif
		#endif		
  } 
	
	///----------------------------------------------------------------------------------------------------------------------------///
	/// 	 27. Base Track Period
	///----------------------------------------------------------------------------------------------------------------------------/// 
	#ifdef FEATURE_POWER_BASE_TRACK
	ZetVar.bBaseTrackPeriod = ZetDF.cAlgoPage.scAlgoData.bBaseTrackPeriodWhenRst;
	ZetVar.wFrameCntUnStableState = 0;
	#else ///< for FEATURE_POWER_BASE_TRACK
	ZetVar.bBaseTrackPeriod = ZetDF.cAlgoPage.scAlgoData.bBaseTrackPeriod;
	#endif ///< for FEATURE_POWER_BASE_TRACK

	#ifdef FEATURE_REK_POWER_BASE_TRACK
	ZetVar.wFrameCntReKUnStableState = 0xFFFF;
	#endif ///< for FEATURE_REK_POWER_BASE_TRACK

  ///-------------------------------------------///
	/// Dev data init
  ///-------------------------------------------///	
  MEMSET((void *)&ZetVar.MutualScanDevData[0].sDevAlloc[0], 0x00, (MAX_DEV_ARRAY_SIZE)*sizeof(short));
  MEMSET((void *)&ZetVar.MutualScanDevData[1].sDevAlloc[0], 0x00, (MAX_DEV_ARRAY_SIZE)*sizeof(short));
	#ifdef FEATURE_PROCESS_COORDINATE_WITH_RAW_DATA
  MEMSET((void *)&ZetVar.MutualScanRawDevData[0], 0x00, (MAX_BASE_ARRAY_SIZE)*sizeof(short));
	#endif ///< for FEATURE_PROCESS_COORDINATE_WITH_RAW_DATA

	#ifdef FEATURE_FORCE_TOUCH_SCAN	
		#ifdef FEATURE_FAKE_FORCE_TOUCH

		#else
  MEMSET((void *)&ZetVar.ForceScanDevData[0].sDevAlloc[0], 0x00, (MAX_DEV_ARRAY_SIZE)*sizeof(short));
  MEMSET((void *)&ZetVar.ForceScanDevData[1].sDevAlloc[0], 0x00, (MAX_DEV_ARRAY_SIZE)*sizeof(short));
	MEMSET((void *)&ZetVar.ForceScanRawDevData[0], 0x00, (MAX_BASE_ARRAY_SIZE)*sizeof(short));
		#endif
	#endif
	
  ///-------------------------------------------///
	/// Gesture Wakeup
  ///-------------------------------------------///	
#ifdef FEATURE_GESTURE_WAKEUP
	ZetVar.bGestureStatus = 0;
	ZetVar.bGestureCount = 0;
#endif ///< for FEATURE_GESTURE_WAKEUP

#ifdef FEATURE_STACK_USED_DEBUG
	ZetVar.dwStackPointerMin = 0xffffffff;
#endif ///< for FEATURE_STACK_USED_DEBUG

  ///-------------------------------------------///
	/// Cluster Search initial
  ///-------------------------------------------///	
	#ifdef FEATURE_CLUSTER_ENABLE
	for(i = 0 ; i < (ZetVar.bDriveMaxAlg); i++)
	{
		ZetVar.ClusterSchmitSwitch[i] = 0;
		#ifdef FEATURE_MUT_PARTIAL_REK
		ZetVar.BaseUpdateControl[i] = 0;
		#endif
		#ifdef FEATURE_MUT_PARTIAL_CROSS_SET
		ZetVar.BaseUpdateCross[i] = 0;
		#endif
	}

	#ifdef FEATURE_CLUSTER_MERGE_V61_DEBUG	
	ptr1 = (short *)(&ZetVar.ClusterMatrixData[0]);
	for(i = 0 ; i < (ZetVar.bDriveMaxAlg + 2); i++)
	{
		ZetVar.ClusterMatrix[i] = (short *)ptr1;
		ptr1 = ptr1 + (ZetVar.bSenseMaxAlg + 2);
	}
	#endif 
	
	#endif ///< for FEATURE_CLUSTER_ENABLE
	
	#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
	ZetVar.bClusterDividRatio = (BYTE)(((WORD)ZetDF.cCluster.scNormalUseState.bClusterPeakVellyDivdeRatio<<CLUSTER_MERGE_RATIO_ORDER)/100);
	ZetVar.bClusterMergeRatio = (BYTE)(((WORD)ZetDF.cCluster.scNormalUseState.bClusterPeakVellyMergeRatio<<CLUSTER_MERGE_RATIO_ORDER)/100);	
	ZetVar.bClusterSizeDecRatio = (BYTE)(((WORD)(ZetDF.cCluster.scNormalUseState.bClusterSizeChangeDecRatio)<<CLUSTER_SIZE_DELTA_RATIO_ORDER)/100);	
	ZetVar.bClusterSizeIncRatio = (BYTE)(((WORD)ZetDF.cCluster.scNormalUseState.bClusterSizeChangeIncRatio<<CLUSTER_SIZE_DELTA_RATIO_ORDER)/100);		
	#endif
	///-------------------------------------------///
	/// Merge Close Finger initialization 
	///-------------------------------------------/// 

	#if defined(FEATURE_MERGE_CLOSE_NINESQU_FINGER) || defined(FEATURE_OLD_MERGE_CLOSE_CLUSTER_FINGER)
	for(i = 0 ; i < FINGER_10_COMBINATION_NUMBER; i++)
	{
		ZetVar.MergeIDStatus[i].bStstus = MERGE_STATE_INITIALIZATION;
		ZetVar.MergeIDStatus[i].bDebounceCnt = MERGE_DEBOUNCE_INIT_VALUE;
	}
	ALMergeParamInitialization();
	#endif ///< for FEATURE_MERGE_CLOSE_NINESQU_FINGER

	#ifdef FEATURE_ADV_NINE_SQAURE
	ZetVar.NineSquClusterIDArray[0] = (BYTE *)(&ZetVar.NineSquClusterIDData[0]);
	ZetVar.NineSquClusterIDArray[1] = (BYTE *)(&ZetVar.NineSquClusterIDData[(MAX_DRIVE_TRACE_NUM +2)*1]);		
	#endif ///< for FEATURE_ADV_NINE_SQAURE

	#ifdef FEATURE_INITIAL_DEV_PROCESS_SCALING
	ZetVar.bInitMovAvgScalerDen = (ZetDF.cAlgoPage.scAlgoChargerMode.bDevProcModeInitScale & INIT_DEV_PROCESS_SCALER) + 12;
	#endif

	///-------------------------------------------///
	/// Border Coordinate Compensation
	///-------------------------------------------///
	#ifdef FEATURE_BORDER_COOR
	ZetVar.bSenseAxisInterpolation = (BYTE)(0x00FF & (ZetVar.wSenseAxisInterpolation16 >>4));	///< divided by 16
	ZetVar.bDriveAxisInterpolation = (BYTE)(0x00FF & (ZetVar.wDriveAxisInterpolation16 >>4));	///< divided by 16	
	ZetVar.wSenseAxisBorderCompNearNum = ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderSenNearCoorPercent	, ZetVar.bSenseAxisInterpolation);
	ZetVar.wSenseAxisBorderCompFarNum  = ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderSenFarCoorPercent		,	ZetVar.bSenseAxisInterpolation);
	ZetVar.wDriveAxisBorderCompNearNum = ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderDriNearCoorPercent	, ZetVar.bDriveAxisInterpolation);
	ZetVar.wDriveAxisBorderCompFarNum  = ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderDriFarCoorPercent		,	ZetVar.bDriveAxisInterpolation);
	
	ZetVar.wSenseAxisBorderCompNearFarDen = ZetVar.bSenseAxisInterpolation >> 1;
	ZetVar.wDriveAxisBorderCompNearFarDen = ZetVar.bDriveAxisInterpolation >> 1;
	#endif ///< for FEATURE_BORDER_COOR
	ZetVar.wSenseAxisBorderHitCompNearNum = ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderHitSenNearCoorPercent	, ZetVar.bSenseAxisInterpolation);
	ZetVar.wSenseAxisBorderHitCompFarNum	= ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderHitSenFarCoorPercent 	, ZetVar.bSenseAxisInterpolation);
	ZetVar.wDriveAxisBorderHitCompNearNum = ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderHitDriNearCoorPercent	, ZetVar.bDriveAxisInterpolation);
	ZetVar.wDriveAxisBorderHitCompFarNum	= ALBorderCompStartEnd(ZetDF.cBorderComp.scAlgoBorderCoorComp.bBorderHitDriFarCoorPercent 	, ZetVar.bDriveAxisInterpolation);
		

	///-------------------------------------------///
	/// Initial Dev is Neg After ReK
	///-------------------------------------------///
	#ifdef FEATURE_MUT_ABNORMAL_REK
	ZetVar.bNegFingerFoundFrameCnt = 0;
	ZetVar.wAfterReKNumMax 					=(ZetDF.cAlgoPage.scAlgoData.bReCalDetAccCnt * ZetDF.cAlgoPage.scAlgoData.bReCalDetCnt )<<2;
	#endif
	
	///-------------------------------------------///
	/// Interpolatin Average
	///-------------------------------------------///
	#ifdef FEATURE_GG_FILTER_FIX
	ZetVar.bInterpolationAvg = (ZetVar.wDriveAxisInterpolation16/16 + ZetVar.wSenseAxisInterpolation16/16)/2;
	#endif

	///-------------------------------------------///
	///  ReK reference
	///-------------------------------------------///
	ZetVar.wContinueReKStopCnt = 0;
	ZetVar.bReKWithFingerCnt = 0;

	#ifdef FEATURE_CLUSTER_ID_DEBUG
	ZetVar.bIDmarker = 0;
	ZetVar.bIDNumMax = 0;
	#endif
	ZetVar.bFingerVellySlop = ZetVar.bFingerSlop;
	#ifdef FEATURE_CMD_SWITCH_DEBUG
	ZetVar.bDebugCtrl = 0;
	#endif

	///-------------------------------------------///
	///  1T2R Dev Compensation Algorithm
	///-------------------------------------------///
	#ifdef FEATURE_1T2R_ARCHITECTURE_FARNEAR_REDUCTION
	Alg1T2RCompPtrInit();
	#endif

  #ifdef FEATURE_1T2R_NEAR_FAR_NEW_EQU_DEBUG
	ZetVar.wNFLargeBEven = 0;
  ZetVar.wNFLargeBOdd = 0;
  #endif
  
  #ifdef FEATURE_1T2R_ARCHITECTURE_FARNEAR_REDUCTION
  for(i=0;i<=ZetVar.bSenseMaxAlg+1;i++)
  {
    ZetVar.sSumArrEven[i] = 0;
    ZetVar.sSumArrOdd[i]  = 0;
  }
  #endif

  #ifdef FEATURE_1T2R_NEAR_FAR_COMPEN_1ST_SHOW_AVG
  for(i=1;i<=ZetVar.bSenseMaxAlg;i++)
  {
    ZetVar.wSumArrEven1st[i] = 0;
    ZetVar.wSumArrOdd1st[i]  = 0;
  }
  #endif

	///-------------------------------------------///
	///  Frequency Hop 
	///-------------------------------------------///
	#ifdef FEATURE_HW_FREQUENCY_HOP
	HopFrequecnyToneSetup();	
	#endif
	SYSSetFreqToneReg(ZetVar.bNowToneID);

	ZetVar.bDynamicFreqHopScanCnt = 0;
	ZetVar.bDynamicFreqStatus			= 0;
	ZetVar.bDynamicFreqHopRoundCnt= 0;
	ZetVar.bDynamicCurrentIDBadCnt= 0;
  ZetVar.bDynamicHopDataOutSel  = 0;

	///-------------------------------------------///
	///  Command parameter SRAM Initial
	///-------------------------------------------///
	SYSScriptRegInitial();
	/*
	ZetVarPara.bCmdPara[SPARA_PNCHIPNUM	] = ZetDF.cMutualAnalog.scMutualNormal.bPnChipNum	;
	ZetVarPara.bCmdPara[SPARA_ADCTRL10	] = ZetDF.cMutualAnalog.scMutualNormal.bADCCtrl10	;
	ZetVarPara.bCmdPara[SPARA_ADCTRL0		] = ZetDF.cMutualAnalog.scMutualNormal.bADC0Gain	;
	ZetVarPara.bCmdPara[SPARA_ADCTRL1		] = ZetDF.cMutualAnalog.scMutualNormal.bADCCtrl1	;
	ZetVarPara.bCmdPara[SPARA_CHGPUMP		] = ZetDF.cMutualAnalog.scMutualNormal.bRegCHGPUMP;
	ZetVarPara.bCmdPara[SPARA_PN_CTRL		] = ZetDF.cMutualAnalog.scMutualNormal.bPnCtrl;
	ZetVarPara.bCmdPara[SPARA_TX_CTRL_H ] = ZetDF.cMutualAnalog.scMutualNormal.wTxCtrl>>8;	

	if((ZetVarPara.bCmdPara[SPARA_ADCTRL10	] & ADC10_MODE_BIT) == ADC10_BUFF_MODE)
	{
		ZetVar.bADC0Gain = 0x70 - ZetVarPara.bCmdPara[SPARA_ADCTRL0		];
	}
	else //if((ZetDF.cMutualAnalog.scMutualNormal.bADCCtrl10 & ADC10_MODE_BIT) == ADC10_SCAL_MODE)
	{
		ZetVar.bADC0Gain = ZetVarPara.bCmdPara[SPARA_ADCTRL0		];
	}

	#ifdef FEATURE_FORCE_TOUCH_SCAN
	ZetVarPara.bCmdPara[SPARA_FORCE_PNCHIPNUM	] = ZetDF.cForceAnalog.scForceNormal.bForcePnChipNum	;
	ZetVarPara.bCmdPara[SPARA_FORCE_ADCTRL10	] = ZetDF.cForceAnalog.scForceNormal.bForceADCCtrl10	;
	ZetVarPara.bCmdPara[SPARA_FORCE_ADCTRL0		] = ZetDF.cForceAnalog.scForceNormal.bForceADC0Gain	;
	ZetVarPara.bCmdPara[SPARA_FORCE_ADCTRL1		] = ZetDF.cForceAnalog.scForceNormal.bForceADCCtrl1	;
	ZetVarPara.bCmdPara[SPARA_FORCE_CHGPUMP		] = ZetDF.cForceAnalog.scForceNormal.bForceRegCHGPUMP;
	if((ZetVarPara.bCmdPara[SPARA_FORCE_ADCTRL10	] & ADC10_MODE_BIT) == ADC10_BUFF_MODE)
	{
		ZetVar.bForceADC0Gain = 0x70 - ZetVarPara.bCmdPara[SPARA_FORCE_ADCTRL0		];
	}
	else //if((ZetDF.cMutualAnalog.scMutualNormal.bADCCtrl10 & ADC10_MODE_BIT) == ADC10_SCAL_MODE)
	{
		ZetVar.bForceADC0Gain = ZetVarPara.bCmdPara[SPARA_FORCE_ADCTRL0		];
	}
	#endif
	//*/
	
	#ifdef FEATURE_NOISE_REJECTION
	if( ((RG_TX_DUAL_TONE & ZetVarPara.bCmdPara[SPARA_PNCHIPNUM])==0x00) && (ZetDF.cMutualAnalog.scMutualNormal.bNoiseRejectEn != 0x00))
	{
		ZetVar.bNoiseRejEn = TRUE;
	}
	else
	{
		ZetVar.bNoiseRejEn = FALSE;
	}
	#endif

	#ifdef FEATURE_ZET7100_DEBUG_MODE
	ZetVar.bScanDebugMode = 0;
	#endif

  #ifdef FEATURE_LINEARITY_COMPENSATION
  #ifdef FEATURE_LINEARITY_COMPENSATION_16TIMES
	ZetVar.iDriveAxisNearStart16 = (ZetVar.bDriveAxisInterpolation) << 4;
	ZetVar.iDriveAxisFarStart16 = (ZetDF.cGlobalData.scPanelInformation.wDriAxisRes) << 4;	
	ZetVar.iSenseAxisNearStart16 = (ZetVar.bSenseAxisInterpolation) << 4;
	ZetVar.iSenseAxisFarStart16 = (ZetDF.cGlobalData.scPanelInformation.wSenAxisRes) << 4;	
	#endif
	#endif

	#ifdef FEATURE_COORD_GAIN_SHIFT
	ZetVar.iSenAxisReportGain = (I2)(ZetDF.cGlobalData.scPanelInformation.iSenAxisReportGain + 512);
	ZetVar.iDriAxisReportGain = (I2)(ZetDF.cGlobalData.scPanelInformation.iDriAxisReportGain + 512);
	ZetVar.iSenAxisResX16D2 = (I2)(ZetDF.cGlobalData.scPanelInformation.wSenAxisRes<<3);
	ZetVar.iDriAxisResX16D2 = (I2)(ZetDF.cGlobalData.scPanelInformation.wDriAxisRes<<3);
	#endif

	#ifdef FEATURE_RAW_DEV_IMPORT
	ZetVar.wImportCnt = 0;	
	ZetVar.bImportFlowCtrl=0;
	#endif
	#ifdef FEATURE_WATER_INIT_SCAN
	ZetVar.bWaterStatus = 0;
	ZetVar.bWaterDetectCnt = 0;
	ZetVar.bWaterNoInitCnt = 0;
	ZetVar.wWaterBaseTrackDebounce = 0;
	#ifdef FEATURE_WATER_INIT_SCAN_DEBUG
	ZetVar.bWaterDebug = 0; 
	#endif
	#endif


	#ifdef FEATURE_IIR_FINGER_UP_DEBUG
	ZetVar.bFingerStatusDebug = 0;
	ZetVar.bFingerProcessDebug = 0;
	#endif


	#ifdef FEATURE_CLUSTER_ENABLE
	ALFingerSearchParam(NORMAL_MODE_PARA);
	#endif

	#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER
	#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_FINGER_PROTECT_INTEN_CTRL
	ZetVar.bSenDevProcIntenCtrlAvgLcl = 8-ZetDF.cAlgoPage.scAlgoData.bSenDevProcIntenCtrl;
	ZetVar.bSenDevProcIntenCtrlAvgTtl = ZetDF.cAlgoPage.scAlgoData.bSenDevProcIntenCtrl;
	#endif
	#endif
	
  #ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_NEW_AVG_DEBUG
  for(i=0;i<20;i++)
  {
    ZetVar.sAvg[i] = 65535;
  }
  #endif

	#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER_PROC_PRIORITY_CTRL_DEBUG
	ZetVar.bAlg_Func_Ctrl = 0;
	#endif

  #ifdef FEATURE_IIR_FILTER_SMOOTHING_SCALING_DEBUG
  ZetVar.wLastExePointXLsb16 = 0;
  ZetVar.wLastExePointYLsb16 = 0;
  #endif

	ZetVar.NoReportCnt = LOW_POWER_MODE_NO_REPORT_CNT;

	#ifdef FEATURE_COORD_FORCE_IIR_AREA_DEBUG
	ZetVar.bIIRAreaCnt = 0;
	#endif

	#ifdef FEATURE_HOVER
	ZetVar.bHoverInDebounce = 0;
	ZetVar.bHoverOutDebounce = 0;
	#endif

	#ifdef REPORT_GESTURE_POINTS_LOG_METHOD
	{
		WORD i;
		bGesturePointBuffer[0]=0xEE;
	  for(i=1;i<600;i++) bGesturePointBuffer[i]=0;
	}

	bCmdD3Cnt=0;
	bINTKeepLowFlag=0;
	bDoubleClickState=0;
	bGesturePointState=GESTURE_POINT_NONE_STATE;
  #endif
	
  #ifdef FEATRUE_MCU_IDLE_IN_WAITFORSCAN
	bWaitForScanFlag=0;
	bPCONIDLEFlag=0;	
	bADCTimerFlag=0;
	dwTmp_TMR1=0xFFFFF000;
	bTimerOneShotFlag=0;
  #endif

	#ifdef FEATURE_FAKE_FORCE_TOUCH
	for(i=0; i<FINGER_MAX_REPORT; i++)
	{
		ZetVar.wLastNormalizedSum[i] = 0;
	}
	#endif	
}
/**
 * @brief MainInit
 *
 *  Main function initialization
 *
 * @return NULL
 *
 */
void MainInit()
{
  ///-------------------------------------------------------------------------------///
  /// Set the IO Voltage 1.8V or 3.3V
  ///-------------------------------------------------------------------------------///
  WRITE_REG16(REG32_P3_SEL18, ZetDF.cMutualAnalog.scMutualNormal.wRegSel18);

  ///-------------------------------------------------------------------------------///
  /// 1. Enable GPIO
  ///-------------------------------------------------------------------------------///
	#ifdef FEATURE_GIO_ENABLE
  SYSGpioInit();
	#endif ///< for FEATURE_GIO_ENABLE
	///-------------------------------------------------------------------------------///  
  /// 2. Command Changeable Variable init 
  ///-------------------------------------------------------------------------------///    
  CommandVarInit();
	
  ///-------------------------------------------------------------------------------///
	/// 3. I2C Init
	///
	///   [JL] : Make the TP able to send the B2 command back, just after system reset
  ///          Do not modify the  session!!!
  ///-------------------------------------------------------------------------------///   
  I2CInit(); 
  TPCmdB2Set();
	#ifdef  FEATURE_CUSTOMER_PROTOCOL
	CustomerInit();
	#ifdef FORCE_SENSOR_PROTOCOL
	CustomerForceSensorInit();
	#endif
	#endif  
  ///-------------------------------------------------------------------------------///
  /// 4. Enable All Interupts
  ///-------------------------------------------------------------------------------///
  IntInit();
  InterruptEnable();

  ///-------------------------------------------------------------------------------///
  /// 5. Trim 512K OSC With High Frequence OSC
  ///-------------------------------------------------------------------------------///
	SYSRC512KTrim();

  ///-------------------------------------------------------------------------------///
	/// 6. Dummy Report
  ///-------------------------------------------------------------------------------///
  DFResetDummyPointSend();

  ///-------------------------------------------------------------------------------///
  /// 7. Variable Init
  ///-------------------------------------------------------------------------------///
  VarInit();

  ///-------------------------------------------------------------------------------///
  /// 8.  SFR  init
  ///-------------------------------------------------------------------------------///  
  SYSInit();
  
  ///-------------------------------------------------------------------------------///
  /// 9. Mutual Scan Trace Setup
  ///-------------------------------------------------------------------------------///  
  TSTraceInit();
	#ifdef FEATURE_FORCE_TOUCH_SCAN
		#ifdef FEATURE_FAKE_FORCE_TOUCH

		#else
  TSForceTouchTraceInit();
		#endif
  #endif

  TSTraceAllSet(PAD_MODE_SEL_GND);

	#ifdef FEATURE_FORCE_TOUCH_SCAN
		#ifdef FEATURE_FAKE_FORCE_TOUCH

		#else
  TSForceTraceAllSet(PAD_MODE_SEL_GND);
		#endif
  #endif

  ADCPowerOff(CAP_MODE);
  ///-------------------------------------------------------------------------------///
  /// 10. Region Scan Init
  ///-------------------------------------------------------------------------------///
#ifdef FEATURE_REGION_SCAN   
  RegionScanInit();
	PnSramTableInit();
#endif ///< for FEATURE_REGION_SCAN  

	///-------------------------------------------------------------------------------///
	/// 11. Trace IO Init
	///-------------------------------------------------------------------------------///
#ifdef FEATURE_TRACEIO_HOVER_SENSOR
	TraceGpioInit();
#endif
}

#ifdef FEATURE_ZET7100_DEBUG_MODE
#define ROWNUM 3
#define GUPNUM (ROWNUM*2)

void DebugInformation()
{
	int data i;
	int data j;
	
	int data k;
	int data iPNChipNum=(ZetVarPara.bCmdPara[SPARA_PNCHIPNUM] & PN_CHIP_EN_NUM);
											
	int data iToneNum= PnToneNum;
	int data dwValue;

//	BYTE const code *pSenseTraceId= &ZetDF.cTraceSetup.scPanelSenseAxis.bSen00;	
///	pSenseTraceId = &ZetDF.cTraceSetup.scPanelSenseAxis.bSen00;	
	/*BYTE const code *pDriveTraceId; 	
	pDriveTraceId = &ZetDF.cTraceSetup.scPanelDriveAxis.bDri00;    */ 
//*
	for(i=1;i<=ZetVar.bDriveMaxAlg;i++)
	{
		for(j=1;j<=ZetVar.bSenseMaxAlg;j++)
		{		
			AlgorithmDataPtr->sDev[i][j]		= 0;
			//AlgorithmDataPtr->sRawDev[i][j]	= 0;
			//ZetVar.AdBaseRound[i-1][j-1]		= 99;
		}
		//AlgorithmDataPtr->sDev[i][0]		= i;
	}
//
//
	//-----------------------------------------------//
	// SenseTraceTableIdx
	/*/-----------------------------------------------//	
	for(j=1;j<=ZetVar.bSenseMaxAlg;j++)
	{
		AlgorithmDataPtr->sDev[0][0]  = SenseTraceAdcGroupNum;
		AlgorithmDataPtr->sDev[1][j]  = pSenseTraceId[j-1];
		AlgorithmDataPtr->sDev[2][j]  = SenseTraceTableIdx[j-1];

		AlgorithmDataPtr->sDev[3][0]  = SenseTraceAdcGroup[0].bGroupSize*100;
		AlgorithmDataPtr->sDev[4][j]  = SenseTraceAdcGroup[0].bPos[j-1];
		AlgorithmDataPtr->sDev[5][j]  = SenseTraceAdcGroup[0].bPad[j-1];

		AlgorithmDataPtr->sDev[6][0]	= SenseTraceAdcGroup[1].bGroupSize*100;
		AlgorithmDataPtr->sDev[7][j]	= SenseTraceAdcGroup[1].bPos[j-1];
		AlgorithmDataPtr->sDev[8][j]	= SenseTraceAdcGroup[1].bPad[j-1];	

		AlgorithmDataPtr->sDev[9][0]	= SenseTraceAdcGroup[2].bGroupSize*100;
		AlgorithmDataPtr->sDev[10][j]	= SenseTraceAdcGroup[2].bPos[j-1];
		AlgorithmDataPtr->sDev[11][j]	= SenseTraceAdcGroup[2].bPad[j-1];
	}
	///-----------------------------------------------/*/
	/*/ DriveTraceTableIdx
	//-----------------------------------------------//	
	for(i=1;i<=ZetVar.bDriveMaxAlg;i++)
	{
		AlgorithmDataPtr->sDev[0][0]  = DriveTraceAdcGroupNum;
		AlgorithmDataPtr->sDev[i][1]  = pDriveTraceId[i-1];
		AlgorithmDataPtr->sDev[i][2]  = DriveTraceTableIdx[i-1];

		AlgorithmDataPtr->sDev[i][3]  = DriveTraceAdcGroup[0].bGroupSize*100;
		AlgorithmDataPtr->sDev[i][4]  = DriveTraceAdcGroup[0].bPos[i-1];
		AlgorithmDataPtr->sDev[i][5]  = DriveTraceAdcGroup[0].bPad[i-1];

		AlgorithmDataPtr->sDev[i][6]	= DriveTraceAdcGroup[1].bGroupSize*100;
		AlgorithmDataPtr->sDev[i][7]	= DriveTraceAdcGroup[1].bPos[i-1];
		AlgorithmDataPtr->sDev[i][8]	= DriveTraceAdcGroup[1].bPad[i-1];		
	}	
	//-----------------------------------------------/*/	
	
	//-----------------------------------------------//
	// DriveTraceTableIdx
	//-----------------------------------------------//	
	AlgorithmDataPtr->sDev[ZetVar.bDriveMaxAlg][ZetVar.bSenseMaxAlg]	= ZetVar.bScanDebugMode;
	for(j=1;j<=iPNChipNum;j++)
	{
		for(i=0;i<PnDriveRoundNum;i++)		
		{
			for(k=0;k<iToneNum;k++)
			{
				AlgorithmDataPtr->sDev[0+k*ROWNUM+ i*GUPNUM][0]		= RegionDriveTrace[i].ToneData[k].bRegionTraceNum+10000*i+1000*k;
				AlgorithmDataPtr->sDev[0+k*ROWNUM+ i*GUPNUM][j]		= RegionDriveTrace[i].ToneData[k].bRow[j-1];
				AlgorithmDataPtr->sDev[1+k*ROWNUM+ i*GUPNUM][j]		= RegionDriveTrace[i].ToneData[k].bRegionTrace[j-1];
				dwValue																						= RegionDriveTrace[i].ToneData[k].dwTrumReg[0];
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][1]		= (dwValue>>16) & 0x0000FFFF;
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][2]		= (dwValue>>0 ) & 0x0000FFFF;
				dwValue 																					= RegionDriveTrace[i].ToneData[k].dwTrumReg[1];
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][3] 	= (dwValue>>16) & 0x0000FFFF;
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][4] 	= (dwValue>>0 ) & 0x0000FFFF;		
				dwValue 										     									= RegionDriveTrace[i].ToneData[k].dwTrumReg[2];
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][5] 	= (dwValue>>16) & 0x0000FFFF;
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][6] 	= (dwValue>>0 ) & 0x0000FFFF;		
				dwValue 										     									= RegionDriveTrace[i].ToneData[k].dwTrumReg[3];
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][7] 	= (dwValue>>16) & 0x0000FFFF;
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][8] 	= (dwValue>>0 ) & 0x0000FFFF;	
				dwValue 										     									= RegionDriveTrace[i].ToneData[k].dwTrumReg[4];
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][9] 	= (dwValue>>16) & 0x0000FFFF;
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][10]	= (dwValue>>0 ) & 0x0000FFFF;	
				dwValue 										     									= RegionDriveTrace[i].ToneData[k].dwTrumReg[5];
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][11]	= (dwValue>>16) & 0x0000FFFF;
				AlgorithmDataPtr->sDev[2+k*ROWNUM+ i*GUPNUM][12]	= (dwValue>>0 ) & 0x0000FFFF;	
			}
		}
	}
	//-----------------------------------------------/*/	
	/*/-----------------------------------------------//
	// DriveTraceTableIdx
	//-----------------------------------------------//	
	AlgorithmDataPtr->sDev[0][0]  = 0x9999;
	for(i=0;i<TRUM_OUT_NUM;i++)
	{
		Trum[0]->Channel[i]  = i * 0x11111111;
		Trum[1]->Channel[i]  = i * 0x11111111;
	}
	for(i=0;i<TRUM_OUT_NUM;i++)
	{
		AlgorithmDataPtr->sDev[i+1][0] = 0xFFFF & ((Trum[0]->Channel[i])>>16) ;
		AlgorithmDataPtr->sDev[i+1][1] = 0xFFFF & ((Trum[0]->Channel[i])>>0 ) ;
		AlgorithmDataPtr->sDev[i+1][2] = 0xFFFF & ((READ_REG32(REG32_TRNUM_OUT0+i*4))>>16 ) ;
		AlgorithmDataPtr->sDev[i+1][3] = 0xFFFF & ((READ_REG32(REG32_TRNUM_OUT0+i*4))>>0 	) ; 	
		
		AlgorithmDataPtr->sDev[i+10][0] = 0xFFFF & ((Trum[1]->Channel[i])>>16) ;
		AlgorithmDataPtr->sDev[i+10][1] = 0xFFFF & ((Trum[1]->Channel[i])>>0 ) ;		
		AlgorithmDataPtr->sDev[i+10][2] = 0xFFFF & ((READ_REG32(REG32_TRNUMB_OUT0+i*4))>>16 ) ;
		AlgorithmDataPtr->sDev[i+10][3] = 0xFFFF & ((READ_REG32(REG32_TRNUMB_OUT0+i*4))>>0 	) ; 	
	}
	Trum[1]->Channel[5] = 0xAABBEE22;
	dwValue = Trum[1]->Channel[5];
	AlgorithmDataPtr->sDev[16][0] = 0xFFFF & ((Trum[1]->Channel[5])>>16) ;
	AlgorithmDataPtr->sDev[16][1] = 0xFFFF & ((Trum[1]->Channel[5])>>0 ) ;	
	
	Trum[1]->Channel[4] = 0x99776655;
	dwValue = Trum[1]->Channel[4];
	AlgorithmDataPtr->sDev[17][0] = 0xFFFF & ((dwValue)>>16) ;
	AlgorithmDataPtr->sDev[17][1] = 0xFFFF & ((dwValue)>>0 ) ;
	//-----------------------------------------------/*/	
}

#endif

/**
 * @brief MainInit
 *
 *  Main function initialization
 *
 * @return NULL
 *
 */
#ifdef FEATURE_WATER_INIT_SCAN_DEBUG
void	WaterInforDebug(void)
{
	int data i;
	int data j;	

	for(i=1;i<ZetVar.bSenseMaxAlg;i+=1)
	{
		AlgorithmDataPtr->sDev[0][i] = ZetVar.InitScanSenseDevData.sDevAlg[i];
		//AlgorithmDataPtr->sDev[0][i] = ZetVar.InitScanSenseDevData.sDev[2*i		];	
		//AlgorithmDataPtr->sDev[1][i] = ZetVar.InitScanSenseDevData.sDev[2*i+1	];	
	}

	for(i=1;i<=ZetVar.bDriveMaxAlg;i+=1)
	{
		AlgorithmDataPtr->sDev[i][0] = ZetVar.InitScanDriveDevData.sDevAlg[i];				
	}

//*	
	//AlgorithmDataPtr->sDev[0][0] = ZetVar.bImportFlowCtrl;

	AlgorithmDataPtr->sDev[1][0] = (ZetVar.bCalibrationCtrl & BASE_EN_TRACKINGBASE)?5555:0;
	AlgorithmDataPtr->sDev[1][1] = ZetVar.bBaseTrackingTimer;
	AlgorithmDataPtr->sDev[1][2] = ZetVar.wWaterBaseTrackDebounce;

	AlgorithmDataPtr->sDev[2][1] = (ZetVar.bWaterStatus & WATER_FOUND_ON_INIT)?999:0;
	AlgorithmDataPtr->sDev[2][2] = (ZetVar.bWaterStatus & WATER_FINGER_ON_AREA)?777:0;
	AlgorithmDataPtr->sDev[2][3] = (ZetVar.bWaterStatus & WATER_FOUND_DETECT)?555:0;
	AlgorithmDataPtr->sDev[2][4] = (ZetVar.bWaterStatus & WATER_FOUND_ON_INIT_DELAY)?222:0;	
	AlgorithmDataPtr->sDev[2][5] = ZetVar.bWaterDetectCnt;
	AlgorithmDataPtr->sDev[2][6] = ZetVar.bWaterNoInitCnt;
	AlgorithmDataPtr->sDev[2][7] = ZetVar.bWaterDebug;
	AlgorithmDataPtr->sDev[2][8] = 0x7FFF;	
	AlgorithmDataPtr->sDev[2][9] = ZetVar.bWaterInitSum;

	AlgorithmDataPtr->sDev[3][1] = ZetVar.wFingerSchmitWeight;
	AlgorithmDataPtr->sDev[3][2] = ZetVar.wFingerWeight;	
	AlgorithmDataPtr->sDev[3][3] = ZetVar.wFingerTH;
	AlgorithmDataPtr->sDev[3][4] = ZetVar.wClusterDevSchmtOn;
	AlgorithmDataPtr->sDev[3][5] = ZetVar.wClusterDevSchmtOff;
	AlgorithmDataPtr->sDev[3][6] = ZetVar.bMaxFingerSupport;
//*/
	
}
#endif
int main()
{
  ///-------------------------------------------------------------------------------///  
  /// 1. init 
  ///-------------------------------------------------------------------------------///
  MainInit(); 

	///-------------------------------------------------------------------------------///  
	/// 2. Frequecny Hopping at Boot-Up
	///-------------------------------------------------------------------------------///	
	#ifdef FEATURE_TRIM_FREQ_HOP 
	TaskBootUpFrequencyHopping();
 	#endif ///< for FEATURE_TRIM_FREQ_HOP

	#ifdef FEATURE_BOOT_FREQUENCY_HOP 
	TaskBootUpFrequencyHop();
	MSHopDataInit();
	#endif
	
	#ifdef FEATURE_DYNAMIC_FREQ_HOP
	MSHopDataInitialization();
	#endif ///< for FEATURE_DYNAMIC_FREQ_HOP	

	#ifdef FEATURE_ZET7100_DEBUG_MODE
	//DebugInformation(); 
	#endif

	///-------------------------------------------------------------------------------///  
  /// 3. Do the Calibration
  ///-------------------------------------------------------------------------------///   
	CBTouchPanelCalibration();  	
  ALRegulateDataReset();

	///-------------------------------------------------------------------------------///
  /// 4. Watch Dog 
  ///-------------------------------------------------------------------------------///
	#ifdef FEATURE_WATCH_DOG  
  SYSWatchDogInit();  
	#endif ///< for FEATURE_WATCH_DOG

  ///-------------------------------------------------------------------------------///
  /// 5. Timer
  ///-------------------------------------------------------------------------------///
	#ifdef FEATURE_TIMER  
	CounterInit(ZetDF.cFrameRate.scAlgoFrameRate.wTimerPeriod);
  TimerInit(ZetDF.cFrameRate.scAlgoFrameRate.wTimerPeriod);
	#endif ///< for FEATURE_TIMER

	///-------------------------------------------------------------------------------///  
  /// 6. Preparation to enter mainloop
  ///-------------------------------------------------------------------------------///  
  /// mainloop  
  LoopIdx = 0;

  while(1)
  {	
    ///-------------------------------------------------------------------------------///      
    /// 1. TASK#1 : Round Init 
    ///-------------------------------------------------------------------------------///
    TaskRoundInit();

    ///-------------------------------------------------------------------------------///  
    /// 2. TASK#2 : Re-Calibration
    ///-------------------------------------------------------------------------------///
    TaskCalibation();

		///-------------------------------------------------------------------------------///  
    /// 3. TASK#3 : Key Scan
    ///-------------------------------------------------------------------------------///
    #ifdef FEATURE_REAL_KEY   
    TaskKeyScan();
		#endif ///<for FEATURE_REAL_KEY   

		///-------------------------------------------------------------------------------///  
    /// 4. TASK#4 : Hover Detect
    ///-------------------------------------------------------------------------------///
    #ifdef FEATURE_TOUCH_HOVER_SENSOR
		TaskHoverDetect();    	
		#endif ///< for FEATURE_TOUCH_HOVER_SENSOR
		
		#ifdef FEATURE_TRACEIO_HOVER_SENSOR
		TaskTraceIOHoverDetect();    	
		#endif
			
		///-------------------------------------------------------------------------------///  
    /// 5. TASK#5 : Init-Scan :1.32ms
    ///-------------------------------------------------------------------------------///	
		#ifndef FEATURE_INIT_ISR_SCAN
		TaskInitScan();
		#endif	///< for FEATURE_INIT_ISR_SCAN		

		///-------------------------------------------------------------------------------///  
    /// 6. Dynamic frequency Hopping
    ///-------------------------------------------------------------------------------///
		#ifdef FEATURE_DYNAMIC_FREQ_HOP
		TaskDynamicFrequencyHop();
		#endif ///< for FEATURE_DYNAMIC_FREQ_HOP

		#ifdef FEATURE_NOISE_DETECTION_MODE
		TaskNoiseDetection();
		#endif
		
		#ifdef FEATURE_DYNAMIC_FREQUENCY_HOP 		
		TaskDynamicUpFrequencyHop();
		#endif

		///-------------------------------------------------------------------------------///  
    /// 7. Initial Scan for water issue
    ///-------------------------------------------------------------------------------///
		#ifdef FEATURE_WATER_INIT_SCAN
		TaskWaterInitScan();
		#endif
	
    ///-------------------------------------------------------------------------------///  
    /// 7. TASK#7 : Mutual Scan
    ///    TASK#7 : Region Scan    
    ///-------------------------------------------------------------------------------/// 
		#ifdef FEATURE_INIT_ISR_SCAN
		TaskIsrScanStart();		
		#endif ///< for FEATURE_INIT_ISR_SCAN
		
		#ifdef FEATURE_ALLPOINT_SCAN
		TaskRegionScan();
		#endif	

    ///-------------------------------------------------------------------------------///  
    /// 8. TASK#8 : Algorithm
    ///-------------------------------------------------------------------------------///      
    #ifdef FEATURE_POSITION_ALGORITHM
    TaskAlgorithm();
		#endif
		
		///-------------------------------------------------------------------------------///
		///	8.1 TASK#8.1 Gesture for Wake-up when Suspend
		///-------------------------------------------------------------------------------///
		#ifdef FEATURE_GESTURE_WAKEUP
		TaskGesture(); 
		#endif ///< for FEATURE_GESTURE_WAKEUP	

		#ifdef FEATURE_GESTURE_PRO
		//ZetVar.bReportGestureId = TaskGesturePro(); 
		#endif ///< for FEATURE_GESTURE_PRO	

		///-------------------------------------------------------------------------------///  
		/// 8.2. Debug Information
		///-------------------------------------------------------------------------------/// 
		#ifdef FEATURE_ZET7100_DEBUG_MODE
		DebugInformation();	
		#endif

		#ifdef FEATURE_WATER_INIT_SCAN_DEBUG
		WaitScanDone();
		WaterInforDebug();
		#endif

		#ifdef FEATURE_RAW_DEV_IMPORT
    TaskAlgDebugMode();
		#endif
 		///-------------------------------------------------------------------------------///  
    /// 9. TASK#9 : Data Transfer1
    ///-------------------------------------------------------------------------------/// 
		TaskDataFormat();
		#ifdef FEATURE_CUSTOMER_PROTOCOL	 
	  CustomerDataFormat();
		#endif		
    #ifdef FORCE_SENSOR_PROTOCOL	 
		CustomerForceSensorDataFormat();
		#endif	

		///-------------------------------------------------------------------------------///
    /// 9. Wait untile the scan procedure done (PipeLine with Algorithm End )
    ///-------------------------------------------------------------------------------/// 
    WaitScanDone();

		#ifdef SYNC_SCAN
		CLR_BIT(REG32_P1,P11_OUT);
		#endif
		///-------------------------------------------------------------------------------///  
    /// 10. TASK#9 :	TPTest  
    ///-------------------------------------------------------------------------------///
    TaskTPTest();
    
    ///-------------------------------------------------------------------------------///  
    /// 11. TASK#10 : Power Control
    ///-------------------------------------------------------------------------------///
    TaskPower();	
		
		///-------------------------------------------------------------------------------///  
		/// 12. TASK#10 : Period Control
		///-------------------------------------------------------------------------------///
		#ifdef FEATURE_TIMER
		TaskPeriodControl();
		#endif ///< for FEATURE_TIMER		

    ///-------------------------------------------------------------------------------///
    ///  Mainloop Index ++
    ///-------------------------------------------------------------------------------///
    LoopIdx ++;   
  }
  return 0;
}

