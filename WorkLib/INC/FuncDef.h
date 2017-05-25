/**
 * @file FuncDef.h
 *
 * Define global functions
 *
 * @version $Revision: 70 $
 * @author JLJuang <JL.Juang@zeitecsemi.com>
 * @note Copyright (c) 2010, Zeitec Semiconductor Ltd., all rights reserved.
 * @note
*/
#ifndef __FUNC_DEF__
#define __FUNC_DEF__
/// =============================================================///
///      START OF BOOT  FUNCTION DEFINITION                      ///
/// =============================================================///

///-------------------------------------------------------------------------------///
/// 1. Main Init
///-------------------------------------------------------------------------------///
EXTERN void MainInit();
EXTERN void VarInit(void);
#ifdef FEATURE_SWITCH_DRIVE_SENSE
EXTERN void ADBasePtrInit();
#endif ///< for FEATURE_SWITCH_DRIVE_SENSE

///-------------------------------------------------------------------------------///
/// 2. Task
///-------------------------------------------------------------------------------///
EXTERN void TaskRoundInit(void);
EXTERN void TaskCalibation(void);

#ifdef FEATURE_INIT_ISR_SCAN
EXTERN void TaskIsrScanStart(void);
#else ///< for FEATURE_INIT_ISR_SCAN
EXTERN void TaskInitScan(void);
#endif ///< for FEATURE_INIT_ISR_SCAN

EXTERN void TaskRegionScan(void);

EXTERN void TaskMutualScan(void);
EXTERN void TaskAlgorithm(void);
#ifdef FEATURE_GESTURE_WAKEUP
EXTERN void TaskGesture(void);
#endif ///< for FEATURE_GESTURE_WAKEUP
#ifdef FEATURE_GESTURE_PRO
EXTERN BYTE TaskGesturePro(void);
#endif ///< for FEATURE_GESTURE_PRO
EXTERN void TaskKeyScan(void);
EXTERN void TaskDataFormat(void);
EXTERN void TaskTPTest(void);
EXTERN void TaskPower(void);
#ifdef FEATURE_TOUCH_HOVER_SENSOR 
EXTERN void TaskHoverDetect();
#endif ///< for FEATURE_TOUCH_HOVER_SENSOR
#ifdef FEATURE_TRACEIO_HOVER_SENSOR
EXTERN void TaskTraceIOHoverDetect(void);
EXTERN void TraceGpioInit(void);
#endif

#if defined(FEATURE_TOUCH_HOVER_SENSOR) || defined(FEATURE_TRACEIO_HOVER_SENSOR)
EXTERN void HoverEnterState(void);
EXTERN void HoverReleaseState(void);
#endif

EXTERN void WaitScanDone();
#ifdef SYNC_SCAN
EXTERN void WaitSyncDone();
#endif
#ifdef FEATURE_TIMER
EXTERN void TaskPeriodControl(void);
#endif ///< for FEATURE_TIMER

EXTERN void TaskWaterInitScan(void);

#ifdef FEATURE_RAW_DEV_IMPORT
EXTERN void TaskAlgDebugMode(void);
#endif



#ifdef REPORT_GESTURE_POINTS_LOG_METHOD
EXTERN void DFGesturePointsLog(void);

#endif

///-------------------------------------------------------------------------------///
/// 3. Debug Function
///-------------------------------------------------------------------------------///
EXTERN void DebugShow(BYTE bData);

///-------------------------------------------------------------------------------///
/// 3. Interrupts
///-------------------------------------------------------------------------------///
EXTERN void I2CTxRxReset(void);
EXTERN void IntInit(void);
EXTERN void IntAdcEnable(void);
EXTERN void IntAdcDisable(void);
EXTERN void IntTimerEnable(void);
EXTERN void IntTimerDisable(void);


///-------------------------------------------------------------------------------///
/// 4. I2C Function
///-------------------------------------------------------------------------------///
EXTERN void I2CInit(void);
EXTERN void I2CTxIsr(void);
EXTERN void I2CRxIsr(void);
EXTERN void I2CDispatchCmd(void);
EXTERN void I2CDispatchVenCmd(void);
EXTERN void I2CDataFormatReset(void);
EXTERN void I2CDataFormatResetInt(void);
EXTERN void I2CDataFormatIntLow(void);
EXTERN void I2CDataFormatDataInCheck(void);
#ifdef FEATURE_FINGER_UP_DEBOUNCE_ALG 
EXTERN void I2CDataFormatDataInCheckSub(void);
#endif ///< for FEATURE_FINGER_UP_DEBOUNCE_ALG
EXTERN void  I2CWaitTransferDone(void);

#ifdef FEATURE_MCU_LIB_ENABLE
EXTERN BOOL I2C_INT(void);
//#endif

EXTERN void I2C_INT_LOW(void);
EXTERN void I2C_INT_HIGH(void);

#endif

///-------------------------------------------------------------------------------///
/// 5. System Control
///-------------------------------------------------------------------------------///
EXTERN void SYSSetFreqToneReg(BYTE bID);
EXTERN void SYSInit(void);
EXTERN void SYSGpioInit(void);
EXTERN void SYSAlgoPageInit(void);

EXTERN void SYSSoftReset(void);
EXTERN void SYSSoftResetInt(void);

EXTERN void SYSDeepSleep(void);
#ifdef FEATURE_GESTURE_WAKEUP
EXTERN void SYSDSleepWithRC500K(void);
#endif ///< for FEATURE_GESTURE_WAKEUP
EXTERN void SYSIdle(void);
EXTERN void SYSWakeUp(void);

EXTERN void SYSWatchDogInit(void);

EXTERN void SYSRC512KTrim(void);

EXTERN void SYSCircuitPowerDown(void);
EXTERN void SYSTraceInit(void);

EXTERN void SYSChargerModeEnable();
EXTERN void SYSChargerModeDisable();
EXTERN void SYSSetDebounceCharger();
EXTERN void SYSSetDebounceNormal();

EXTERN void SYSPsuedoInit();
EXTERN void SYSPsuedoSetup(BOOL bChargerEnable);

#ifdef FEATURE_POWER_SAVE_MODE
EXTERN void SYSPowerSaveMode();
#endif ///< for FEATURE_POWER_SAVE_MODE

EXTERN void SYSSetVarNormal() reentrant;
EXTERN void SYSSetVarCharger() reentrant;

#ifdef FEATURE_INIT_SCAN_DEVDETECT_HEAVY_PRESS
EXTERN void SYSSetVarNormalHeavy();
EXTERN void SYSSetVarChargerHeavy();
#endif 

//#ifdef FEATURE_FIX_FRAME_RATE
EXTERN void SYSTimer0Set(void);
EXTERN void SYSTimer0SetInt(void);
//#endif
EXTERN void SYSSetInitialScanReg(void);
EXTERN void SYSKeyScanReg(void);
EXTERN void SYSSetMutualScanReg(void);
#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
EXTERN void SYSSetForceScanReg(void);
	#endif
#endif
EXTERN void SYSSetPnChipDuration(BYTE bPnChipNumber , BYTE bPnControl);

EXTERN void SYSScriptRegInitial(void);



///-------------------------------------------------------------------------------///
/// 6. TP Command
///-------------------------------------------------------------------------------///
EXTERN void TPCmdB2Set(void);

EXTERN void TPCmdA0(void);
EXTERN void TPCmdA1(void);
EXTERN void TPCmdA3(void);
EXTERN void TPCmdAB(void);

///-------------------------------------------------------------------------------///
///  7. Calibration
///-------------------------------------------------------------------------------///
EXTERN void CBTouchPanelCalibration(void);
EXTERN void CBMutualScanCalibration(BYTE bCalibrationTimes);
EXTERN void CBMutualRevScanCalibration(void);
EXTERN void CBBaseArrayAlloc(void);
EXTERN void CBMutualScanTrackBaseCutDev(BOOL bADDDev);
EXTERN void CBMutualResumeTraceSetting(void);
#ifdef FEATURE_INIT_SCAN
EXTERN void CBInitScanTrackBaseCutDev(BOOL bAddDev);
EXTERN void CBInitTrackBaseCutDeV(void);
#endif ///< for FEATURE_INIT_SCAN
#ifdef FEATURE_RECALIBRATION
EXTERN void CBInitSingedDevCheck(void);
EXTERN void CBResetReKCheck(void);
#endif ///< for FEATURE_RECALIBRATION
#ifdef FEATURE_BASE_TRACKING
EXTERN void CBBaseTrackCheck(void);
#endif ///< for FEATURE_BASE_TRACKING
#ifdef FEATURE_MUT_ABNORMAL_REK
EXTERN void CBMutReKCheck(void);
#endif ///< for FEATURE_MUT_ABNORMAL_REK

///-------------------------------------------------------------------------------///
///  8. Region Scan
///-------------------------------------------------------------------------------///
EXTERN void RegionScanDataInit(BYTE bApplyMode);
EXTERN void RegionDataStructSetup(BYTE bApplyMode);
EXTERN void RegionScanInit(void);
EXTERN void PnSramTableInit(void);

EXTERN void RegionScanBaseTrack(void);
EXTERN void RegionScanCalibration(BYTE bCalibrationTimes);
EXTERN void RegionScanProcess(void);
EXTERN void RegionScanTriggerStart(void);
EXTERN void RegionScanCollectIsr(void);
EXTERN void RegionScanIsr(void);
EXTERN void RegionScanReadAdcData(BYTE bDriveRegionId ,BYTE bSenseGroupId, BYTE bCalibrationTimes);
EXTERN void RegionScanReadDevData(BYTE bDriveRegionId ,BYTE bSenseGroupId);
EXTERN void RegionScanSetPNCodeTable(BYTE bPnChipID);

#ifdef FEATURE_1T2R_ARCHITECTURE
EXTERN int RegionDevArrayGet1T2RRow(int Row,int Col);
EXTERN int RegionDevArrayGetRevese1T2RCol(int i,int j);

#endif

#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
EXTERN void ForceScanCalibration(BYTE bCalibrationTimes);
EXTERN void ForceScanReadAdcData(BYTE bDriveRegionId ,BYTE bSenseGroupId, BYTE bCalibrationTimes);
EXTERN void ForceScanTriggerStart(void);
EXTERN void ForceScanIsr(void);
EXTERN void ForceScanReadDevData(BYTE bDriveRegionId ,BYTE bSenseGroupId);
	#endif
#endif

///-------------------------------------------------------------------------------///
///  8. Mutual Scan
///-------------------------------------------------------------------------------///
EXTERN void AdcIsr();

EXTERN void ResetADConverter(void);
EXTERN void StartADConverter(void);
EXTERN void WaitADCConverterDone(void);
EXTERN void ADCPowerOn(BYTE bApplyMode);
#ifdef FEATRUE_TURNOFF_UNUSED_ADC
EXTERN void ADCPartialPowerOn(BYTE bApplyMode);
#endif
EXTERN void ADCPowerOff(BYTE bApplyMode);

EXTERN void MSMutualScanDevDataInit(void);

EXTERN void MSMutualScanAnalogSetup(void);
EXTERN void MSMutualScanKeyAnalogSetup(void);
EXTERN void MSMutualScanKey(void);
EXTERN void MSMutualTraceMappingSetup(void) ;

EXTERN void MSMutualScanTriggerStart(void);
EXTERN void MSMutualScanAdcIsr(void);

#ifdef FEATURE_DEV_COLLECT
EXTERN void MSDevCollectSetup(BYTE bType);

EXTERN void MSDevCollectCtrlSetup();

EXTERN void MSDevCollectAdcIsr();
EXTERN BYTE MSMutualScanCollectProc(BYTE bDev, BYTE idx);
#endif ///< for FEATURE_DEV_COLLECT

EXTERN void ResetDevBuffer(BYTE bDataType);

#ifdef FEATURE_BASE_AVG_REMIDER_RESUME
EXTERN void ResetBaseRemiderBuffer();
#endif ///< for FEATURE_BASE_AVG_REMIDER_RESUME

#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
EXTERN void MSForceScanAnalogSetup(void);
EXTERN void MSForceScanDevDataInit(void);
	#endif
#endif


///-------------------------------------------------------------------------------///
///  9. Key Scan
///-------------------------------------------------------------------------------///
EXTERN void KeyScanProcess(void);
EXTERN void KeyScanCalibration(void);
EXTERN void KeyScanBaseInit(void);
EXTERN void KeyScan(BOOL bDev, BYTE bScanTimes);

///-------------------------------------------------------------------------------///
///  9. Init Scan
///-------------------------------------------------------------------------------///
EXTERN void ISInitScanPrepareSetup(void);
EXTERN void ISInitScanEndSetup(void);
EXTERN void ISInitScanDriveAxisEvenTraceSetup(void);
EXTERN void ISInitScanDriveAxisOddTraceSetup(void);
EXTERN void ISInitScanSenseAxisEvenTraceSetup(void);
EXTERN void ISInitScanSenseAxisOddTraceSetup(void);
EXTERN void ISInitScanSenseAxis(void);
EXTERN void ISInitScanDriveAxis(void);
EXTERN void ISInitScanAnalogSetup(void);

EXTERN void ISInitScanSenseAxisCalibration(BYTE bADMode);
EXTERN void ISInitScanDriveAxisCalibration(BYTE bADMode); 


#ifdef FEATURE_INIT_SCAN
EXTERN void ISInitScanTriggerStart(void);
EXTERN void ISInitScanAdcIsr(void);
#endif ///< for FEATURE_INIT_SCAN 
#ifdef FEATURE_TOUCH_HOVER_SENSOR 
EXTERN void HoverScanCalibration(void) ;
EXTERN void HoverScan(void);
#endif ///< for FEATURE_TOUCH_HOVER_SENSOR

EXTERN void ISInitScanProcessData(void);
EXTERN void ISInitPostDevCut(void);
#ifdef FEATURE_INIT_ISR_SCAN
EXTERN void ISInitScanTriggerStart(void) ;
EXTERN void ISInitScanAdcIsr(void );
#endif ///<for FEATURE_INIT_ISR_SCAN

EXTERN void ISInitPostDevCut(void);


///-------------------------------------------------------------------------------///
/// 10. Algorithm
///-------------------------------------------------------------------------------///
#ifdef FEATURE_CO_AXIS_PROCESS
EXTERN void ALCoAxisProcess();
EXTERN void ALCoAxisDetect();
EXTERN BOOL ALCoAxisCheck();
#endif ///< for FEATURE_CO_AXIS_PROCESS

#ifdef FEATURE_HEAVY_PRESS
EXTERN void ALHeavyPress();
#endif ///<for FEATURE_HEAVY_PRESS


#ifdef FEATURE_NINE_SQUARE_ENABLE
EXTERN void ALTabletNineSquareSearch();
EXTERN void ALTabletNineSquareFingerSearch();
#ifdef FEATURE_ADV_NINE_SQAURE
EXTERN void ALTabletAdvNineSquareFingerSearch();
#endif ///< for FEATURE_ADV_NINE_SQAURE

EXTERN void ALTabletCoordinateProcess();
#ifdef FEATURE_BORDER_DEV
EXTERN void ALBorderDevComp(BYTE row, BYTE col, BYTE id);
#endif ///< for FEATURE_BORDER_DEV
#endif  ///< for FEATURE_NINE_SQUARE_ENABLE

#ifdef FEATURE_BORDER_COOR
#ifdef FEATURE_REV_131
EXTERN int ALBorderXComp(int iOrgCoorX,BYTE idx);
EXTERN int ALBorderYComp(int iOrgCoorY,BYTE idx);
#else
EXTERN int ALBorderXComp(int iOrgCoorX);
EXTERN int ALBorderYComp(int iOrgCoorY);
#endif
EXTERN WORD ALBorderCompStartEnd(BYTE BorderCoorCompenPercent, BYTE bAxisInterpolationLength);
#endif ///< for FEATURE_BORDER_COOR



#ifdef FEATURE_SENSE_DEV_PROCESS
#ifdef FEATURE_SENSE_DEV_PROCESS_MA_FILTER
EXTERN void ALSenDevProcessMA();
EXTERN void ALSenDevProcessEvenOdd(BYTE LoopSrt, BYTE LoopEnd, BYTE DrvAxisNo);
#else
EXTERN void ALSenDevProcess();
#endif
#endif ///< for FEATURE_SENSE_DEV_PROCESS


#ifdef FEATURE_DRIVE_DEV_PROCESS
#ifdef FEATURE_DRIVE_DEV_PROCESS_MA_FILTER
#ifdef FEATURE_1T2R_ARCHITECTURE_DEVPRORCESS
EXTERN void ALDriDevProcessMA1T2R();
#endif
EXTERN void ALDriDevProcessMA();
#else
EXTERN void ALDriDevProcess();
#endif  ///< FEATURE_MUTUAL_DRV_DEV_PROC_USING_MV_FILT

#ifdef FEATURE_1T2R_ARCHITECTURE_CROSSTALK_REDUCTION
EXTERN void	AL1T2RDevCompensation();
#endif

#ifdef FEATURE_1T2R_ARCHITECTURE_FARNEAR_REDUCTION
#ifdef FEATURE_1T2R_NEAR_FAR_DEV_COMPEN
EXTERN void	AL1T2RFarNearDevCompensation(void);
#endif
#ifdef FEATURE_1T2R_NEAR_FAR_DEV_COMPEN_2ND
EXTERN void	AL1T2RFarNearDevCompensation2nd(void);
#ifdef FEATURE_1T2R_NEAR_FAR_DEV_COMPEN_2ND_ACCURACY_MID_AREA_CORRECT_SUBROUTINE
EXTERN short ALDevReduce(short sDevRef1, short sDevRef2, short sDevTarget, BYTE bReduceRatio);
#endif
#endif
EXTERN void	Alg1T2RCompPtrInit(void);
#ifdef FEATURE_1T2R_NEAR_FAR_MA
EXTERN void AL1T2RFarNearDevCompenMA(void);
#endif
#endif

#endif ///< for FEATURE_DRIVE_DEV_PROCESS

EXTERN BOOL AL1T2REvenOddCheck(int Row , int Col);


EXTERN void ALSpecifyCutDev();

#ifdef FEATURE_INITIAL_DEV_PROCESS
EXTERN void ALInitialDevProcess();
#endif ///< for FEATURE_INITIAL_DEV_PROCESS

#ifdef FEATURE_VIRTUAL_KEY 
EXTERN void  ALVirtualKey();
#endif ///< for FEATURE_VIRTUAL_KEY

#ifdef FEATURE_ONEWAY_COORD_TRACK
EXTERN void ALFingerTracking();
#endif 

#ifdef FEATURE_ADVANCE_COORD_TRACK
EXTERN void ALFingerTrackingAdvance();
#endif 


EXTERN WORD ALCalculateCoordDiff();
#ifdef FEATURE_FINGER_UP_DEBOUNCE_ALG
EXTERN void ALDebouncingSystem(BYTE bFingerId,BYTE bDebounceCntDown,BYTE bDebounceCntUp);
EXTERN void ALReportZeroFingerCounting();
#else ///< for FEATURE_FINGER_UP_DEBOUNCE_ALG
EXTERN void ALDebouncing(BYTE bFingerId);
#endif ///< for FEATURE_FINGER_UP_DEBOUNCE_ALG

EXTERN void ALFingerDebounce();
EXTERN BYTE ALSteadyRange(BYTE bFingerId);

EXTERN void ALCoordinateSmoothing();
EXTERN void ALRegulateDataReset();

EXTERN void ALPalmDetect(void);

EXTERN void ALKeyDetect(void);

#ifdef FEATURE_MERGE_TWO_FINGER
EXTERN void ALMergeFinger(void);
EXTERN BYTE ALCalTwoFingerPitch(void);
#endif ///< for FEATURE_MERGE_TWO_FINGER

#ifdef FEATURE_SHARP_DEV_CUT
EXTERN void ALSharpDevCut(BYTE bMI, BYTE bMJ);
#endif ///< for FEATURE_SHARP_DEV_CUT

#ifdef FEATURE_ONE_FINGER_CLUSTER
EXTERN void ALTabletOneFingerCluster(void);
#endif ///< for FEATURE_ONE_FINGER_CLUSTER

#if defined(FEATURE_MERGE_TWO_FINGER) || defined(FEATURE_ONE_FINGER_CLUSTER)
EXTERN void ALTabletOneFingerClusterSub(BYTE bSlot,BYTE bDriStart,BYTE bDriEnd,BYTE bSenStart,BYTE bSenEnd);
#endif ///< for FEATURE_MERGE_TWO_FINGER or FEATURE_ONE_FINGER_CLUSTER

#ifdef FEATURE_INIT_SCAN_DEVDETECT_HEAVY_PRESS
void ALInitHeavyPressDetectChangeMutualGain(void);
#endif ///< FEATURE_INIT_SCAN_DEVDETECT_HEAVY_PRESS
EXTERN BOOL CoAxisExecuteCheck();
EXTERN void CoAxisStateCheck();

#ifdef FEATURE_DEV_COLLECT
EXTERN BOOL CoAxisExecuteCheckForNormal();
EXTERN BOOL CoAxisExecuteCheckForCharger();
EXTERN BOOL ALDevProcessCtrl(BYTE bDevProcessCtrl);
#endif ///< for FEATURE_DEV_COLLECT

#ifdef FEATURE_TOUCH_HOVER_SENSOR 
void HoverFinegrDownInZoneCheck(void);
#endif ///< for FEATURE_TOUCH_HOVER_SENSOR

#ifdef FEATURE_COMP_MUT_WITH_INIT
EXTERN void ALInitDevCompMutDevCtrl();
EXTERN void ALInitDevCompMutDevProcess();
#endif ///< for FEATURE_COMP_MUT_WITH_INIT


#ifdef FEATURE_COORD_EDGE_POSITION_LOCK
#ifndef FEATURE_MERGE_CLOSE_CLUSTER_FINGER
EXTERN BOOL ALFingerInBorderCheck(BYTE idx);
#endif
#endif ///< for FEATURE_COORD_EDGE_POSITION_LOCK


EXTERN void ALCheckSumProcess(void);

#ifdef FEATURE_FLOATING_FINGER_ENHANCE
EXTERN void ALFingerEnhance(void);
#endif


#ifdef FEATURE_CLUSTER_ENABLE
EXTERN void ALClusterClearBuf();
EXTERN void ALPClusterSearch(BYTE bIsHover);
EXTERN void ALPClusterSearchSubReSumWeight(BYTE bRadius , BYTE bType);
EXTERN void ALPClusterSearchSubAlg(void);
EXTERN void ALPClusterSearchSubCoordProc(BYTE bIsHover);
EXTERN BOOL ALPClusterMaxDevWeightCheck(BYTE bID, BYTE bIsHover);

#ifdef FEATURE_MERGE_CLOSE_CLUSTER_FINGER
EXTERN void	ALPSearchTracking(BYTE bIsHover);
EXTERN void	ALPReportTracking(void);
#endif ///< for FEATURE_MERGE_CLOSE_CLUSTER_FINGER


#ifdef FEATURE_NEW_MERGE_CLOSE_CLUSTER_FINGER
EXTERN void	ALPhoneMergeCheck(BYTE bIsHover);
EXTERN int ALPClusterSearchSubCoordCalculate(int dwWeightUpper , int dwWeightLower);

#ifdef FEATURE_CLUSTER_MERGE_V61
EXTERN BYTE ALProjectDevPeakCnt(BYTE bID , BYTE bTHRatio);
EXTERN BYTE ALProjectDevPeakSearch(BYTE bTHRatio);
#endif
#endif

#endif  ///< for FEATURE_CLUSTER_ENABLE

#ifdef FEATURE_MERGE_CLOSE_NINESQU_FINGER
EXTERN void ALTabletMergeCloseFinger(void);
EXTERN void ALTabletSearchTracking(void);
EXTERN void ALTabletReportFingerTracking(void);
#endif ///< for FEATURE_MERGE_CLOSE_NINESQU_FINGER 

#if defined(FEATURE_OLD_MERGE_CLOSE_CLUSTER_FINGER) || defined(FEATURE_MERGE_CLOSE_NINESQU_FINGER)
EXTERN void ALMergeParamInitialization(void);
#endif

#ifdef FEATURE_MUT_PARTIAL_REK
EXTERN void ALClearPartialMutReKControl(void);
#endif

#ifdef FEATURE_LTYPE_DEV_RE_MAPPING
EXTERN void ALLTypeDevReMapping(void);
#endif

#ifdef FEATURE_HTYPE_DEV_RE_MAPPING
EXTERN void ALHTypeDevReMapping(void);
#endif

#ifdef FEATURE_RAW_DATA_COPY
EXTERN void ALDevRawDataCopy(void);
#endif

#ifdef FEATURE_MERGE_DEV_ARRAY
EXTERN void ALMergeDevMapping(void);
#endif

#ifdef FEATURE_BORDER_DEV_INTERNAL
EXTERN void ALBorderDevInternalComp();
#endif

EXTERN void ResetBaseBuffer(void);
#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
EXTERN void ResetForceBaseBuffer(void);
	#endif
#endif

#ifdef FEATURE_FORCE_TOUCH_SCAN  
EXTERN BYTE FingerMapForceDev(int bi , int bj);
EXTERN LocationType ClusterCenter(BYTE bID);
#endif

#ifdef FEATURE_FAKE_FORCE_TOUCH
EXTERN short ALPFakeForceTouch(int bi , int bj);
EXTERN WORD UpdateSumValue(WORD NowSum, WORD LastSum, WORD LimitedValue);
#endif

#ifdef FEATURE_GESTURE_PRO
EXTERN BYTE GetFreemancode(I2 xi, I2 yi);
EXTERN BYTE editDistance(BYTE lengthTarget, BYTE lengthSource, BYTE *bufTarget, volatile BYTE *bufSource);

#endif

EXTERN void ALFingerSearchParam(BYTE bMode);
EXTERN void ALReseveMaxClusterInWaterMode(void);

EXTERN void ALInitDevRatio(void);


///-------------------------------------------------------------------------------///
///  11. Data Format Function
///-------------------------------------------------------------------------------///
EXTERN void DFResetDummyPointSend(void);
EXTERN void DFMutualAdBaseSend(BYTE bSenseNumber, BYTE bDriveNumber, BYTE bApplyMode);
#ifdef FEATURE_TOUCH_HOVER_SENSOR 
EXTERN void DFHoverAdBaseSend(void);
#endif ///< for FEATURE_TOUCH_HOVER_SENSOR

#ifdef FEATURE_WIN8_DATAFORMAT 
EXTERN void DFWindows8Data(void);
#else
EXTERN void DFDynamicCoordinate(void);
#endif ///< for FEATURE_WIN8_DATAFORMAT

#ifdef FEATURE_DYNAMIC_FREQ_TRAN_MODE_ON
EXTERN void FHDMDFHopDataFormatSend(void);
#endif ///< FEATURE_DYNAMIC_FREQ_TRAN_MODE_ON

EXTERN void DFFocalData(void);

EXTERN void DFMutualScanBase(void);
EXTERN void DFMutualScanDev(void);


#ifdef FEATURE_INIT_SCAN
EXTERN void DFInitScanBase(void);
EXTERN void DFInitScanDev(void);
#endif ///< for FEATURE_INIT_SCAN

EXTERN void DFKeyMutualScanBase(void);
EXTERN void DFKeyMutualScanDev(void);

EXTERN void DFKeyData(void);

EXTERN void DFCheckSumData(void);
#ifdef FEATURE_MUTUAL_DEV_SHOW_INIT_DEV
EXTERN void CopyInitDevToMutDev(void);
#endif

#ifdef FEATURE_FORCE_TOUCH_SCAN 
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
EXTERN void DFForceScanBase(void);
EXTERN void DFForceScanDev(void);
	#endif
#endif

#ifdef FEATURE_PRESS_TOUCH 
EXTERN void DFForceC1C2AdBaseSend(void);
EXTERN void DFForceC1C2ScanBase(void);
#endif

///-------------------------------------------------------------------------------///
/// 12. Timer
///-------------------------------------------------------------------------------///
EXTERN void TimerIsr();
EXTERN void TimerInit(WORD wTimerPeriod);
EXTERN void TimerSetup(BYTE bImmediately, WORD wTimerPeriod);
EXTERN void CounterInit(WORD wTimerPeriod);
///-------------------------------------------------------------------------------///
/// 13. Trace Control Function
///-------------------------------------------------------------------------------///
EXTERN void TSTraceToGnd(BYTE bTableIdx);
EXTERN void TSTraceToAdc(BYTE bTableIdx);
EXTERN BYTE TSTraceTableIdxGet(BYTE bTraceId);
EXTERN void TSTraceToPosWave(BYTE bTableIdx);
EXTERN inline void TSTraceToDrive(BYTE bTableIdx, BYTE bWave);

EXTERN void TSTraceAllSet(BYTE bMode);
EXTERN void TSTraceInit(void);
EXTERN void TSSenseAllTraceModeSet(BYTE bMode ,BYTE bApplyMode);
EXTERN void TSSenseGroupTraceModeSet(BYTE bSenseGroupId, BYTE bMode , BYTE bApplyMode);
EXTERN void TSSenseGroupTraceToGnd(BYTE bSenseGroupId);
EXTERN void TSSenseGroupTraceToAdc(BYTE bGroupId ,BYTE bApplyMode);
EXTERN void TSKeySenseGroupTraceToAdc(void);
EXTERN void TSTraceModeSet(BYTE iTableIdx, BYTE bMode);

#ifdef FEATURE_INIT_REGION_SCAN
EXTERN void TSSenseAllTracePNModeSet(BYTE bRound);
EXTERN SBYTE const code RegionDriveTable[TABLE_DEFINE_REGION_ROW][MAX_REGION_ROUND];
#endif
#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
EXTERN void TSForceTouchTraceInit();	
EXTERN void TSForceTraceAllSet(BYTE bMode);
	#endif
#endif

EXTERN void TSDriveGroupTraceToGnd(BYTE bDriveGroupId , BYTE bApplyMode);
EXTERN void TSDriveGroupTraceToAdc(BYTE bDriveGroupId);

EXTERN void TSDriveAllTraceModeSet(BYTE bMode);
EXTERN void TSDriveGroupTraceModeSet(BYTE bGroupId, BYTE bMode);
EXTERN void TSDriveGroupTraceModeSet(BYTE bDriveGroupId, BYTE bMode);

EXTERN void TSAllTraceToGnd(void);
EXTERN void TSDriveGroupTraceToDrive(BYTE bDriveRegionId , BYTE bApplyMode);
#ifdef FEATURE_NOISE_DETECTION_MODE
EXTERN void TaskNoiseDetection(void);
#endif

///-------------------------------------------------------------------------------///
/// 14. Coordinate Related
///-------------------------------------------------------------------------------///
EXTERN void CoorRawPointAdd(BYTE id, I2 x, I2 y);
EXTERN void CoorRawPointGet(BYTE id, int idx, PointType *point);
EXTERN void CoorExePointAdd(BYTE id, I2 x, I2 y);
EXTERN void CoorExePointGet(BYTE id, int idx, PointType *point);
#ifdef FEATURE_IIR_FILTER_SMOOTHING_SCALING
EXTERN void CoorExePointRemainderGet(BYTE id, Point16Type *point);
EXTERN void CoorExePointRemainderAdd(BYTE id, U2 x, U2 y);
#endif

EXTERN void CoorPointInit(BYTE id, I2 x, I2 y);

EXTERN void CoorSmoothing(BYTE id);
#ifdef FEATURE_COORD_EDGE_POSITION_LOCK
EXTERN void CoordEdgeLimiter(WORD wCoord , BYTE idx , BYTE bAxis);
#endif ///< for FEATURE_COORD_EDGE_POSITION_LOCK

#if defined(FEATURE_COOR_EXTEND_BASE_ON_DRIVE_TRACE) || defined(FEATURE_COOR_SHIFT_BASE_ON_SENSE_TRACE)
EXTERN BYTE CoordMapToTraceChannel(WORD wCoord , BYTE bAxis);
#endif

#ifdef FEATURE_COOR_EXTEND_BASE_ON_DRIVE_TRACE
EXTERN int CoordExtendShift(int iCoord ,  BYTE bAxis);
#endif ///< for FEATURE_COORD_EDGE_POSITION_LOCK

#ifdef FEATURE_COOR_SHIFT_BASE_ON_SENSE_TRACE
EXTERN int CoordAxisShift(int iCoordRaw , int iCoordRef ,  BYTE bAxis);
#endif

EXTERN void DeltaDistanceGet(BYTE id, int idx, WORD *wDist);
EXTERN void DeltaDistanceAdd(BYTE id, WORD wDist);


///-------------------------------------------------------------------------------///	
/// 2. Frequecny Hopping at Boot-Up
///-------------------------------------------------------------------------------///  
#ifdef FEATURE_TRIM_FREQ_HOP 
EXTERN void MSHopDataInitialization(void);
EXTERN void TaskBootUpFrequencyHopping(void);
//EXTERN SBYTE const code FrequencyTrimSet[];
#endif ///< for FEATURE_TRIM_FREQ_HOP

#ifdef FEATURE_DYNAMIC_FREQ_HOP
EXTERN void TaskDynamicFrequencyHop(void);
EXTERN void DynamicFreqSetInitialization(void);
EXTERN void DynamicRecentScanDataRecovery(void);
EXTERN void DynamicHopNewFrequency(BYTE bNewID);
#endif ///< for FEATURE_DYNAMIC_FREQ_HOP

#ifdef FEATURE_HW_FREQUENCY_HOP
EXTERN void MSHopDataInit(void);

#ifdef FEATURE_BOOT_FREQUENCY_HOP
EXTERN void TaskBootUpFrequencyHop(void);
#endif
#ifdef FEATURE_DYNAMIC_FREQUENCY_HOP 
EXTERN void TaskDynamicUpFrequencyHop(void);
EXTERN void DynamicRecentScanDataRecovery(void);
EXTERN void MSHopSetMinNoiseToneID(void);

#endif

#endif

#ifdef FEATURE_LINEARITY_COMPENSATION
#ifdef FEATURE_LINEARITY_COMPENSATION_16TIMES
EXTERN int ALLinearCompensation(int iCoordinate16, WORD wAxisInterpolation16, BYTE SenseOrDrive);
#else
EXTERN int ALLinearCompensation(int iCoordinate, WORD wAxisInterpolation16);
#endif
#endif

#ifdef FEATURE_GIO_ENABLE
EXTERN void GpioDataOut(BYTE bData);
EXTERN void GpioDataOut16(WORD dData);
EXTERN void GpioDataOut32(DWORD dData);
EXTERN void GpioDataOut64(QWORD qData);

#endif

#ifdef FEATURE_CUSTOMER_PROTOCOL
EXTERN void CustomerDataFormat(void);
EXTERN void I2CDispatchCustomerCmd(void);
EXTERN void CustomerResponseArray(BYTE bTmpBuf[], WORD wI2cTxLen, BYTE bResetRxTxIdx);
EXTERN void CustomerInit(void);
EXTERN void CustomerTxIsrINTControl(void);
#endif

#ifdef FORCE_SENSOR_PROTOCOL	 
EXTERN void CustomerForceSensorDataFormat(void);
EXTERN void I2CDispatchCustomerForceSensorCmd(void);
EXTERN BYTE RemapADCOrder(BYTE i,BYTE j);
EXTERN void CustomerForceSensorInit(void);

#endif	

#ifdef FEATURE_HOVER
EXTERN void ALPHover(void);
#endif

#ifdef FEATURE_RAW_DEV_IMPORT
EXTERN void ImportDevData(void);
#endif

#endif ///< __FUNC_DEF__

