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

#ifdef IC_MELFAS
void CustomerDataFormat(void)
{
 //Fill coordinate information to Double buffer
	BYTE data i;
	BYTE data bPacketNumber = 0;
	BYTE data bCNT;
	BYTE data bFingerNum;
	WORD data wValidPoint,w1,w2,w3,w4;
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
			//I2C_INT_HIGH();
			ZetVar.wSysMode2 &= ~SYS_MODE2_ANY_FINGER_DOWN;
		} 

	  	CustomerVar.bCustomerReportFingerCNT=bCNT;		
		bPacketNumber=0;		
		//CustomerVar.bcntBuffer[1]=0;
		if(CustomerVar.bCustomerLastReportFingerCNT>0||bCNT>0)
		{	
			w1=(((wValidPoint<<8)&0xff00)| ((wValidPoint>>8)&0x00ff));
			w3=(((CustomerVar.wCustomerLastValidPoint<<8)&0xff00)| ((CustomerVar.wCustomerLastValidPoint>>8)&0x00ff));
	    	for(i=0;i<bFingerNum; i++)
			{		         
				w2=(w1>>i)& 0x0001;
				w4=(w3>>i)& 0x0001;
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
					 CustomerVar.bcntBuffer[0] = bCNT<<3;
					 CustomerVar.bDoubleBuffer[0+bPacketNumber*8]=0xa1+i;
					 CustomerVar.bDoubleBuffer[1+bPacketNumber*8]=(BYTE)(((wPosY>>8)<<4)|((wPosX>>8)&0x0f));//Yh Xh
					 CustomerVar.bDoubleBuffer[2+bPacketNumber*8]=(BYTE)(wPosX&0x00FF); //xL
					 CustomerVar.bDoubleBuffer[3+bPacketNumber*8]=(BYTE)(wPosY&0x00FF);//yL
					 CustomerVar.bDoubleBuffer[4+bPacketNumber*8]= 0x02;
					 CustomerVar.bDoubleBuffer[5+bPacketNumber*8]= 0x93; 								 
					 CustomerVar.bDoubleBuffer[6+bPacketNumber*8]= 0x07;
					 CustomerVar.bDoubleBuffer[7+bPacketNumber*8]= 0x03; 
					
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
				else if(w2==0x0000)
				{  
					if(w4==0x0001)
					{
					CustomerVar.bDoubleBuffer[0+bPacketNumber*8]= 0x21+i;//0x40|(i+1);
					
					CustomerVar.bDoubleBuffer[4+bPacketNumber*8]= 0x00; 
					CustomerVar.bDoubleBuffer[5+bPacketNumber*8]= 0x00;	
					CustomerVar.bDoubleBuffer[6+bPacketNumber*8]= 0x00;									
					CustomerVar.bDoubleBuffer[7+bPacketNumber*8]= 0x00;				
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
			}        
				
			if(CustomerVar.bCustomerLastReportFingerCNT > bCNT)
			{
				CustomerVar.bcntBuffer[0] = CustomerVar.bCustomerLastReportFingerCNT<<3;
			}        
			    
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
	CustomerVar.bINTtriggerCnt=0xFF;
	CustomerVar.bI2CKeepSendflag=0;
	BYTE a = 0;
	for(a = 0; a < 12; a++)
	{
		CustomerVar.bCustomerBuf[a]=0x00;
	}
	BYTE i = 0;
	for(i = 0; i < 8 ; i++)
	{
		CustomerVar.bCustomerBuf[i]=0x00;
		CustomerVar.bDebugBuf[i]=0;
		CustomerVar.bLastCustomCmdBuf[i]=0;
	}
	CustomerVar.bCustomerReSendCNT=0;
	CustomerVar.bCustomerKeyReportFlag=0;
	CustomerVar.bCustomerKeyValidByte=0;

	CustomerVar.bCustomerReportFingerCNT=0;
	CustomerVar.bCustomerLastReportFingerCNT=0;
	CustomerVar.wCustomerLastValidPoint=0;

	CustomerVar.bTimerINTtrigger=0;
	CustomerVar.bDoubleBufferStoreIdx=0;
	CustomerVar.bDoubleBufferSendIdx=0; 



}
#endif	

#ifdef IC_ST

void CustomerDataFormat(void)
{
 //Fill coordinate information to Double buffer
	BYTE data i;
	BYTE data bPacketNumber = 0;
	BYTE data bCNT;
	BYTE data bFingerNum;
	WORD data wValidPoint,w1,w2,w3,w4;
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
		if(ZetVar.FingerCoordinateRecord[0].wFingerStatus & FINGER_STATUS_HOVER)
		{
			//ZetVar.FingerCoordinateRecord[0].wFingerStatus &= ~FINGER_STATUS_HOVER;
			CustomerVar.bHoverFlag = 1;
		}
		else 
		{
			CustomerVar.bHoverFlag = 0;
		}	
		
		CustomerVar.bcntBuffer[0]=0x00;//bCNT*0x04;//HIBYTE(wValidPoint);
		CustomerVar.bcntBuffer[1]=0x00;//LOBYTE(wValidPoint);
		if(CustomerVar.bCustomerLastReportFingerCNT>0||bCNT>0)
		{	
			w1=(((wValidPoint<<8)&0xff00)| ((wValidPoint>>8)&0x00ff));
			w3=(((CustomerVar.wCustomerLastValidPoint<<8)&0xff00)| ((CustomerVar.wCustomerLastValidPoint>>8)&0x00ff));
	    	for(i=0;i<bFingerNum; i++)
			{		         
				w2=(w1>>i)& 0x0001;
				w4=(w3>>i)& 0x0001;
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
					 CustomerVar.bDoubleBuffer[0+bPacketNumber*8]=(i<<4)|0x05; 
			 		 CustomerVar.bDoubleBuffer[1+bPacketNumber*8]=(BYTE)(wPosX&0xFF);//(bCNT<<4)|0x0c;
			 		 CustomerVar.bDoubleBuffer[2+bPacketNumber*8]=(BYTE)(((wPosY&0x000f)<<4)|((wPosX>>8)&0x0F));
					 CustomerVar.bDoubleBuffer[3+bPacketNumber*8]=(BYTE)((wPosY>>4)&0x00ff);
					 CustomerVar.bDoubleBuffer[4+bPacketNumber*8]=0x06;						 
					 CustomerVar.bDoubleBuffer[5+bPacketNumber*8]=0x02;
					 CustomerVar.bDoubleBuffer[6+bPacketNumber*8]=0x02;
					 CustomerVar.bDoubleBuffer[7+bPacketNumber*8]=0x01;
					 
					 CustomerVar.bHoverBuffer[0]=0x09;
					 CustomerVar.bHoverBuffer[1]=0x00;
    				 CustomerVar.bHoverBuffer[2]=(BYTE)((wPosX>>4)&0x00FF);
					 CustomerVar.bHoverBuffer[3]=(BYTE)((wPosY>>4)&0x00FF);
					 CustomerVar.bHoverBuffer[4]=(BYTE)(((wPosY&0x000F)<<4)|(wPosX&0x000F)); 
					 CustomerVar.bHoverBuffer[5]=ZetVar.ClusterData[0].wClusterMaxPeakDev;
					 //CustomerVar.FingerupINTflag = 1;
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
					if(w4==0x0001)
					{
						CustomerVar.bDoubleBuffer[0+bPacketNumber*8]=(i<<4)|0x04; 
						 CustomerVar.bDoubleBuffer[4+bPacketNumber*8]=0x06;					 
						 CustomerVar.bDoubleBuffer[5+bPacketNumber*8]=0x02;
						 CustomerVar.bDoubleBuffer[6+bPacketNumber*8]=0x02;
						 CustomerVar.bDoubleBuffer[7+bPacketNumber*8]=0x01;
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
			}        
			
      		CustomerVar.bcntBuffer[0]=0x00;//bCNT*0x04;//HIBYTE(wValidPoint);
			CustomerVar.bcntBuffer[1]=bCNT*0x04;//LOBYTE(wValidPoint);
			if(CustomerVar.bCustomerLastReportFingerCNT > bCNT)
			{
				CustomerVar.bcntBuffer[1]=CustomerVar.bCustomerLastReportFingerCNT*0x04;
			}
			
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
	
	CustomerVar.bCustomCmd85Cnt = 1;
	CustomerVar.bCustomCmd86Cnt = 1;
	CustomerVar.bCustomCmdB60045 = 1;
	CustomerVar.FingerupINTflag = 0x00;
	CustomerVar.bHoverFlag = 0;
	CustomerVar.bINTtriggerCnt=0xff;
	//trigger to INT LOW at initial stage
	//fine-tune INT LOW timing....
	//CustomerVar.bINTtriggerCnt=12;
	//CustomerVar.bINTtriggerCnt=0;
	
	BYTE i = 0;
	for(i = 0; i < 8 ; i++)
	{
		CustomerVar.bCustomerBuf[i]=0x00;
		CustomerVar.bHoverBuffer[i]=0x00;
		CustomerVar.bDebugBuf[i]=0;
		CustomerVar.bLastCustomCmdBuf[i]=0;
	}

#ifdef FEATURE_FAKE_FORCE_TOUCH
	for(i=0; i<FINGER_MAX_REPORT; i++)
	{
		CustomerVar.wLastNormalizedSum[i] = 0;
	}
#endif

	CustomerVar.bLastCustomCmdBuf[7]=0xFF; //0;	
	CustomerVar.bCustomReportCnt=0;
	CustomerVar.bWakeUpFlag=0;
	CustomerVar.bI2CKeepSendflag=0;
	

	//CustomerVar.bCustomerReSendCNT=10;
	CustomerVar.bCustomerReSendCNT=0;
	CustomerVar.bCustomerKeyReportFlag=0;
	CustomerVar.bCustomerKeyValidByte=0;

	CustomerVar.bCustomerUpgradeFlag=0;

	CustomerVar.bCustomerReportFingerCNT=0;
	CustomerVar.bCustomerLastReportFingerCNT=0;
	CustomerVar.wCustomerLastValidPoint=0;

	CustomerVar.bTimerINTtrigger=0;

}
#endif	

#ifdef IC_Synopsys

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
		
		CustomerVar.bcntBuffer[0]=0x00;//bCNT*0x04;//HIBYTE(wValidPoint);
		CustomerVar.bcntBuffer[1]=0x00;//LOBYTE(wValidPoint);
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
					 
					 CustomerVar.bDoubleBuffer[0+bPacketNumber*8]=0x01;
					 CustomerVar.bDoubleBuffer[1+bPacketNumber*8]=(BYTE)(wPosX&0x00FF); //x|¡§??¡ìa??
					 CustomerVar.bDoubleBuffer[2+bPacketNumber*8]=(BYTE)((wPosX>>8)&0x00FF); //x????
					 CustomerVar.bDoubleBuffer[3+bPacketNumber*8]=(BYTE)(wPosY&0x00FF);//y|¡§??¡ìa??
					 CustomerVar.bDoubleBuffer[4+bPacketNumber*8]=(BYTE)((wPosY>>8)&0x00FF);//y????
					 CustomerVar.bDoubleBuffer[5+bPacketNumber*8]= 0x2d;							  
					 CustomerVar.bDoubleBuffer[6+bPacketNumber*8]= 0x04; 
					 CustomerVar.bDoubleBuffer[7+bPacketNumber*8]= CustomerVar.bGestureId;//0x03; 
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
					CustomerVar.bDoubleBuffer[0+bPacketNumber*8]=0x00;  
					CustomerVar.bDoubleBuffer[1+bPacketNumber*8]=0x00; //x|¡§??¡ìa??
					CustomerVar.bDoubleBuffer[2+bPacketNumber*8]=0x00; //x????
					CustomerVar.bDoubleBuffer[3+bPacketNumber*8]=0x00;//y|¡§??¡ìa??
					CustomerVar.bDoubleBuffer[4+bPacketNumber*8]=0x00;//y????
					CustomerVar.bDoubleBuffer[5+bPacketNumber*8]= 0x00;                 
					CustomerVar.bDoubleBuffer[6+bPacketNumber*8]= 0x00;
					CustomerVar.bDoubleBuffer[7+bPacketNumber*8]= 0x00;	
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
			
      		CustomerVar.bcntBuffer[0]=HIBYTE(wValidPoint);
			CustomerVar.bcntBuffer[1]=LOBYTE(wValidPoint);
			if(bPacketNumber!=0) 
	 		{
	 			CustomerVar.bINTtriggerCnt=0; 
				CustomerVar.bCustomerReSendCNT=CUSTOMER_RESNED_NUM; 
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

	CustomerVar.bCustomCmd05Cnt = 0;
	CustomerVar.WCustomCmd07Cnt = 0;
	CustomerVar.bCustomCmd46Cnt = 0;
	CustomerVar.bCustomCmd25Cnt = 0;
	CustomerVar.bCustomCmd08Cnt = 0;	
	CustomerVar.bINTtriggerCnt = 0XFF;
	BYTE i = 0;
	for(i = 0; i < 8 ; i++)
	{
		CustomerVar.bCustomerBuf[i]=0x00;
		CustomerVar.bHoverBuffer[i]=0x00;
		CustomerVar.bDebugBuf[i]=0;
		CustomerVar.bLastCustomCmdBuf[i]=0;
	}

#ifdef FEATURE_FAKE_FORCE_TOUCH
	for(i=0; i<FINGER_MAX_REPORT; i++)
	{
		CustomerVar.wLastNormalizedSum[i] = 0;
	}
#endif

	CustomerVar.bCustomReportCnt=0;
	CustomerVar.bI2CKeepSendflag=0;
	
	CustomerVar.bCustomerReSendCNT=0;
	CustomerVar.bCustomerKeyReportFlag=0;
	CustomerVar.bCustomerKeyValidByte=0;
	
	CustomerVar.bCustomerReportFingerCNT=0;
	CustomerVar.bCustomerLastReportFingerCNT=0;
	CustomerVar.wCustomerLastValidPoint=0;

	CustomerVar.bTimerINTtrigger=0;

}
#endif	

#ifdef IC_CY8CTMA448

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
		
		CustomerVar.bcntBuffer[0]=0x00;//bCNT*0x04;//HIBYTE(wValidPoint);
		CustomerVar.bcntBuffer[1]=0x00;//LOBYTE(wValidPoint);
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
					 CustomerVar.bNomalDataKey=1;			
					 CustomerVar.bDoubleBuffer[9+bPacketNumber*10] = 0x00; 
					 CustomerVar.bDoubleBuffer[10+bPacketNumber*10]= 0xC0+i;
					 CustomerVar.bDoubleBuffer[11+bPacketNumber*10]=(BYTE)(wPosX&0x00FF);//XL  
					 CustomerVar.bDoubleBuffer[12+bPacketNumber*10]=(BYTE)((wPosX>>8)&0x00FF);//XH 
					 CustomerVar.bDoubleBuffer[13+bPacketNumber*10]=(BYTE)(wPosY&0x00FF);//YL
					 CustomerVar.bDoubleBuffer[14+bPacketNumber*10]=(BYTE)((wPosY>>8)&0x00FF);//YH
					 CustomerVar.bDoubleBuffer[15+bPacketNumber*10]=0x80;//WEIGHT
					 CustomerVar.bDoubleBuffer[16+bPacketNumber*10]=0x00;		 
					 CustomerVar.bDoubleBuffer[17+bPacketNumber*10]=0x00;
					 CustomerVar.bDoubleBuffer[18+bPacketNumber*10]=0x00;
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
					if(CustomerVar.bCustomReportCnt!=0xFF) 
					{
						CustomerVar.bCustomReportCnt++;
					}	
					else 
					{
						CustomerVar.bCustomReportCnt=0;
					}
					//bPacketNumber++;
				}
			}        
			
      		CustomerVar.bcntBuffer[0]=HIBYTE(wValidPoint);
			CustomerVar.bcntBuffer[1]=LOBYTE(wValidPoint);
			if(bPacketNumber!=0) 
	 		{
	 			CustomerVar.bINTtriggerCnt=0; 
				CustomerVar.bCustomerReSendCNT=CUSTOMER_RESNED_NUM; 
	 		}
			
		}
		
		if(CustomerVar.wTimeToNormal > 0)//¦Ì¡Â???a??¨º¡À??2?¨ºy¨¤¡ä?????¨¤??2??¨¹¡ä£¤?t
		{
			CustomerVar.wTimeToNormal++;
			I2C_INT_HIGH();
			if(CustomerVar.wTimeToNormal < 100)
			{
				return;
			}
			else
			{
				CustomerVar.wTimeToNormal = 200;
			} 
		}
		if((bCNT==0)&&(CustomerVar.bNomalDataKey==1))
		{
			I2C_INT_LOW();
			CustomerVar.bDoubleBuffer[0]=0x07;			
			CustomerVar.bDoubleBuffer[1]=0x00;
			CustomerVar.bDoubleBuffer[2]=0x07;//???¡ä			
			CustomerVar.bDoubleBuffer[3]=0x00;
			CustomerVar.bDoubleBuffer[4]=0x01;
			CustomerVar.bDoubleBuffer[5]=0xF1;//¨¬?3?
			CustomerVar.bDoubleBuffer[6]=0x46;//¨¬?3?
			CustomerVar.bDoubleBuffer[7]=0x00;
			CustomerVar.bDoubleBuffer[8]=0x40;
			CustomerVar.bNomalDataKey=0;
			ZetVar.wI2cTxIdx= 0;
			 ZetVar.wI2cTxLen = 8;
			 ZetVar.pI2CData = (BYTE *)(&CustomerVar.bDoubleBuffer[0]);
			 ZetVar.wI2cRxIdx= 0;
		}
		
		else if(bCNT>0)
		{
			 CustomerVar.bDoubleBuffer[0]=0x11+(bCNT-1)*0x0a;			
			 CustomerVar.bDoubleBuffer[1]=0x00;
			 CustomerVar.bDoubleBuffer[2]=0x11+(bCNT-1)*0x0a;//???¡ä			
		     CustomerVar.bDoubleBuffer[3]=0x00;
			 CustomerVar.bDoubleBuffer[4]=0x01;
			 CustomerVar.bDoubleBuffer[5]=0xc0+CustomerVar.bDoubleBuffer[5];//¨¬?3?
			 CustomerVar.bDoubleBuffer[6]=0x46;//¨¬?3?
			 CustomerVar.bDoubleBuffer[7]=bCNT;
			 CustomerVar.bDoubleBuffer[8]=0x01; 
			 if(CustomerVar.bCustomerLastReportFingerCNT<=0)//¨¦?¨°?¦Ì??a0
			 {
				 CustomerVar.bDoubleBuffer[10]= 0xA0; 
			 }
			 else//¦Ì¡À?¡ã¦Ì?¨ºyo¨ª¨¦?¨°?¦Ì?¨ºy??2??a0
			 {
			 	
				 CustomerVar.bDoubleBuffer[10]= 0xC0; 
			 }
			 ZetVar.wI2cTxIdx= 0;
			 ZetVar.wI2cTxLen = 80;//80
			 ZetVar.pI2CData = (BYTE *)(&CustomerVar.bDoubleBuffer[0]);
			 ZetVar.wI2cRxIdx= 0;	 
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
	CustomerVar.bCustomCmd0100Cnt = 0;
	CustomerVar.bCustomCmd0400Cnt = 0;
	CustomerVar.bINTtriggerCnt = 0x00;
	CustomerVar.bNomalDataKey = 0;
	CustomerVar.wTimeToNormal = 0;
	BYTE i = 0;
	for(i = 0; i < 8 ; i++)
	{
		CustomerVar.bCustomerBuf[i]=0x00;
		CustomerVar.bHoverBuffer[i]=0x00;
		CustomerVar.bDebugBuf[i]=0;
		CustomerVar.bLastCustomCmdBuf[i]=0;
	}

#ifdef FEATURE_FAKE_FORCE_TOUCH
	for(i=0; i<FINGER_MAX_REPORT; i++)
	{
		CustomerVar.wLastNormalizedSum[i] = 0;
	}
#endif

	CustomerVar.bCustomReportCnt=0;
	CustomerVar.bI2CKeepSendflag=0;
	
	CustomerVar.bCustomerReSendCNT=0;
	CustomerVar.bCustomerKeyReportFlag=0;
	CustomerVar.bCustomerKeyValidByte=0;
	
	CustomerVar.bCustomerReportFingerCNT=0;
	CustomerVar.bCustomerLastReportFingerCNT=0;
	CustomerVar.wCustomerLastValidPoint=0;

	CustomerVar.bTimerINTtrigger=0;

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

