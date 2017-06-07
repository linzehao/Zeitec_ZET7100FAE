/**
 * @file Customer.c
 *
 *  Customer Function
 *
 *
 * @version $Revision$
 * @author Maple Huang <maple.huang@zeitecsemi.com>
 * @note Copyright (c) 2017, Zeitec Semiconductor Ltd., all rights reserved.
 * @note
*/

#include "ZetDef.h"

#ifdef FEATURE_CUSTOMER_PROTOCOL

CustomerVarType volatile xdata CustomerVar;

#ifdef NEW_I2C_PARSING_FLOW
void CustomerDataFormat(void)
{
 //Fill coordinate information to Double buffer
	BYTE data i;
	BYTE data bPacketNumber = 0;
	BYTE data bCNT;
	BYTE data bFingerNum;
	WORD data wValidPoint,w1,w2;
	WORD data wPosX;
	WORD data wPosY;
	PointType  xdata ptLastExePoint;

	//if(ZetVar.bWorkingState==WORKING_STATE_ZET_CMD_STATE)
	if(!(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL||ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_INITIAL))
	{
		return;
	}
	bFingerNum = ZetDF.cFormatCtrl.scDataCtrl.bFingerNum;
	bCNT=0;
	wValidPoint=0;
	
  if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL)
	{
	  for(i=0;i<bFingerNum; i++)
		{
			if(ZetVar.FingerCoordinateRecord[i].bFingerDown == FINGER_DOWN)
			{
				bCNT++;
				w1 = 0x0001<< i;
				w2 = (((w1<<8)&0xff00)| ((w1>>8)&0x00ff));
				wValidPoint |= w2;
			}
		} 			

		if(wValidPoint > 0)
		{
			ZetVar.wSysMode2 |= SYS_MODE2_ANY_FINGER_DOWN;

			ZetVar.wGreenModeCounter = 0;
		  if(ZetVar.wSysMode2 & SYS_MODE2_GREEN_MODE)
	    {
	  		ZetVar.wSysMode2 &= ~SYS_MODE2_GREEN_MODE;
				ZetVar.bTimerCounter = ZetDF.cAlgoPage.scAlgoPowerSave.bGreenModeDebounce;
	    }
	    if(!(ZetVar.bTimerStatus & TIMER_TO_NORMAL))
	    {
				ZetVar.bTimerStatus = (TIMER_TO_NORMAL  | TIMER_RELOAD_FLAG);
	    }

			if(ZetVar.bTimerCounter > 0)
			{
				ZetVar.bTimerCounter --;
			}
		}
		else
		{
			ZetVar.wSysMode2 &= ~SYS_MODE2_ANY_FINGER_DOWN;
		} 

	  CustomerVar.bCustomerReportFingerCNT=bCNT;		
		bPacketNumber=0;		

	  CustomerVar.bDoubleBufferStoreIdx=((CustomerVar.bDoubleBufferStoreIdx+1)%2);
		CustomerVar.bcntBuffer[CustomerVar.bDoubleBufferStoreIdx][0]=0;
		CustomerVar.bcntBuffer[CustomerVar.bDoubleBufferStoreIdx][1]=0;
		
		if(CustomerVar.bCustomerLastReportFingerCNT>0||bCNT>0)
		{	
			w1=(((wValidPoint<<8)&0xff00)| ((wValidPoint>>8)&0x00ff));
	    for(i=0;i<bFingerNum; i++)
			{		         
				w2=(w1>>i)& 0x0001;
				if(w2==0x0001)	
				{
					//also need to check Coord. changed!
					CoorExePointGet(i, COOR_EXE_IDX_LAST2, &ptLastExePoint); 		 
					if(ZetDF.cFormatCtrl.scDataCtrl.bXYCoorExchange == TRUE)
					{
						wPosX = ZetVar.FingerCoordinateRecord[i].ptCoordinate.y;
						wPosY = ZetVar.FingerCoordinateRecord[i].ptCoordinate.x;
					}
					else
					{
						wPosX = ZetVar.FingerCoordinateRecord[i].ptCoordinate.x;
						wPosY = ZetVar.FingerCoordinateRecord[i].ptCoordinate.y;
					}

					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][0+bPacketNumber*8]=0x01;
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][1+bPacketNumber*8]=(BYTE)(wPosX&0x00FF); 
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][2+bPacketNumber*8]=(BYTE)((wPosX>>8)&0x00FF); 
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][3+bPacketNumber*8]=(BYTE)(wPosY&0x00FF);
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][4+bPacketNumber*8]=(BYTE)((wPosY>>8)&0x00FF);
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][5+bPacketNumber*8]= 0x2d; //0x11;//CustomerVar.bDebugBuf[6]; //0x3D; //0x3E; 								 
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][6+bPacketNumber*8]= 0x04; //0x04; //CustomerVar.bDebugBuf[7]; // 0x07;  //0x04;	
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][7+bPacketNumber*8]= 0x03;

					if(CustomerVar.bCustomReportCnt!=0xFF) 
					{
						CustomerVar.bCustomReportCnt++;
					}	
					else 
					{
						CustomerVar.bCustomReportCnt=0;
					}	
					bPacketNumber++;
				}

				if(w2==0x0000)
				{
	        CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][0+bPacketNumber*8]=0x00;  
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][1+bPacketNumber*8]=0x00; 
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][2+bPacketNumber*8]=0x00; 
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][3+bPacketNumber*8]=0x00;
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][4+bPacketNumber*8]=0x00;
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][5+bPacketNumber*8]= 0x00; 
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][6+bPacketNumber*8]= 0x00; 
					CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferStoreIdx][7+bPacketNumber*8]= 0x00;	
					if(CustomerVar.bCustomReportCnt!=0xFF) 
					{
						CustomerVar.bCustomReportCnt++;
					}	
					else 
					{
						CustomerVar.bCustomReportCnt=0;
					}	
					bPacketNumber++;						
				}				
			}        
			    
			//CustomerVar.bcntBuffer[0]=HIBYTE(wValidPoint);
			//CustomerVar.bcntBuffer[1]=LOBYTE(wValidPoint);
      CustomerVar.bcntBuffer[CustomerVar.bDoubleBufferStoreIdx][0]=HIBYTE(wValidPoint);
			CustomerVar.bcntBuffer[CustomerVar.bDoubleBufferStoreIdx][1]=LOBYTE(wValidPoint);
			
	 		if(bPacketNumber!=0) //no point moving or just touch or finger-up
	 		{
	 			CustomerVar.bINTtriggerCnt=0; //force to trigger INT Low
			 	CustomerVar.bCustomerReSendCNT=CUSTOMER_RESNED_NUM; //resend n times
	 		}
		}

		 CustomerVar.wCustomerLastValidPoint=wValidPoint;
		 CustomerVar.bCustomerLastReportFingerCNT=bCNT;			 
	   if(CustomerVar.bCustomerReSendCNT>0) 
	   {
		   CustomerVar.bCustomerReSendCNT--;
	   }
		 
     if(CustomerVar.bCustomerReSendCNT!=0)    
     {
   		CustomerVar.bINTtriggerCnt=0; //force to trigger INT Low					     
     }
	//	CustomerVar.bDebugBuf[2] = bPacketNumber;
	//	CustomerVar.bDebugBuf[3] = CustomerVar.bcntBuffer[CustomerVar.bDoubleBufferStoreIdx][0];	
	} 

	CustomerVar.bDoubleBufferSendIdx=CustomerVar.bDoubleBufferStoreIdx;

	if(CustomerVar.bINTtriggerCnt==0)   
	{       
		if(I2C_INT()==TRUE) 
		{		
			I2C_INT_LOW(); 
		}			
		CustomerVar.bINTtriggerCnt=0xFF; //Max value means disable    
	} 	
	else if(CustomerVar.bINTtriggerCnt!=0xFF&&CustomerVar.bINTtriggerCnt>0)  
	{
		CustomerVar.bINTtriggerCnt--;  
	}
}


void CustomerInit(void)
{  
	BYTE data i = 0;
	for(i = 0; i < 8 ; i++)
	{
		CustomerVar.bCustomerBuf[i]=0x00;
		CustomerVar.bDebugBuf[i]=0;
		CustomerVar.bLastCustomCmdBuf[i]=0;
	}

	CustomerVar.bLastCustomCmdBuf[7]=0xFF; //0;

	//CustomerVar.bWorkingState=ZetDF.cFormatCtrl.scDataCtrl.bDefaultProtocolVendor;
	//CustomerVar.bWorkingSubState=WORKING_STATE_CUSTOMER_INITIAL;

	CustomerVar.bCustomCmd0000Cnt=0;
	//CustomerVar.bCustomCmd0102Cnt=0;
	CustomerVar.bCustomCmd0102Cnt=1;
	CustomerVar.bCustomCmd5801Cnt=0;
	CustomerVar.bCustomCmd5901Cnt=0;
	CustomerVar.bCustomCmd6501Cnt=0;
	CustomerVar.bCustomCmd6801Cnt=0;
	CustomerVar.bCustomCmd03Cnt=0;
	CustomerVar.bCustomCmd00eeCnt=0;
	CustomerVar.bCustomCmd05Cnt=0;
	CustomerVar.bCustomCmd04Cnt=0;
	CustomerVar.bCustomCmd1eCnt = 0;
	CustomerVar.bCustomCmd0eCnt=0;
	//CustomerVar.bCustomCmdD801Cnt=0;
	CustomerVar.bCustomCmd6801nnCnt=0;

	//CustomerVar.bCustomCmdE201Cnt=0;
	CustomerVar.bCustomReportCnt=0;

	CustomerVar.bWakeUpFlag=0;

	CustomerVar.bCustomCmd5901WakeupCnt=0;

	CustomerVar.bI2CKeepSendflag=0;
	//CustomerVar.bINTtriggerCnt=0xFF;
	//trigger to INT LOW at initial stage
	//fine-tune INT LOW timing....
	//CustomerVar.bINTtriggerCnt=12;
	CustomerVar.bINTtriggerCnt=0;

	//CustomerVar.bCustomerReSendCNT=10;
	CustomerVar.bCustomerReSendCNT=0;
	CustomerVar.bCustomerKeyReportFlag=0;
	CustomerVar.bCustomerKeyValidByte=0;

	CustomerVar.bCustomerUpgradeFlag=0;

	CustomerVar.bCustomerReportFingerCNT=0;
	CustomerVar.bCustomerLastReportFingerCNT=0;
	CustomerVar.wCustomerLastValidPoint=0;

	CustomerVar.bTimerINTtrigger=0;
	 
	// CustomerVar.bDoubleBufferIdx=0;
	CustomerVar.bDoubleBufferStoreIdx=0;
	CustomerVar.bDoubleBufferSendIdx=0;
}

#else
void CustomerDataFormat(void)
{
 //Fill coordinate information to Double buffer
	BYTE data i;
	BYTE data bPacketNumber;
	BYTE data bCNT;
	BYTE data bFingerNum;
	BYTE data bTmpIndex;
	WORD data wValidPoint;
	WORD data wPosX;
	WORD data wPosY;
	PointType xdata ptLastExePoint;
	
	//if(ZetVar.bWorkingState==WORKING_STATE_ZET_CMD_STATE)
	if(!(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL||ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_INITIAL))
	{
		return;
	}	 
	bFingerNum = ZetDF.cFormatCtrl.scDataCtrl.bFingerNum; 

	bCNT=0;
	wValidPoint=0;			

  if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL)
	{	   
		//filled in next buffer
		bTmpIndex=(CustomerVar.bDoubleBufferIdx+1)%2;
		//bTmpIndex=0;
		for(i=0;i<bFingerNum; i++) 
		{ 						 	
			if(ZetVar.FingerCoordinateRecord[i].bFingerDown == FINGER_DOWN)									  
			{
					bCNT++; 	
					//MSB is 1st bit => Point 0 (i)
					wValidPoint |= (0x0001L<<(15-i)); 			
			}
		} 						 

		CustomerVar.bCustomerReportFingerCNT=bCNT;		
		bPacketNumber=0;				 
		if(bCNT!=CustomerVar.bCustomerLastReportFingerCNT) //finger number change!!!
		{															
			CustomerVar.bDoubleBuffer[bTmpIndex][1+0*9]=0x17;
			if(bCNT==0) 
			{										 
				 CustomerVar.bDoubleBuffer[bTmpIndex][2+0*9]=0x00;  //All finger-up ==> No touch 
				 CustomerVar.bDoubleBuffer[bTmpIndex][3+0*9]=0x00;
			}
			else
			{
				 CustomerVar.bDoubleBuffer[bTmpIndex][2+0*9]=0x80; //finger number change
				 CustomerVar.bDoubleBuffer[bTmpIndex][3+0*9]=bCNT; 									 
			}

			CustomerVar.bDoubleBuffer[bTmpIndex][4+0*9]=0x00;
			CustomerVar.bDoubleBuffer[bTmpIndex][5+0*9]=0x00;
			CustomerVar.bDoubleBuffer[bTmpIndex][6+0*9]=0x00;
			CustomerVar.bDoubleBuffer[bTmpIndex][7+0*9]=0x00;
			CustomerVar.bDoubleBuffer[bTmpIndex][8+0*9]=0x00;
			CustomerVar.bDoubleBuffer[bTmpIndex][9+0*9]=0x00;
			bPacketNumber++;
		}

		if(CustomerVar.bCustomerLastReportFingerCNT>0||bCNT>0)
		{	
			// bTmpIndex=0; // implement single buffer first!!
			BYTE bFakeArea[15]=    {0x04,0x05,0x05,0x04,0x08,0x07,0x06,0x07,0x09,0x0A,0x07,0x06,0x07,0x06,0x06};
			BYTE bFakePressure[15]={0x23,0x23,0x23,0x23,0x33,0x33,0x33,0x43,0x43,0x43,0x43,0x43,0x33,0x33,0x33};

			for(i=0;i<bFingerNum; i++)
			{		         
				if((((wValidPoint>>(15-i))&0x01)==0x01)||(((CustomerVar.wCustomerLastValidPoint>>(15-i))&0x01)==0x01))
				{		   
				    CustomerVar.bDoubleBuffer[bTmpIndex][1+bPacketNumber*9]=0x19+i;
				    //0x90 unchange coordinate, 0x91 moving, 0x94 just touch(contact), 0x15 finger-up
				    if((((CustomerVar.wCustomerLastValidPoint>>(15-i))&0x01)==0x00) && (((wValidPoint>>(15-i))&0x01)==0x01))
				   	{  
				   	   CustomerVar.bDoubleBuffer[bTmpIndex][2+bPacketNumber*9]=0x94;  
				    }
						else if((((CustomerVar.wCustomerLastValidPoint>>(15-i))&0x01)==0x01) && (((wValidPoint>>(15-i))&0x01)==0x00))
						{
				       CustomerVar.bDoubleBuffer[bTmpIndex][2+bPacketNumber*9]=0x15;  
						}
						else
						{
							//also need to check Coord. changed!
							CoorExePointGet(i, COOR_EXE_IDX_LAST2, &ptLastExePoint);
							if(ZetVar.FingerCoordinateRecord[i].ptCoordinate.x !=ptLastExePoint.x || \
							ZetVar.FingerCoordinateRecord[i].ptCoordinate.y !=ptLastExePoint.y)
							{
								CustomerVar.bDoubleBuffer[bTmpIndex][2+bPacketNumber*9]=0x91;  
							}
							else
							{
								CustomerVar.bDoubleBuffer[bTmpIndex][2+bPacketNumber*9]=0x90;
								//ignore same position, don't increase bPacketNumber...                             
								// continue;														 
							}
						}

				    if(ZetDF.cFormatCtrl.scDataCtrl.bXYCoorExchange == TRUE)
						{
							wPosX = ZetVar.FingerCoordinateRecord[i].ptCoordinate.y;
							wPosY = ZetVar.FingerCoordinateRecord[i].ptCoordinate.x;
						}
						else
						{
							wPosX = ZetVar.FingerCoordinateRecord[i].ptCoordinate.x;
							wPosY = ZetVar.FingerCoordinateRecord[i].ptCoordinate.y;
						}
						
				   	CustomerVar.bDoubleBuffer[bTmpIndex][3+bPacketNumber*9]=(BYTE)(wPosX&0x00FF); 
				  	CustomerVar.bDoubleBuffer[bTmpIndex][4+bPacketNumber*9]=(BYTE)(wPosX>>8); 
				 		CustomerVar.bDoubleBuffer[bTmpIndex][5+bPacketNumber*9]=(BYTE)(wPosY&0x00FF);
				 		CustomerVar.bDoubleBuffer[bTmpIndex][6+bPacketNumber*9]=(BYTE)(wPosY>>8); 
				 		CustomerVar.bDoubleBuffer[bTmpIndex][7+bPacketNumber*9]= bFakePressure[CustomerVar.bCustomReportCnt%15]; //0x11;//CustomerVar.bDebugBuf[6]; //0x3D; //0x3E;                  
						CustomerVar.bDoubleBuffer[bTmpIndex][8+bPacketNumber*9]= bFakeArea[CustomerVar.bCustomReportCnt%15]; //0x04; //CustomerVar.bDebugBuf[7]; // 0x07;	//0x04;  
				    if(CustomerVar.bCustomReportCnt!=0xFF) 
						{
							CustomerVar.bCustomReportCnt++;
						}
						else  
						{
							CustomerVar.bCustomReportCnt=0;
						}

						CustomerVar.bDoubleBuffer[bTmpIndex][9+bPacketNumber*9]= 0x00;  //0x00;
				 		bPacketNumber++;		
				}
			}        
			    
			CustomerVar.bDoubleBuffer[bTmpIndex][0]=bPacketNumber;  //total packet size(58 01 & 59 01 content): 1+9*j
			if(bPacketNumber!=0) //no point moving or just touch or finger-up
			{
					CustomerVar.bINTtriggerCnt=0; //force to trigger INT Low
					CustomerVar.bCustomerReSendCNT=CUSTOMER_RESNED_NUM; //resend n times
			}
		}

		CustomerVar.wCustomerLastValidPoint=wValidPoint;
		CustomerVar.bCustomerLastReportFingerCNT=bCNT;			 

		//move to 58 01 handle
		if(CustomerVar.bCustomerReSendCNT>0) 
		{
			CustomerVar.bCustomerReSendCNT--;
		}
		if(CustomerVar.bCustomerReSendCNT!=0)    
		{
			CustomerVar.bINTtriggerCnt=0; //force to trigger INT Low					     
		}			

		if(bCNT==0 && CustomerVar.bCustomerLastReportFingerCNT==0 && CustomerVar.bCustomerReSendCNT==0)
		{
    	CustomerVar.bDoubleBuffer[bTmpIndex][0]=0;  //let 58 01 handle to know no point report needed		
		}

		#if defined(FEATURE_REAL_KEY) || defined(FEATURE_VIRTUAL_KEY)					
    //handle Key, Key is pressed or just released, trigger a INT LOW
		//CustomerVar.bCustomerKeyReportFlag=0; //clear after I2C send to host
		if(ZetVar.KeyCtrl.bKeyValidByte||ZetVar.bKeyLastStatus)
		{
		   if(ZetVar.KeyCtrl.bKeyValidByte!=ZetVar.bKeyLastStatus)
		   {
				  CustomerVar.bCustomerKeyReportFlag[CustomerVar.bDoubleBufferIdx]=1;
					CustomerVar.bCustomerKeyValidByte[CustomerVar.bDoubleBufferIdx]=ZetVar.KeyCtrl.bKeyValidByte;   											
				  CustomerVar.bINTtriggerCnt=0; //force to trigger INT Low					
		   }
		}					
    #endif		

		//change index after filled the next buffer
		 CustomerVar.bDoubleBufferIdx=bTmpIndex;
	}

  if(CustomerVar.bINTtriggerCnt==0)
  {
    if(I2C_INT()==TRUE) 
		{
			I2C_INT_LOW();
    }
		
		CustomerVar.bINTtriggerCnt=0xFF; //Max value means disable
  }
  else if(CustomerVar.bINTtriggerCnt!=0xFF&&CustomerVar.bINTtriggerCnt>0)
  {
  	CustomerVar.bINTtriggerCnt--;
  }
}

void CustomerInit(void)
{  
	BYTE data i;
	for(i = 0; i < 8 ; i++)
	{
		CustomerVar.bCustomerBuf[i] = 0x00;
		CustomerVar.bDebugBuf[i] = 0;
		CustomerVar.bLastCustomCmdBuf[i] = 0;
	}
	CustomerVar.bLastCustomCmdBuf[7]=0xFF; //0;

	CustomerVar.bWorkingSubState=WORKING_SUBSTATE_CUSTOMER_INITIAL_0;

	CustomerVar.bCustomCmd0000Cnt=0;
	//CustomerVar.bCustomCmd0102Cnt=0;
	CustomerVar.bCustomCmd0102Cnt=1;
	CustomerVar.bCustomCmd5801Cnt=0;
	CustomerVar.bCustomCmd5901Cnt=0;
	CustomerVar.bCustomCmd6501Cnt=0;
	CustomerVar.bCustomCmd6801Cnt=0;
	//CustomerVar.bCustomCmdD801Cnt=0;
	CustomerVar.bCustomCmd6801nnCnt=0;

	//CustomerVar.bCustomCmdE201Cnt=0;
	CustomerVar.bCustomReportCnt=0;

	CustomerVar.bWakeUpFlag=0;

	CustomerVar.bCustomCmd5901WakeupCnt=0;

	CustomerVar.bI2CKeepSendflag=0;
	CustomerVar.bINTtriggerCnt=0xFF;
	//trigger to INT LOW at initial stage
	//fine-tune INT LOW timing....
	//CustomerVar.bINTtriggerCnt=12;
	CustomerVar.bINTtriggerCnt=0;

	//CustomerVar.bCustomerReSendCNT=10;
	CustomerVar.bCustomerReSendCNT=0;
	CustomerVar.bCustomerKeyReportFlag[0]=0;
	CustomerVar.bCustomerKeyReportFlag[1]=0;
	CustomerVar.bCustomerKeyValidByte[0]=0;
	CustomerVar.bCustomerKeyValidByte[1]=0;

	CustomerVar.bCustomerUpgradeFlag=0;

	CustomerVar.bCustomerReportFingerCNT=0;
	CustomerVar.bCustomerLastReportFingerCNT=0;
	CustomerVar.wCustomerLastValidPoint=0;

	CustomerVar.bTimerINTtrigger=0; 
	CustomerVar.bDoubleBufferIdx=0;
}
#endif

#ifdef FORCE_SENSOR_PROTOCOL	 
CustomerForceSensorVarType  volatile xdata CustomerForceSensorVar;

void CustomerForceSensorInit()
{   
	CustomerForceSensorVar.bDoubleBufferSendIdx=0;
	CustomerForceSensorVar.bDoubleBufferStoreIdx=0;
	CustomerForceSensorVar.bCmdRemapEnableFlag=1;
	CustomerForceSensorVar.bCmdPatternCheckEnableFlag=0;
	{
		int i,j;
		for(i=0;i<8; i++)
		{
			for(j=0;j<12;j++)
			{
				// CustomerForceSensorVar.wCustomerForceSensorAdBase[bTmpIndex][j+i*12]=LE2BE(20000+(AlgorithmDataPtr->sDev[i+1][j+1]<<2));
				 CustomerForceSensorVar.wCustomerForceSensorAdBase[0][j+i*12]=LE2BE(20000);
				 CustomerForceSensorVar.wCustomerForceSensorAdBase[1][j+i*12]=LE2BE(20000);
			}
		}
	}
}
	 
BYTE RemapADCOrder(BYTE i,BYTE j)
{
  BYTE bRemapIndex;
	bRemapIndex=(j)+i*12;
	return bRemapIndex;
}

void CustomerForceSensorDataFormat()
{
	BYTE data i,j;	 
	BYTE data bTmpIndex;
	BYTE data bRemapIndex;
	WORD data wTmpADC;

	if(ZetVar.bWorkingState!=WORKING_STATE_CUSTOMER_FORCETOUCH)
	{
	 return;
	}

	//remap the dev to customer forceSensor ADBase pool
	CustomerForceSensorVar.bDoubleBufferStoreIdx=((CustomerForceSensorVar.bDoubleBufferStoreIdx+1)%2);
	bTmpIndex = CustomerForceSensorVar.bDoubleBufferStoreIdx;

	for(i=0;i<8; i++)//TP sensor
	{
	  for(j=0;j<12;j++)//TP drive
	  {
	    bRemapIndex=RemapADCOrder(i,j);

	    if(CustomerForceSensorVar.bCmdPatternCheckEnableFlag==1)
	    {
	    	CustomerForceSensorVar.wCustomerForceSensorAdBase[bTmpIndex][bRemapIndex]=LE2BE((WORD)((i<<8)+j));
	    }
			else
			{
			  wTmpADC=20000+(AlgorithmDataPtr->sDev[j+1][i+1]*32);
				CustomerForceSensorVar.wCustomerForceSensorAdBase[bTmpIndex][bRemapIndex]=LE2BE(wTmpADC);
			}
	  }
	}
	CustomerForceSensorVar.bDoubleBufferSendIdx=CustomerForceSensorVar.bDoubleBufferStoreIdx;
}
#endif

#endif // FEATURE_CUSTOMER_PROTOCOL

