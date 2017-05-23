/**
 * @file VarDef.h
 *
 *  VarDef.h define the global variables
 *
 *
 * @version $Revision: 31 $
 * @author JLJuang <JL.Juang@zeitecsemi.com>
 * @note Copyright (c) 2010, Zeitec Semiconductor Ltd., all rights reserved.
 * @note
*/

#ifndef __VARDEF_H__
#define __VARDEF_H__

#include "ZetDEF.h"


///-------------------------------------------------------------------------------///
///  Register Declaration
///-------------------------------------------------------------------------------///
#define EXTERN extern

EXTERN int volatile BreakPoint;
EXTERN REGISTERS RegTrnumType  __attribute__((section(".RegTrumA")))   RegTrumA;   ///< _at_ 0x194004
EXTERN REGISTERS RegTrnumType  __attribute__((section(".RegTrumB")))   RegTrumB;   ///< _at_ 0x194024

#ifndef FEATURE_MCU_LIB_ENABLE
EXTERN REGISTERS GpioType RegGpio  __attribute__((section(".REG_GPIO")));        ///< _at_ 0x18C040
#endif

///-------------------------------------------------------------------------------///
///  Data flash SubClass #7 => MutualDriPtr
///-------------------------------------------------------------------------------///
//EXTERN GlobalVarType volatile xdata __attribute__((section(".MEM_ZETVAR"))) ZetVar ;
EXTERN GlobalVarType volatile xdata  ZetVar ;

#ifdef FEATURE_CUSTOMER_PROTOCOL
EXTERN CustomerVarType volatile xdata CustomerVar;
#ifdef FORCE_SENSOR_PROTOCOL
EXTERN CustomerForceSensorVarType  volatile xdata CustomerForceSensorVar;
#endif

#endif

#ifdef REPORT_GESTURE_POINTS_LOG_METHOD
EXTERN  BYTE volatile  xdata bGesturePointBuffer[600];
EXTERN  BYTE volatile xdata bGesturePointState;
EXTERN  BYTE volatile xdata bGesturePointBufferIdx;
EXTERN  BYTE volatile xdata bFrameCnt;
EXTERN  BYTE volatile xdata bNonTouchCnt;
EXTERN  BYTE volatile xdata bCmdD3Cnt;
EXTERN  BYTE volatile xdata bINTKeepLowFlag;

EXTERN  BYTE volatile xdata bDoubleClickState;

EXTERN WORD volatile xdata  wReferPointPosX;
EXTERN WORD volatile xdata  wReferPointPosY;

#endif


#ifdef FEATRUE_MCU_IDLE_IN_WAITFORSCAN
EXTERN BYTE volatile xdata bWaitForScanFlag; // 1: start to wait, 0:leave waiting
EXTERN BYTE volatile xdata bPCONIDLEFlag;
EXTERN BYTE volatile xdata bADCTimerFlag;
EXTERN BYTE volatile xdata bTimerOneShotFlag;
EXTERN DWORD volatile xdata dwTmp_TMR1;
#endif

EXTERN GlobalVarParaType volatile xdata  __attribute__((section(".MEM_ZETVARPARA"))) ZetVarPara;

EXTERN GlobalDFVarType const code  ZetDF;
EXTERN BYTE volatile xdata *pGenBuf;
EXTERN BYTE volatile xdata *pGenBuf1;
//EXTERN BYTE volatile xdata ZetAlgoPage[DF_PAGE_SIZE];

EXTERN MutualScanDevDataType volatile xdata  *AlgorithmDataPtr;
EXTERN MutualScanDevDataType volatile xdata  *ScanLatchDataPtr;

#ifdef FEATURE_FORCE_TOUCH_SCAN
	#ifdef FEATURE_FAKE_FORCE_TOUCH

	#else
EXTERN MutualScanDevDataType volatile xdata  *ForceAlgorithmDataPtr;
EXTERN MutualScanDevDataType volatile xdata  *ForceScanLatchDataPtr;
	#endif // FEATURE_FAKE_FORCE_TOUCH
#endif

///---------------------------------------------------------------------------///
/// Mutual ADC Data Pointer
///---------------------------------------------------------------------------///
EXTERN RegTrnumType volatile xdata *Trum[2];

///---------------------------------------------------------------------------///
/// Distance Calculation
///---------------------------------------------------------------------------///
EXTERN WORD volatile data wNowCoordinateX;
EXTERN WORD volatile data wNowCoordinateY;
EXTERN WORD volatile data wLastCoordinateX;
EXTERN WORD volatile data wLastCoordinateY;

///---------------------------------------------------------------------------///
/// Main Loop Control
///---------------------------------------------------------------------------///
EXTERN WORD volatile data LoopIdx;

///---------------------------------------------------------------------------///
/// ZET7100 INT pin
///---------------------------------------------------------------------------///
EXTERN BYTE volatile xdata INTPortReg;
EXTERN BYTE volatile xdata INTPinBit; 

///---------------------------------------------------------------------------///
/// Finger Search Algorithm
///---------------------------------------------------------------------------///

///---------------------------------------------------------------------------///
/// Project Code
///---------------------------------------------------------------------------///
EXTERN BYTE const code RomProject[4];

///---------------------------------------------------------------------------///
/// DEV Collect
///---------------------------------------------------------------------------///
#ifdef FEATURE_DEV_COLLECT
EXTERN BYTE volatile data DevCollectMode;
EXTERN BYTE volatile xdata bDevCount;
///EXTERN WORD volatile xdata DevSum[MAX_SENSE_TRACE_NUM + 2];
///EXTERN BYTE volatile xdata DevMax[MAX_SENSE_TRACE_NUM + 2];
///EXTERN BYTE volatile xdata DevMax2[MAX_SENSE_TRACE_NUM + 2];
///EXTERN BYTE volatile xdata DevMin[MAX_SENSE_TRACE_NUM + 2];
EXTERN BYTE volatile data DevCollectCount;
EXTERN BYTE volatile data DevCollect2Pow;
#endif ///< for DEV_COLLECT

#ifdef FEATURE_INIT_REGION_SCAN  
EXTERN int data RegionAdcData[TABLE_DEFINE_REGION_ROW][MAX_TRACE_NUM];
#endif


///---------------------------------------------------------------------------///
/// Noise Rejection Function
///---------------------------------------------------------------------------///
#ifdef FEATURE_NOISE_REJECTION
EXTERN WORD volatile data wNoiseMax;
#endif



/// ******** MAIN CODE  VARIABLE DEFINITION  ******* ////
#endif ///< __VARDEF_H__


