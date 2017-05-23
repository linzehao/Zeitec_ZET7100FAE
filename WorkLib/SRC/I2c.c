/**
 * @file I2C.c
 *
 * I2C Related Function
 *
 * @version $Revision: 62 $
 * @author JLJuang <JL.Juang@zeitecsemi.com>
 * @note Copyright (c) 2010, Zeitec Semiconductor Ltd., all rights reserved.
 * @note
*/
#include"ZetDEF.h"
#ifdef FEATURE_CUSTOMER_PROTOCOL
#ifdef SPI_FLASH_WR_ENABLE
BYTE volatile xdata bFlashBuffer[4096];
#endif

#ifdef NEW_I2C_PARSING_FLOW
BYTE const code bCustomKey4Cmd03[]={1,0x03};
BYTE const code bCustomKey4Cmd04[]={1,0x04};
BYTE const code bCustomKey4Cmd05[]={1,0x05};
BYTE const code bCustomKey4Cmd06[]={1,0x06};
BYTE const code bCustomKey4Cmd09[]={1,0x09};
BYTE const code bCustomKey4Cmd0A[]={1,0x0A};
BYTE const code bCustomKey4Cmd0E[]={1,0x0E};
BYTE const code bCustomKey4Cmd0E00[]={2,0x0E,0x00};
BYTE const code bCustomKey4Cmd0E01[]={2,0x0E,0x01};
BYTE const code bCustomKey4Cmd15[]={1,0x15};
BYTE const code bCustomKey4Cmd1E[]={1,0x1E};
BYTE const code bCustomKey4Cmd22[]={1,0x22};
BYTE const code bCustomKey4Cmd2A[]={1,0x2A};
BYTE const code bCustomKey4Cmd2501[]={2,0x25,0x01};
BYTE const code bCustomKey4Cmd45[]={1,0x45};
BYTE const code bCustomKey4Cmd47[]={1,0x47};
BYTE const code bCustomKey4Cmd4B[]={1,0x4B};
BYTE const code bCustomKey4Cmd4E[]={1,0x4E};
BYTE const code bCustomKey4Cmd51[]={1,0x51};
BYTE const code bCustomKey4CmdEE[]={1,0xEE};
BYTE const code bCustomKey4CmdFF00[]={2,0xFF,0x00};
BYTE const code bCustomKey4CmdFF01[]={2,0xFF,0x01};
BYTE const code bCustomKey4CmdFF02[]={2,0xFF,0x02};
BYTE const code bCustomKey4CmdFF03[]={2,0xFF,0x03};
BYTE const code bCustomKey4CmdFF04[]={2,0xFF,0x04};
//reserve switching cmd
BYTE const code bCustomKey4CmdFFF101[]={3,0xFF,0xF1,0x01};
BYTE const code bCustomKey4CmdFFF102[]={3,0xFF,0xF1,0x02};
BYTE const code bCustomKey4CmdFFF103[]={3,0xFF,0xF1,0x03};
BYTE const code bCustomKey4CmdFFFF[]={2,0xFF,0xFF};

void CustomHfunc4Cmd03();
void CustomHfunc4Cmd04();
void CustomHfunc4Cmd05();
void CustomHfunc4Cmd06();
void CustomHfunc4Cmd09();
void CustomHfunc4Cmd0A();
void CustomHfunc4Cmd0E();
void CustomHfunc4Cmd0E00();
void CustomHfunc4Cmd0E01();
void CustomHfunc4Cmd15();
void CustomHfunc4Cmd1E();
void CustomHfunc4Cmd22();
void CustomHfunc4Cmd2A();
void CustomHfunc4Cmd2501();
void CustomHfunc4Cmd45();
void CustomHfunc4Cmd47();
void CustomHfunc4Cmd4B();
void CustomHfunc4Cmd4E();
void CustomHfunc4Cmd51();
void CustomHfunc4CmdEE();
void CustomHfunc4CmdFF00();
void CustomHfunc4CmdFF01();
void CustomHfunc4CmdFF02();
void CustomHfunc4CmdFF03();
void CustomHfunc4CmdFF04();

void CustomHfunc4CmdFFF101();
void CustomHfunc4CmdFFF102();
void CustomHfunc4CmdFFF103();
void CustomHfunc4CmdFFFF();

BYTE const code CustomRes4Cmd0A[]={0x95,0x0c,0x01,0x02};

BYTE const code CustomRes4Cmd15[]={0x37,0x04,0x7f,0x07};
BYTE const code CustomRes4Cmd4B[]= {0x05,0x26,0x26,0x00,0x9f,0xd4,0x7d,0x0f};
BYTE const code CustomRes4Cmd4E[] = {0x03,0x09,0x09,0x16,0x80,0x50};		
BYTE const code CustomRes4CmdEE[] = {0x34,0x21,0x00,0x0a,0x00,0x26,0x01,0x01,0x04,0x0e,0x25,0x2a,0x12,0x01,0x06,0x15,0x00,0x47,0x00,0x00,0x00,0x00,0x00,0x00};
BYTE const code CustomRes4CmdFF01[] = {0x54,0x01,0x00,0x0f,0x45,0x46,0x00,0x00,0x00,0x00};
BYTE const code CustomRes4CmdFF02[] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00};			
BYTE const code CustomRes4CmdFF03[] = {0x55,0x01,0x00,0x00,0x06,0x07,0x00,0x00,0x00,0x00,0x00,0x00};			
BYTE const code CustomRes4CmdFF04[] = {0x51,0x21,0x00,0x01,0x00,0x55,0x00,0x00,0x00,0x00,0x00,0x00};			
BYTE  const code CustomRes4Cmd2A[] = {0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x4c,\
							  0x47,0x30,0x33,0x32,0x37,0x2d,0x30,0x31};	

I2CCmdType const code I2CCmd[]=
{ {bCustomKey4Cmd03,  CustomHfunc4Cmd03},
  {bCustomKey4Cmd04,  CustomHfunc4Cmd04},
  {bCustomKey4Cmd05,  CustomHfunc4Cmd05},
	{bCustomKey4Cmd06,  CustomHfunc4Cmd06},
	{bCustomKey4Cmd09,  CustomHfunc4Cmd09},
	{bCustomKey4Cmd0A, CustomHfunc4Cmd0A},
	{bCustomKey4Cmd0E,  CustomHfunc4Cmd0E},
	{bCustomKey4Cmd0E00,  CustomHfunc4Cmd0E00},
	{bCustomKey4Cmd0E01,  CustomHfunc4Cmd0E01},
	{bCustomKey4Cmd15,  CustomHfunc4Cmd15},
	{bCustomKey4Cmd1E,  CustomHfunc4Cmd1E},
	{bCustomKey4Cmd22,  CustomHfunc4Cmd22},
	{bCustomKey4Cmd2A,  CustomHfunc4Cmd2A},
	{bCustomKey4Cmd2501, CustomHfunc4Cmd2501},
	{bCustomKey4Cmd45, CustomHfunc4Cmd45},
	{bCustomKey4Cmd47,  CustomHfunc4Cmd47},
	{bCustomKey4Cmd4B,  CustomHfunc4Cmd4B},
	{bCustomKey4Cmd4E, CustomHfunc4Cmd4E},
	{bCustomKey4Cmd51,  CustomHfunc4Cmd51},
	{bCustomKey4CmdEE,  CustomHfunc4CmdEE},
	{bCustomKey4CmdFF00,  CustomHfunc4CmdFF00},
	{bCustomKey4CmdFF01,  CustomHfunc4CmdFF01},
	{bCustomKey4CmdFF02,  CustomHfunc4CmdFF02},
	{bCustomKey4CmdFF03,  CustomHfunc4CmdFF03},
  {bCustomKey4CmdFF04,  CustomHfunc4CmdFF04},
	{bCustomKey4CmdFFF101,  CustomHfunc4CmdFFF101},
	{bCustomKey4CmdFFF102, CustomHfunc4CmdFFF102},
	{bCustomKey4CmdFFF103, CustomHfunc4CmdFFF103},
	{bCustomKey4CmdFFFF,  CustomHfunc4CmdFFFF}
};

//WORD const code wCustomCmdElementNum=29;
WORD const code wCustomCmdElementNum=sizeof(I2CCmd)/sizeof(I2CCmd[0]);
BYTE const code bCustomMaxKeyLength=4; //3;
BYTE const code bHitKeyFlag=0;

//BYTE const code bCustomBuf4Cmd15[]={ ...... };
//BYTE const code bCustomBuf4Cmd1E[]={ ...... };
//BYTE const code bCustomBuf4Cmd22[]={ ...... };

#else

BYTE const code bCustomCmd0700Cnt0Buf[]= {0x25,0xD6,0x00,0x81,0x00,0x00,0x2C,0x58,0x01,0x00,0x00,0x00,0x05,0x59,0x01,0x09,0x00,0x00,0x06,0x63, \
                                          0x01,0x06,0x00,0x01,0x26,0x6A,0x01,0x07,0x00,0x00,0x47,0x72,0x01,0x6F,0x00,0x00,0x07,0xE2,0x01,0x03, \
                                          0x00,0x00,0x08,0xE6,0x01,0x0D,0x00,0x00,0x0F,0xF4,0x01,0x0A,0x00,0x01,0x12,0xFF,0x01,0x01,0x00,0x00, \
                                          0x13,0x01,0x02,0x05,0x00,0x01,0x17,0x07,0x02,0x0F,0x00,0x01,0x19,0x17,0x02,0x14,0x00,0x01,0x28,0x2C, \
                                          0x02,0x04,0x00,0x00,0x2A,0x31,0x02,0x0C,0x00,0x00,0x2E,0x3E,0x02,0x09,0x00,0x01,0x2F,0x48,0x02,0x19, \
                                          0x00,0x00,0x37,0x62,0x02,0x06,0x00,0x00,0x38,0x69,0x02,0x23,0x00,0x01,0x3D,0x8D,0x02,0x04,0x01,0x01, \
                                          0x41,0x97,0x02,0x13,0x00,0x01,0x42,0xAB,0x02,0x02,0x00,0x01,0x45,0xAE,0x02,0x08,0x00,0x01,0x46,0xB7, \
                                          0x02,0x09,0x07,0x01,0x48,0x07,0x03,0x4F,0x00,0x01,0x4E,0x57,0x03,0x07,0x00,0x00,0x50,0x5F,0x03,0x06, \
                                          0x00,0x00,0x54,0x66,0x03,0x03,0x00,0x01,0x64,0x6A,0x03,0x35,0x00,0x0C,0x65,0xA0,0x03,0x18,0x00,0x00, \
                                          0x66,0xB9,0x03,0x1C,0x00,0x01,0x67,0xD6,0x03,0x0D,0x01,0x01,0x68,0xF2,0x03,0x0A,0x00,0x00,0x69,0xFD, \
                                          0x03,0x11,0x00,0x00
                                         };


#ifdef FEATURE_BM_NEW
//Atmel MainBoard
BYTE const code bCustomCmd5901Cnt0Buf[]= {0x01,0x80,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x10,0x66,0xE9, \
                                          0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00, \
                                          0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00, \
                                          0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF, \
                                          0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66, \
                                          0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25, \
                                          0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00, \
                                          0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00, \
                                          0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                          0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9, \
                                          0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00, \
                                          0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9, \
                                          0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                          0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9, \
                                          0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00, \
                                          0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25
                                         };
#else //ST Mainboard
/*
BYTE const code bCustomCmd5901Cnt0Buf[]={0x01,0x80,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01, \
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x10,0x6F,0xB9, \
0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00, \
0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF, \
0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F, \
0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99, \
0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00, \
0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00, \
0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10, \
0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00, \
0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF, \
0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F, \
0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99, \
0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00};
*/
//Atmel Mainboard response pattern before upgrade procedure

BYTE const code bCustomCmd5901Cnt0Buf[]= {0x01,0x80,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x10,0x6F,0xB9, \
                                          0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                                          0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00, \
                                          0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF, \
                                          0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F, \
                                          0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99, \
                                          0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00, \
                                          0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00, \
                                          0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                          0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
                                          0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                                          0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
                                          0xFF ,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                          0x6F,0xB9,0x99,0x00,	0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
                                          0x99,0x00,0x00,0x00,	0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                                          0x00,0x00,0x00,0xFF,	0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99
                                         };

#endif

BYTE const code bCustomCmdD801Cnt1Buf[]= {0x04,0x00,0x03,0x00,0x11,0x00,0x10,0x00,0x04,0x00,0x0C,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x06,0x00, \
                                          0x08,0x00,0x12,0x00,0x17,0x00,0x0A,0x00,0x10,0x00,0x1D,0x00,0x00,0x00,0x00,0x00,0x16,0x00,0x13,0x00, \
                                          0x13,0x00,0x19,0x00,0x0E,0x00,0x0F,0x00,0x1E,0x00,0xFD,0xFF,0x07,0x00,0x14,0x00,0x06,0x00,0x1A,0x00, \
                                          0x18,0x00,0x08,0x00,0x18,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x0A,0x00,0x06,0x00,0x07,0x00,0x09,0x00, \
                                          0x0B,0x00,0x12,0x00,0x09,0x00,0x04,0x00,0x11,0x00,0x05,0x00,0x05,0x00,0x0C,0x00,0x0A,0x00,0x04,0x00, \
                                          0x09,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x01,0x00,0x12,0x00,0x08,0x00,0xFB,0xFF,0x0B,0x00, \
                                          0x0D,0x00,0x00,0x00,0x0F,0x00,0xFE,0xFF
                                         };

BYTE const code bCustomCmdD801Cnt2Buf[]= {0x07,0x00,0x0B,0x00,0x0D,0x00,0x15,0x00,0x0E,0x00,0x0D,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x02,0x00, \
                                          0x06,0x00,0x0C,0x00,0x00,0x00,0x08,0x00,0x06,0x00,0x06,0x00,0x1F,0x00,0x0B,0x00,0x0F,0x00,0x12,0x00, \
                                          0x0C,0x00,0x16,0x00,0x0C,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x06,0x00,0x0B,0x00,0x01,0x00, \
                                          0x00,0x00,0x0D,0x00,0x02,0x00,0x0D,0x00,0x1A,0x00,0x06,0x00,0x1C,0x00,0x0D,0x00,0x14,0x00,0x07,0x00, \
                                          0x13,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x14,0x00,0x1D,0x00,0x0F,0x00,0xFF,0xFF,0x03,0x00, \
                                          0x17,0x00,0x09,0x00,0x16,0x00,0x14,0x00,0x17,0x00,0x12,0x00,0x18,0x00,0x1A,0x00,0x15,0x00,0x14,0x00, \
                                          0x00,0x00,0x00,0x00,0x0C,0x00,0x1B,0x00
                                         };


BYTE const code bCustomCmdD801Cnt3Buf[]= {0x0B,0x00,0x04,0x00,0xFB,0xFF,0x06,0x00,0x13,0x00,0x18,0x00,0x1D,0x00,0x10,0x00,0x12,0x00,0x18,0x00, \
                                          0x13,0x00,0x0A,0x00,0x18,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x04,0x00,0x12,0x00,0x01,0x00, \
                                          0xF9,0xFF,0x0F,0x00,0x04,0x00,0x1E,0x00,0x14,0x00,0x13,0x00,0x0D,0x00,0x19,0x00,0x0D,0x00,0x07,0x00, \
                                          0x06,0x00,0x0A,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x15,0x00,0x0A,0x00,0x0E,0x00,0x05,0x00,0x17,0x00, \
                                          0x20,0x00,0x55,0x00,0x30,0x00,0x13,0x00,0x19,0x00,0x13,0x00,0x04,0x00,0x1F,0x00,0x15,0x00,0x08,0x00, \
                                          0x00,0x00,0x00,0x00,0x02,0x00,0x09,0x00,0x00,0x00,0xFD,0xFF,0x0A,0x00,0x28,0x00,0x68,0x00,0xE2,0x01, \
                                          0x84,0x01,0x46,0x00,0x18,0x00,0x16,0x00
                                         };

BYTE const code bCustomCmdD801Cnt4Buf[]= {0x01,0x00,0x09,0x00,0xFA,0xFF,0x0C,0x00,0x00,0x00,0x00,0x00,0x0B,0x00,0x01,0x00,0xED,0xFF,0xFD,0xFF, \
                                          0x00,0x00,0x14,0x00,0x9C,0x00,0x25,0x03,0xF7,0x02,0x84,0x01,0x26,0x00,0x0B,0x00,0x08,0x00,0x01,0x00, \
                                          0xFF,0xFF,0xFD,0xFF,0x00,0x00,0x00,0x00,0x05,0x00,0x06,0x00,0x01,0x00,0x03,0x00,0x08,0x00,0x02,0x00, \
                                          0x2B,0x00,0x56,0x01,0x2A,0x02,0xD0,0x00,0x17,0x00,0x14,0x00,0xFF,0xFF,0x08,0x00,0x06,0x00,0x06,0x00, \
                                          0x00,0x00,0x00,0x00,0x24,0x00,0x1D,0x00,0x22,0x00,0x24,0x00,0x22,0x00,0x0C,0x00,0x3D,0xFF,0x6A,0xFD, \
                                          0x6B,0xFE,0xF2,0xFF,0x08,0x00,0x0A,0x00,0x16,0x00,0x15,0x00,0x0F,0x00,0x1A,0x00,0x00,0x00,0x00,0x00, \
                                          0x27,0x00,0x26,0x00,0x25,0x00,0x1F,0x00
                                         };

BYTE const code bCustomCmdD801Cnt5Buf[]= {0x23,0x00,0x16,0x00,0x78,0xFF,0xB6,0xFD,0x2D,0xFE,0xD2,0xFF,0x10,0x00,0x15,0x00,0x1D,0x00,0x14,0x00, \
                                          0x19,0x00,0x1B,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x1D,0x00,0x28,0x00,0x1D,0x00,0x1A,0x00,0x18,0x00, \
                                          0xFC,0xFF,0xC8,0xFF,0xD7,0xFF,0x08,0x00,0x0A,0x00,0x0E,0x00,0x10,0x00,0x06,0x00,0x21,0x00,0x0D,0x00, \
                                          0x00,0x00,0x00,0x00,0x15,0x00,0x1D,0x00,0x14,0x00,0x10,0x00,0x1F,0x00,0x12,0x00,0x0D,0x00,0x17,0x00, \
                                          0x26,0x00,0x28,0x00,0x0A,0x00,0x06,0x00,0x18,0x00,0x02,0x00,0x12,0x00,0x09,0x00,0x00,0x00,0x00,0x00, \
                                          0x05,0x00,0x0B,0x00,0x06,0x00,0x15,0x00,0x10,0x00,0x15,0x00,0x13,0x00,0x10,0x00,0x11,0x00,0x16,0x00, \
                                          0x0D,0x00,0x0C,0x00,0x13,0x00,0x12,0x00
                                         };

BYTE const code bCustomCmdD801Cnt6Buf[]= {0x02,0x00,0x0B,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0xFB,0xFF,0x0F,0x00,0x0E,0x00,0x0D,0x00,0x19,0x00, \
                                          0x10,0x00,0x0E,0x00,0x26,0x00,0x16,0x00,0x0C,0x00,0x0F,0x00,0x0C,0x00,0x0D,0x00,0x09,0x00,0x0C,0x00, \
                                          0x00,0x00,0x00,0x00,0x01,0x00,0x0D,0x00,0x07,0x00,0x11,0x00,0x0A,0x00,0x14,0x00,0x0D,0x00,0x01,0x00, \
                                          0x11,0x00,0x12,0x00,0x07,0x00,0x11,0x00,0x09,0x00,0x0D,0x00,0x0B,0x00,0x0D,0x00,0x00,0x00,0x00,0x00, \
                                          0x03,0x00,0x1F,0x00,0x13,0x00,0x20,0x00,0x18,0x00,0x17,0x00,0x1A,0x00,0x13,0x00,0x1D,0x00,0x17,0x00, \
                                          0x0A,0x00,0x1B,0x00,0x15,0x00,0x11,0x00,0x1C,0x00,0x0B,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x18,0x00, \
                                          0x17,0x00,0x15,0x00,0x0E,0x00,0x1A,0x00
                                         };

BYTE const code bCustomCmdD801Cnt7Buf[]= {0x0F,0x00,0x0B,0x00,0x28,0x00,0x1C,0x00,0x04,0x00,0x08,0x00,0x09,0x00,0x07,0x00,0x0E,0x00,0x11,0x00, \
                                          0x00,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0x1B,0x00,0x19,0x00,0x22,0x00,0x20,0x00,0x18,0x00,0x0B,0x00, \
                                          0x20,0x00,0x28,0x00,0xFE,0xFF,0x09,0x00,0x0F,0x00,0x06,0x00,0x12,0x00,0x14,0x00,0x00,0x00,0x00,0x00, \
                                          0x06,0x00,0x0C,0x00,0x14,0x00,0x15,0x00,0x19,0x00,0x19,0x00,0x17,0x00,0x13,0x00,0x16,0x00,0x1A,0x00, \
                                          0x08,0x00,0x12,0x00,0xFE,0xFF,0x1C,0x00,0x08,0x00,0x11,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x02,0x00, \
                                          0x0F,0x00,0x16,0x00,0x1F,0x00,0x24,0x00,0x1C,0x00,0x10,0x00,0x13,0x00,0x19,0x00,0x00,0x00,0x14,0x00, \
                                          0xFF,0xFF,0x09,0x00,0x0E,0x00,0x08,0x00
                                         };

BYTE const code bCustomCmdD801Cnt8Buf[]= {0x00,0x00,0x00,0x00,0x04,0x00,0x0F,0x00,0x08,0x00,0x1C,0x00,0x15,0x00,0x1B,0x00,0x0F,0x00,0xFC,0xFF, \
                                          0x1D,0x00,0x25,0x00,0x19,0x00,0x0C,0x00,0x20,0x00,0x15,0x00,0x11,0x00,0x12,0x00,0x00,0x00,0x00,0x00, \
                                          0x02,0x00,0x01,0x00,0x0B,0x00,0x02,0x00,0x11,0x00,0x12,0x00,0x0C,0x00,0xFB,0xFF,0x18,0x00,0x1A,0x00, \
                                          0x15,0x00,0x11,0x00,0x10,0x00,0x0A,0x00,0x0C,0x00,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                                         };


BYTE const code bCustomCmdD801Cnt0Buf[]= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFD,0xFF,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                          0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                                         };


#endif

#endif


void I2CDataFormatDataInCheckSub(void)
{
    ///-------------------------------------------------------------------///
    /// 1. Check if any finger in
    ///-------------------------------------------------------------------///
    if( 		(ZetVar.bFingerCountsFound >= 1)
                || 	(	(ZetVar.wAlgoStatus2 & (ALG2_HEAVY_PRESS_REPORT_FROZEN|ALG2_HEAVY_PRESS_REPORT_FROZEN_LAST)) == ALG2_HEAVY_PRESS_REPORT_FROZEN_LAST)
      )
    {
        ZetVar.wSysMode |= SYS_MODE_FINGER_REPORT;
        ZetVar.bFingerUpRpCnt = ZetDF.cFormatCtrl.scDataCtrl.bFingerUpReportCnt;
        ZetVar.bDataIn = TRUE;
        return;
    }

#if defined(FEATURE_TOUCH_HOVER_SENSOR) || defined(FEATURE_TRACEIO_HOVER_SENSOR)
    if((ZetVar.wSysMode & SYS_MODE_HOVER_STATE_CHANGED))
        ///&&(ZetDF.cHover.scHoverCtrl.bHoverEnable != FALSE))
    {
        ZetVar.wSysMode |= SYS_MODE_FINGER_REPORT;
        ZetVar.bDataIn = TRUE;
        return;
    }
#endif ///< for FEATURE_TOUCH_HOVER_SENSOR

    ///-------------------------------------------------------------------///
    /// 2. Check if any key pressed
    ///-------------------------------------------------------------------///
#ifdef FEATURE_REAL_KEY
    if((ZetVar.KeyCtrl.bKeyValidByte != 0x00) || (ZetVar.bKeyLockRelease == FALSE))
    {
        ZetVar.wSysMode |= SYS_MODE_FINGER_REPORT;
        ZetVar.bFingerUpRpCnt = ZetDF.cFormatCtrl.scDataCtrl.bFingerUpReportCnt;
        ZetVar.bDataIn = TRUE;
        return;
    }
#endif ///< for FEATURE_REAL_KEY
    ///-------------------------------------------------------------------///
    /// 3. If there is no finger and no key,  return a null data for software
    ///-------------------------------------------------------------------///
    if( ZetVar.wSysMode & SYS_MODE_FINGER_REPORT)
    {
        ZetVar.bDataIn = TRUE;
    }
    return;
}


/**
 * @brief I2CDataFormatIntLow
 *
 *  Trigger Int low to invoke host to receive data
 *
 * @return NULL
 *
 */
void I2CDataFormatDataInCheck(void)
{
    ZetVar.bDataIn = FALSE;
#ifdef FEATURE_IIR_FINGER_UP
    if(ZetVar.bFingerUpEn & FINGER_UP_REPORT_BIT0)
#else
    if(ZetDF.cFinger.scNormal.bFingerUpEnable & FINGER_UP_REPORT_BIT0)
#endif
    {
        //if(ZetVar.bHeavyPressDetectReportFingerFrozenLast == TRUE)
        if(ZetVar.wAlgoStatus2 & ALG2_HEAVY_PRESS_REPORT_FROZEN_LAST)
        {
            I2CDataFormatDataInCheckSub();
            return;
        }
        else
        {
            if(ZetVar.wAlgoStatus & ALGO_FINGER_UP_DEBOUNCE_REPORTING)
            {
                if(	(ZetVar.bFingerCountsFound ==0)
#ifdef FEATURE_IIR_FINGER_UP
                        && (!(ZetVar.bFingerUpEn & FINGER_UP_MV_BIT1))
#endif
#ifdef FEATURE_REAL_KEY
                        && (ZetVar.KeyCtrl.bKeyValidByte ==0)
#endif ///< for FEATURE_REAL_KEY
#ifdef FEATURE_FINGER_UP_DEBOUNCE_ALG
                        && (ZetVar.bFingerReportCounts == 1)
#endif
                  )
                {
                    ZetVar.bDataIn = NULLSTATE;
                }
                else
                {
                    ZetVar.wSysMode |= SYS_MODE_FINGER_REPORT;
                    ZetVar.bDataIn = TRUE;
                }
                ZetVar.bFingerUpRpCnt = ZetDF.cFormatCtrl.scDataCtrl.bFingerUpReportCnt;
            }
            else
            {
                I2CDataFormatDataInCheckSub();
                return;
            }
        }
    }
    else
    {
        I2CDataFormatDataInCheckSub();
        return;
    }

}

/**
 * @brief  I2CWaitTransferDone()
 *
 *  Wait transfer done
 *
 * @return NULL
 *
 */
void  I2CWaitTransferDone(void)
{
    while(I2C_INT()==FALSE)
    {
        /// Watch dog clear
#ifdef FEATURE_WATCH_DOG
        SYSWatchDogClear();
#endif ///< for FEATURE_WATCH_DOG
    }
}

/**
 * @brief  I2CInit()
 *
 *  Init the I2C module
 *
 * @return NULL
 *
 */
void I2CInit(void)
{
    int data iI2CCtrl;
    int data iI2CCon2;
    ///-------------------------------------------------------------------------------///
    /// 1. I2C_DADDR
    ///-------------------------------------------------------------------------------///
    /// I2C_DADDR  = ZetDF.cMiscRegister.scInterface.bRegI2CDADDR;
    WRITE_REG(REG32_I2C_DADDR, ZetDF.cMiscRegister.scInterface.bRegI2CDADDR);
    /// FWADR 	   = ZetDF.cMiscRegister.scInterface.bRegFWADR;
    WRITE_REG(REG32_FWADR, ZetDF.cMiscRegister.scInterface.bRegFWADR);

    ///-------------------------------------------------------------------------------///
    /// 1. Set I2C Variables
    ///-------------------------------------------------------------------------------///
    ZetVar.bI2cIntLowTimeOutDefault = ZetDF.cFormatCtrl.scDataCtrl.bI2CIntLowTimeOutCnt;
    ZetVar.bI2cRxLen = 0;
    ZetVar.wI2cRxIdx = 0;

    ZetVar.pI2CData = (BYTE *)&ZetVar.bB2Buf[0];
    ZetVar.wI2cTxLen = B2_BUF_LEN ;
    ZetVar.wI2cTxIdx = 0;
    ZetVar.bI2cStatus = 0;
    ///------------------------------------------------------------///
    /// Calculate the data length
    /// 3 = PACKET_ID  + VALID[1:0]
    ///------------------------------------------------------------///
    ZetVar.bI2cByteNumber =  (3+(ZetDF.cFormatCtrl.scDataCtrl.bFingerNum<<2));
    /// Check the key byte
#ifdef FEATURE_REAL_KEY
    if(ZetDF.cKeyCtrl.scKeyDriveTrace.bKeySupport == TRUE)
    {
        ZetVar.bI2cByteNumber++;
    }
#endif
#ifdef FEATURE_VIRTUAL_KEY
    if (ZetVar.bVirtualKeyEnable == TRUE)
    {
        ZetVar.bI2cByteNumber++;
    }
#endif ///< for FEATURE_VIRTUAL_KEY  	
    ///-------------------------------------------------------------------------------///
    /// 2. Set I2C Hardware
    ///-------------------------------------------------------------------------------///

    /// enable I2C I/O
    iI2CCtrl = READ_REG32(REG32_I2C_CTRL);
    iI2CCtrl &= ~(I2C_DEGLITCH_EN|I2C_DEGLITCH_MAX2|I2C_DEGLITCH_MAX1|I2C_DEGLITCH_MAX0);
    iI2CCtrl |=  (ZetDF.cMiscRegister.scInterface.bI2Ctrl & (I2C_DEGLITCH_EN|I2C_DEGLITCH_MAX2|I2C_DEGLITCH_MAX1|I2C_DEGLITCH_MAX0));
    WRITE_REG32(REG32_I2C_CTRL, iI2CCtrl);
    SET_BIT32(REG32_I2C_CTRL, I2CEN);

    /// Clear I2C Stop Flag  and Set to slave mode (set to 0)
    CLR_BIT32(REG32_I2CON, (MASTER_MODE| I2C_STOP));

    /// LOCK
    iI2CCon2 = READ_REG32(REG32_I2CON2);
    iI2CCon2 &= ~(RG_DRVSEL_SPI_18V1|RG_DRVSEL_SPI_18V0);
    iI2CCon2 |= (ZetDF.cMiscRegister.scInterface.bI2CCon2 & (RG_DRVSEL_SPI_18V1|RG_DRVSEL_SPI_18V0));
    WRITE_REG32(REG32_I2CON2, iI2CCon2);
    CLR_BIT(REG32_I2CON2, (RG_SCL_LOCKB));

    /// Disable mass trasnfer
    CLR_BIT32(REG32_I2C_CTRL, (FLASH_I2C_EN));
    SET_BIT32(REG32_I2C_CTRL, (STD_I2C_EN));

    ///-------------------------------------------------------------------------------///
    /// 3 INT pin init
    ///-------------------------------------------------------------------------------///
    /// Set the INT pin high

    /// Set P35 as output pin for use as  I2C INT pin
    if((ZetDF.cGlobalData.scPanelInformation.bICPackageType & PACKAGE_INT_PIN_BIT4) == ZET7100_PACKAGE_TYPE_A)
    {
        INTPortReg	= INT_CTRL_P3;
        INTPinBit		= INT_PIN_P5;
        I2C_INT_HIGH();
        SET_BIT32(REG32_IODIRP3, P35_OUT);
    }
    else //if((ZetDF.cGlobalData.scPanelInformation.bICPackageType & PACKAGE_INT_PIN_BIT4) == ZET7100_PACKAGE_TYPE_B)
    {
        INTPortReg	= INT_CTRL_P1;
        INTPinBit 	= INT_PIN_P2;
        I2C_INT_HIGH();
        SET_BIT32(REG32_IODIR, P12_OUT);
    }

    ///-------------------------------------------------------------------------------///
    /// Set SDA,SCL pull high
    ///-------------------------------------------------------------------------------///
    WRITE_REG32(REG32_PORT3_PH, ZetDF.cMiscRegister.scInterface.bRegPort3PH);

#ifdef FEATURE_INT_PULL_HIGH_CONTROL
    ///-------------------------------------------------------------------------------///
    /// INT Pull High Control
    ///-------------------------------------------------------------------------------///
    WRITE_REG32(REG32_PORT1_PH, ZetDF.cMiscRegister.scInterface.bRegPort1PH);
    WRITE_REG32(REG32_PORT_CFG, ZetDF.cMiscRegister.scInterface.bRegPortCfg);
#endif
}

/**
 * @brief I2CDataFormatReset
 *
 *  Reset the default i2c transfer buffer to the dynamic mode buffer (for mainloop)
 *
 * @return NULL
 *
 */
void I2CDataFormatReset(void)
{

    ///------------------------------------------------------------///
    /// Replace the 0x3C as the reset NULL ID 0x00
    ///------------------------------------------------------------///
    ZetVar.pCurReportData[0]  = I2C_NULL_PACKET_ID;
    ZetVar.pI2CData =(BYTE *) ZetVar.pCurReportData;
    ZetVar.wI2cTxLen = ZetVar.bI2cByteNumber;
    ZetVar.wI2cTxIdx = 0;
    ///------------------------------------------------------------///
    /// Force the INT high
    ///------------------------------------------------------------///
    #ifdef REPORT_GESTURE_POINTS_LOG_METHOD
    if(bINTKeepLowFlag!=1)
    #endif
    {
      I2C_INT_HIGH();
    }

}

/**
 * @brief  I2CTxCheckEnd()
 *
 *  Service the I2C Transfer End
 *
 * @return NULL
 *
 */
void I2CTxCheckEnd()
{
    if(ZetVar.wI2cTxIdx >= ZetVar.wI2cTxLen)
    {

        #ifdef REPORT_GESTURE_POINTS_LOG_METHOD
				if (ZetVar.bI2CCmd == 0xD3) 
        {
          if(bCmdD3Cnt ==0)
          {
              bCmdD3Cnt++;
							bINTKeepLowFlag=1;
							//if(bGesturePointState[1]==0x00) //only get 1 time by D3 cmd
							if(0)
							{
								bGesturePointState=GESTURE_POINT_NONE_STATE;
								bCmdD3Cnt=0;
							}
          }
					else if(bCmdD3Cnt ==1)
					{
							bGesturePointState=GESTURE_POINT_NONE_STATE;
              //LM, test
              bCmdD3Cnt=0;
							bGesturePointBuffer[1]=0x00;
							bINTKeepLowFlag=0;
							
							//ZetVar.bTranType = TRAN_TYPE_DYNAMIC; //switch back to report touching point
					}
        }
        #endif
		
				#ifdef FEATURE_CUSTOMER_PROTOCOL
        if(ZetVar.bWorkingState==WORKING_STATE_ZET_CMD_STATE)
        {
            I2CDataFormatReset();    
        }
        else
        {
            CustomerVar.bI2CKeepSendflag=0;
            ZetVar.pCurReportData[0]  = I2C_NULL_PACKET_ID;
            ZetVar.pI2CData =(BYTE *) ZetVar.pCurReportData;
            ZetVar.wI2cTxLen = ZetVar.bI2cByteNumber;
            ZetVar.wI2cTxIdx = 0;
        }
			#else
        I2CDataFormatReset();   
			#endif
    }
}





/**
 * @brief  I2CTxNonAck()
 *
 *  Service the I2C None-ACK
 *
 * @return NULL
 *
 */
void I2CTxNonAck()
{
    ZetVar.wI2cRxIdx = 0;
    CLR_BIT(REG32_I2CON, STROBE_PEND);
    CLR_BIT(REG32_I2CON, I2C_STOP);
    CLR_BIT(REG32_I2C_TX_IF, I2CTX_IF);
}
/**
 * @brief  I2CTransmit()
 *
 *  Service the I2C TX operation
 *
 * @return NULL
 *
 */
void I2CTransmit(void)
{
    /// mix transmit data
    if((ZetVar.bTranType == TRAN_TYPE_MIX_DYNAMIC_MUTUALDEV) )
    {
        ZetVar.wI2cTxLen = ZetVar.bI2cByteNumber + (ZetVar.bDriveMaxAlg + 2) * (ZetVar.bSenseMaxAlg + 2) * MUTUAL_DATA_TYPE;
#ifdef FEATURE_HTYPE_DEV_RE_MAPPING
        ZetVar.wSysMode2 |= SYS_MODE2_TX_MUTUAL_DEV_MODE;
#endif
        if(ZetVar.wI2cTxIdx < ZetVar.bI2cByteNumber)
        {
            WRITE_REG(REG32_I2CBUF,  ZetVar.pI2CData[ZetVar.wI2cTxIdx]);
        }
        else
        {
            if(ZetVar.wSysMode2 & SYS_MODE2_RAW_MUTUAL_DEV)
            {
#ifdef FEATURE_CLUSTER_DEBUG_ENABLE
                ZetVar.pI2CData = (BYTE xdata *)&ZetVar.ClusterMatrix[0][0];
#else
                ZetVar.pI2CData = (BYTE xdata *)&AlgorithmDataPtr->sRawDev[0][0];
#endif
            }
            else
            {
                ZetVar.pI2CData = (BYTE xdata *)&AlgorithmDataPtr->sDev[0][0];
            }
            WRITE_REG(REG32_I2CBUF,  ZetVar.pI2CData[ZetVar.wI2cTxIdx- ZetVar.bI2cByteNumber]);
        }

        if(ZetVar.wI2cTxIdx == 0)
        {
            if(I2C_INT() == TRUE)
            {
                WRITE_REG(REG32_I2CBUF, I2C_NULL_PACKET_ID);
            }
            else
            {
                WRITE_REG(REG32_I2CBUF, I2C_MIX_DYNAMIC_MUTUALDEV_PACKET_ID);
            }
        }

    }
    else
    {
        WRITE_REG(REG32_I2CBUF,  ZetVar.pI2CData[ZetVar.wI2cTxIdx]);
    }

}

/**
 * @brief  I2CTxIsr()
 *
 *  Service the I2C TX(Transceive) operation
 *
 * @return NULL
 *
 */
void I2CTxIsr(void)
{
#ifdef FEATURE_STACK_USED_DEBUG
    if(__nds32__get_current_sp() < ZetVar.dwStackPointerMin)
    {
        ZetVar.dwStackPointerMin = __nds32__get_current_sp();
    }
#endif ///< for FEATURE_STACK_USED_DEBUG

    WRITE_REG(REG32_I2CON, STROBE_PEND);
    if(!(READ_REG(REG32_I2CON) & I2C_ACK))
    {
        ZetVar.bI2cStatus &= ~(I2C_STA_TX_START);
        I2CTxNonAck();
        return;
    }

    I2CTransmit();

    if(ZetVar.wI2cTxIdx == 0)
    {
        ZetVar.bI2cStatus |= I2C_STA_TX_START;
    }

    /// transfer data index ++
    ZetVar.wI2cTxIdx = ZetVar.wI2cTxIdx + 1;

    /// Set timeout
    ZetVar.bIntLowTimeout = ZetVar.bI2cIntLowTimeOutDefault;

    /// The wrong fetch data from the host
#ifdef FEATURE_CUSTOMER_PROTOCOL
    if(ZetVar.bWorkingState==WORKING_STATE_ZET_CMD_STATE)
    {
        //if((I2C_INT() == TRUE) && (!(ZetVar.bI2cStatus & I2C_STA_SRAM_RW_MODE)))
        if((I2C_INT() == TRUE) && (!(ZetVar.bI2cStatus & I2C_STA_SRAM_RW_MODE))&& ZetVar.bTranType == TRAN_TYPE_DYNAMIC)
        {        
           I2CDataFormatReset();
        }
    }
    else
    {
       //To control INT High/Low in Tx isr according cutsomer protocol requirement
       CustomerTxIsrINTControl();
    }

#else
  #ifdef REPORT_GESTURE_POINTS_LOG_METHOD
	  if((I2C_INT() == TRUE) && (!(ZetVar.bI2cStatus & I2C_STA_SRAM_RW_MODE)) && (ZetVar.bTranType == TRAN_TYPE_DYNAMIC))
	#else
    if((I2C_INT() == TRUE) && (!(ZetVar.bI2cStatus & I2C_STA_SRAM_RW_MODE)))
	#endif
    {
        I2CDataFormatReset();
    }
#endif
    ///-----------------------------------------------------///
    /// Stop Cycle:
    /// The last trasnfer data byte sent
    ///-----------------------------------------------------///
    I2CTxCheckEnd();

    /// Reset the Command Index to Zero
    ZetVar.wI2cRxIdx = 0;

    CLR_BIT(REG32_I2CON, STROBE_PEND);
    CLR_BIT(REG32_I2CON, I2C_STOP);

    CLR_BIT(REG32_I2C_TX_IF, I2CTX_IF);
}

/**
 * @brief  I2CRxIsr()
 *
 *  Service the I2C Rx(Receive) operation
 *
 * @return NULL
 *
 */
void I2CRxIsr(void)
{
    BYTE data bI2cData;
    /// Save the wI2cRxIdx
    bI2cData = READ_REG(REG32_I2CBUF);
    if(ZetVar.wI2cRxIdx < MAX_RX_BUF_LEN)
    {
        ZetVar.bI2CRxBuf[ZetVar.wI2cRxIdx] = bI2cData;
    }
    else
    {
        ZetVar.bI2CRxBuf[MAX_RX_BUF_LEN-1] = bI2cData;
    }
    ZetVar.bI2cData = bI2cData;

    ZetVar.bI2cStatus &= ~I2C_STA_TX_START;
    ZetVar.bI2cStatus &= ~I2C_STA_SRAM_RW_MODE; ///< 0: disable SRAM Read Mode

    ZetVar.wI2cRxIdx = ZetVar.wI2cRxIdx +  1;

    if(ZetVar.bI2cStatus & I2C_STA_PACKET_HEAD)
    {
        ZetVar.bI2CCmd = ZetVar.bI2cData; ///ZetVar.bI2CRxBuf[0];
    }

    if(ZetVar.bMTKFormatEnable  == TRUE)
    {
        if (ZetVar.bI2CCmd > MAX_MTK_MODE_SKPI_TPCMD)
        {
            I2CDispatchCmd();
            ZetVar.wI2cTxIdx = 0;
        }
    }
    else
    {
        I2CDispatchCmd();
    }

    if(ZetVar.bI2cRxLen > 0)
    {
        ZetVar.bI2cRxLen = ZetVar.bI2cRxLen -1;
    }

    CLR_BIT(REG32_I2CON, STROBE_PEND);
    CLR_BIT(REG32_I2CON, I2C_STOP);

    ///--------------------------------------------///
    /// Clear interrupt flag
    ///--------------------------------------------///
    WRITE_REG(REG32_I2C_RX_IF, I2C_RX_IF_CLEAR);
}

/**
 * @brief  I2CDispatchVenCmd()
 *
 *  Dispatch C0 Cmd
 *
 * @return NULL
 *
 */
void I2CDispatchVenCmd()
{
    BYTE  data i;
    BYTE  const code *ptr;
    BYTE  data cnt;
    BYTE  data cntshift;
    BYTE  data bLShift;
    BYTE  data bRShift;
    BYTE  data bStart;

    ZetVar.bVenCmd = ZetVar.bI2CRxBuf[1];

    ///----------------------------------------------------
    /// Check Command Mode
    ///----------------------------------------------------
    if(ZetVar.bVenCmd == VENCMD_ANALOG_SET1)
    {
        ///--------------------------------------------------------------------------------------------///
        /// Change the AD CTRL0 and Non-Drive and Sense Value
        ///
        /// I2CBuf[0] : [C1]
        /// I2CBuf[1] : [0]  									/// Vender Command
        /// I2CBuf[2] : [bAdcCtrl0Setup]			/// ADC_CTRL0 : Detect Range			 : Value = 5 / 2
        /// I2CBuf[3] : [bMutDriveSenseLevel] /// Sense Level 									 : Value = 0 / 1 / 2
        /// I2CBuf[4] : [bDgdCtrl0Setup]			/// DGD_CTRL0 : Decimation Ratio   : Value = 4
        /// I2CBuf[5] : [bDgdCtrl5Setup]			/// DGD_CTRL5 : Digital Filter Freq: Value = 3
        /// I2CBuf[6] : [bAdcCtrl8Setup]			/// ADC_CTRL8 : FrontEnd Clk Div   : Value = 5
        /// I2CBuf[7] : [bOptClkSetup]				/// OPT_CLK 	: AD CLK Div				 : Value = 3
        /// I2CBuf[8] : [0000_0000]						/// [4]: ADC_CTRL11.4              : Value = 0
        /// I2CBuf[9] : [XX]
        ///
        ///--------------------------------------------------------------------------------------------///
        ZetVar.wI2cRxIdx = 0;
    }
    else if(ZetVar.bVenCmd == VENCMD_GET_TRACE) ///<  C1-01
    {
        bLShift = 0;
        bRShift = 0;
        bStart  = 0;
        cntshift= 0;
        ///--------------------------------------------------
        /// [C1][01][TRACE][XX][XX][XX][XX][XX][XX][XX]
        ///     [TRACE] = 0x00 --> DRIVE
        ///     [TRACE] = 0x01 --> SENSE
        ///--------------------------------------------------
        ///----------------------------------
        ///  C1-01-00 : Mutual Alg Drive Axis
        ///----------------------------------
        if(ZetVar.bI2CRxBuf[2] == GET_TRACE_DRIVE) ///<  C1-01-00
        {
            ptr = &ZetDF.cTraceSetup.scPanelDriveAxis.bDri00;
#ifdef FEATURE_1T2R_ARCHITECTURE
            if(	((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE)	== TP_TYPE_1T2R)
                    || ((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE)  == TP_TYPE_1T2R_REVERSE)
              )
            {
                cnt = ZetDF.cGlobalData.scPanelInformation.bDriveAxisMax<<1;
                bRShift = 1;
            }
#ifdef FEATURE_1T2R_NO_EDGE
            else if((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE) == TP_TYPE_1T2R_NO_EDGE)
            {
                cnt = (ZetDF.cGlobalData.scPanelInformation.bDriveAxisMax<<1) - 2;
                bRShift = 1;
                bStart  = 1;
                cntshift= 1;
            }
#endif
            else
#endif
            {
                cnt = ZetDF.cGlobalData.scPanelInformation.bDriveAxisMax;
            }
        }
        ///----------------------------------
        ///  C1-01-01: Mutual Alg Sense Axis
        ///----------------------------------
        else if(ZetVar.bI2CRxBuf[2] == GET_TRACE_SENSE)  ///<  C1-01-01
        {
            ptr = &ZetDF.cTraceSetup.scPanelSenseAxis.bSen00;
#ifdef FEATURE_1T2R_ARCHITECTURE
            if(	((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE)	== TP_TYPE_1T2R)
                    ||((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE)  == TP_TYPE_1T2R_REVERSE)
              )
            {
                cnt = ZetDF.cGlobalData.scPanelInformation.bSenseAxisMax>>1;
                bLShift = 1;
            }
#ifdef FEATURE_1T2R_NO_EDGE
            else if((ZetDF.cFormatCtrl.scDataCtrl.bTPType & TP_TYPE_TYPE) == TP_TYPE_1T2R_NO_EDGE)
            {
                cnt = ZetDF.cGlobalData.scPanelInformation.bSenseAxisMax>>1;
                bLShift = 1;
            }
#endif
            else
#endif
            {
                cnt = ZetDF.cGlobalData.scPanelInformation.bSenseAxisMax;
            }
        }
        ///----------------------------------
        ///  C1-01-02: Force Alg Drive Axis
        ///----------------------------------
        else if(ZetVar.bI2CRxBuf[2] == GET_FORCE_TRACE_DRIVE) ///<  C1-01-02
        {
            ptr = &ZetDF.cForceTraceSetup.scForceDriveAxis.bForceDri00;
            cnt = ZetDF.cGlobalData.scForceTouchInformation.bFDriveAxisMax;
        }
        ///----------------------------------
        ///  C1-01-03: Force Alg Sense Axis
        ///----------------------------------
        else if(ZetVar.bI2CRxBuf[2] == GET_FORCE_TRACE_SENSE)  ///<  C1-01-03
        {
            ptr = &ZetDF.cForceTraceSetup.scForceSenseAxis.bForceSen00;
            cnt = ZetDF.cGlobalData.scForceTouchInformation.bFSenseAxisMax;
        }
        ///----------------------------------
        ///  C1-01-04 : Mutual HW Drive Axis
        ///----------------------------------
        else if(ZetVar.bI2CRxBuf[2] == GET_TRACE_HW_DRIVE) ///<  C1-01-04
        {
            ptr = &ZetDF.cTraceSetup.scPanelDriveAxis.bDri00;
            cnt = ZetDF.cGlobalData.scPanelInformation.bDriveAxisMax;
        }
        ///----------------------------------
        ///  C1-01-05 : Mutual HW Sense Axis
        ///----------------------------------
        else if(ZetVar.bI2CRxBuf[2] == GET_TRACE_HW_SENSE) ///<  C1-01-05
        {
            ptr = &ZetDF.cTraceSetup.scPanelSenseAxis.bSen00;
            cnt = ZetDF.cGlobalData.scPanelInformation.bSenseAxisMax;
        }
        else
        {
            ptr = &ZetDF.cTraceSetup.scPanelDriveAxis.bDri00;
            cnt = ZetDF.cGlobalData.scPanelInformation.bDriveAxisMax;
        }

        for(i=0; i<(cnt+cntshift); i++)
        {
            pGenBuf1[i] = *(ptr + ((i<<bLShift)>>bRShift));
        }

        ZetVar.wI2cTxLen = cnt;

        ZetVar.pI2CData = (BYTE *)(&pGenBuf1[bStart]);
        ZetVar.wI2cTxIdx = 0;
        ZetVar.wI2cRxIdx = 0;
        I2C_INT_LOW();
    }
    else if(ZetVar.bVenCmd == VENCMD_SET_TRAN_TYPE)  ///<  C1-02
    {
        ///---------------------------------------------------------------------///
        /// Set the transfer type
        ///---------------------------------------------------------------------///
        /// TRAN_TYPE_DYNAMIC		                (0x00)
        /// TRAN_TYPE_MUTUAL_SCAN_BASE          (0x01) ///< 16-bit
        /// TRAN_TYPE_MUTUAL_SCAN_DEV           (0x02)
        /// TRAN_TYPE_INIT_SCAN_BASE 		        (0x03)
        /// TRAN_TYPE_INIT_SCAN_DEV		      	  (0x04)
        /// TRAN_TYPE_KEY_MUTUAL_SCAN_BASE		  (0x05)
        /// TRAN_TYPE_KEY_MUTUAL_SCAN_DEV 		  (0x06)
        /// TRAN_TYPE_KEY_DATA  			          (0x07)
        /// TRAN_TYPE_MTK_TYPE  			          (0x0A)
        /// TRAN_TYPE_FOCAL_TYPE  		          (0x0B)
        /// TRAN_TYPE_MIX_DYNAMIC_MUTUALDEV     (0x0D)
        /// TRAN_TYPE_MIX_DYNAMIC_FRH           (0x0E)
        /// TRAN_TYPE_CHECKSUM_READ		          (0x0F)
        /// TRAN_TYPE_ADV_INIT_SCAN_DEV         (0x10)

        /// TRAN_TYPE_FORCE_SCAN_BASE         	(0x11)
        /// TRAN_TYPE_FORCE_SCAN_DEV  	       	(0x12)
        /// TRAN_TYPE_FORCE_C1C2_BASE  	       	(0x13)
        ///---------------------------------------------------------------------///
        ZetVar.wI2cRxIdx = 0;
        if((ZetVar.bI2CRxBuf[3] == 0x55) &&
                (ZetVar.bI2CRxBuf[4] == 0xAA))
        {
            if (ZetVar.bI2CRxBuf[2] < TRAN_TYPE_UNKNOWN)
            {
                ZetVar.bTranType = ZetVar.bI2CRxBuf[2];
                I2C_INT_HIGH();  ///< [KV] add for Dev Mode err-Transfer in 1st Round
            }
        }
    }
    // disable mark for avoid Zetouch query fail
    //#ifdef FEATURE_FORCE_TOUCH_SCAN
    else if(ZetVar.bVenCmd == VENCMD_TP_DETIAL_LEN_QUERY)  ///<  C1-03
    {
        pGenBuf1[0] = LOBYTE(VENCMD_TP_DETIAL_LEN_QUERY_BUF_LEN);
        pGenBuf1[1] = HIBYTE(VENCMD_TP_DETIAL_LEN_QUERY_BUF_LEN);
        ZetVar.wI2cTxLen = VENCMD_TP_DETIAL_LEN_QUERY_CMD_LEN;

        ZetVar.pI2CData = (BYTE *)(&pGenBuf1[0]);
        ZetVar.wI2cTxIdx = 0;
        ZetVar.wI2cRxIdx = 0;
        I2C_INT_LOW();
    }
    else if(ZetVar.bVenCmd == VENCMD_TP_DETIAL_INFO)  ///<  C1-04
    {
        pGenBuf1[TPINFO_BYTE_0] = ZetDF.cGlobalData.scForceTouchInformation.bFSenseAxisMax; ///< Don't use ZetVar.bSenseMaxAlg, because the ZetVar is not inited, yet
        pGenBuf1[TPINFO_BYTE_1] = ZetDF.cGlobalData.scForceTouchInformation.bFDriveAxisMax; ///< Don't use ZetVar.bDriveMaxAlg, because the ZetVar is not inited, yet
        pGenBuf1[TPINFO_BYTE_2] = ZetDF.cGlobalData.scPanelInformation.bSenseAxisMax; ///< Don't use ZetVar.bSenseMax, because the ZetVar is not inited, yet
        pGenBuf1[TPINFO_BYTE_3] = ZetDF.cGlobalData.scPanelInformation.bDriveAxisMax; ///< Don't use ZetVar.bDriveMax, because the ZetVar is not inited, yet
        ZetVar.wI2cTxLen = VENCMD_TP_DETIAL_LEN_QUERY_BUF_LEN;
        ZetVar.pI2CData = (BYTE *)(&pGenBuf1[0]);
        ZetVar.wI2cTxIdx = 0;
        ZetVar.wI2cRxIdx = 0;
        I2C_INT_LOW();
    }
    else if(ZetVar.bVenCmd == VENCMD_LOCK_IN_TEST_MODE)  ///<  C1-05
    {
        ZetVar.wSysMode |= (SYS_MODE_TP_TEST_EN);
        I2C_INT_HIGH();
    }
    //#endif
}



#ifdef FEATURE_CUSTOMER_PROTOCOL

#define UNCHANGE_IDX 0
#define RESET_RXIDX 1
#define RESET_TXIDX 2
#define RESET_TXRXIDX 3

void CustomerResponseArray(BYTE bTmpBuf[], WORD wI2cTxLen, BYTE bResetRxTxIdx)
{
  WORD wTmpIdx;
  ZetVar.wI2cTxIdx= 0;
  ZetVar.wI2cTxLen = wI2cTxLen;

  for(wTmpIdx=0; wTmpIdx < wI2cTxLen; wTmpIdx++)
  {
      CustomerVar.bCustomerBuf[wTmpIdx]= bTmpBuf[wTmpIdx];
  }
  //remark first, don't overflow	ZetVar.bWorkingSubState++;
  //  ZetVar.bWorkingSubState++;
  if(wI2cTxLen>0)
  {     	
      ZetVar.pI2CData = (BYTE *)(&CustomerVar.bCustomerBuf[0]);
			#ifdef NEW_I2C_PARSING_FLOW //don't reset RxIdx in new Parsing Flow
  	  #else
      if(bResetRxTxIdx == RESET_RXIDX)
      {
          ZetVar.wI2cRxIdx = 0;
      }
      else if(bResetRxTxIdx == RESET_TXIDX)
      {
          ZetVar.wI2cTxIdx = 0;
      }
      else if(bResetRxTxIdx == RESET_TXRXIDX)
      {
          ZetVar.wI2cTxIdx = 0;
          ZetVar.wI2cRxIdx = 0;
      }

      //  I2C_INT_LOW();
    	#endif
  }
}

#ifdef NEW_I2C_PARSING_FLOW
void CustomHfunc4Cmd03()
{ 
  ZetVar.bWorkingState = WORKING_STATE_CUSTOMER_NORMAL;	
}
void CustomHfunc4Cmd04()
{
			if(CustomerVar.bCustomCmd04Cnt < 255)
			{
				CustomerVar.bCustomCmd04Cnt++;
			
				if(CustomerVar.bCustomCmd04Cnt==2)
				{
					BYTE bTmpBuf[] = {0x81};
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
				}
				else if(CustomerVar.bCustomCmd04Cnt%2==1)
				{
					BYTE bTmpBuf[] = {0x00};
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
				}
			}
			if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL)
			{
				BYTE bTmpBuf[] = {0x00};
				CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
			}
}
void CustomHfunc4Cmd05()
{
            
		if(CustomerVar.bCustomCmd05Cnt < 255)
    {
			CustomerVar.bCustomCmd05Cnt++;

			if(CustomerVar.bCustomCmd05Cnt == 1)
      {
                   
					BYTE bTmpBuf[] = {0x06};
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
      }
			else if(CustomerVar.bCustomCmd05Cnt == 2)
      {
				
					BYTE bTmpBuf[] = {0x00};			
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
					
      }
			else if(CustomerVar.bCustomCmd05Cnt==3) 
      {			
					BYTE bTmpBuf[] = {0x02};
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
      }         
			else if(CustomerVar.bCustomCmd05Cnt==4) 
      {
					BYTE bTmpBuf[] = {0x00};
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
      }             
    }
        

		if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL)
    {

       if(CustomerVar.bWakeUpFlag==1)
       {
					BYTE bTmpBuf[] = {0x00};
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
                    CustomerVar.bWakeUpFlag=0;
       }
			 else
			 {
					BYTE bTmpBuf[] = {0x04};
					CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
			 }
    }

}
void CustomHfunc4Cmd06()
{
		BYTE bTmpSize = 80; //40;				
		ZetVar.wI2cTxIdx= 0;
		ZetVar.wI2cTxLen = bTmpSize;
		ZetVar.pI2CData = (BYTE *)(&CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferSendIdx][0]);
		ZetVar.wI2cRxIdx= 0;						 
	//	CustomerResponseArray((BYTE *)(&CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferSendIdx][0]), bTmpSize, RESET_RXIDX); 
			
}

void CustomHfunc4Cmd09()
{
	BYTE bTmpSize = 2;			
	CustomerResponseArray((BYTE *)(&CustomerVar.bcntBuffer[CustomerVar.bDoubleBufferSendIdx][0]), bTmpSize, RESET_RXIDX); 			
	//CustomerResponseArray((BYTE *)(&CustomerVar.bcntBuffer[0]), bTmpSize, RESET_RXIDX); 
}
void CustomHfunc4Cmd0A()
{				
	CustomerResponseArray((BYTE *)CustomRes4Cmd0A,4, RESET_RXIDX);  
}
void CustomHfunc4Cmd0E()
{		
    if(CustomerVar.bCustomCmd0eCnt < 255)
		{
			CustomerVar.bCustomCmd0eCnt++;
			BYTE bTmpBuf[] = {0x00};			
			CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
			if(CustomerVar.bCustomCmd0eCnt == 11)
			{
				BYTE bTmpBuf[] = {0x01};			
				CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
			}
			else if(CustomerVar.bWakeUpFlag == 0)
			{
				CustomerVar.bCustomCmd0eCnt = 12;
				BYTE bTmpBuf[]= {0x00};
				CustomerResponseArray(bTmpBuf, 1, RESET_RXIDX);
			}
			else if(CustomerVar.bWakeUpFlag == 1)
			{
				CustomerVar.bCustomCmd0eCnt = 12;
				BYTE bTmpBuf[] = {0x01};
				CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
			}
		}
}

void CustomHfunc4Cmd0E01()
{	
	CustomerVar.bWakeUpFlag = 1;
	/// Idle Mode Enabled
	//ZetVar.wSysMode |= (SYS_MODE_IDLE);		
	ZetVar.wSysMode |= (SYS_MODE_DEEP_SLEEP);		
	/// Test Mode Disabled
	ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;
	/// Cancel the previous interrupt, if any
	//	I2C_INT_HIGH();			
}

void CustomHfunc4Cmd0E00()
{
	ZetVar.bWorkingState = WORKING_STATE_CUSTOMER_NORMAL;
	/// Wake up the system
	ZetVar.wSysMode &= ~(SYS_MODE_IDLE | SYS_MODE_DEEP_SLEEP);
	/// Test Mode Disabled
	ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;
	/// Cancel the previous interrupt, if any
			//		 I2C_INT_HIGH();									

}


void CustomHfunc4Cmd15()
{				   
  #ifdef SPI_API_TEST
	 bFlashBuffer[0]=0x00;
	 bFlashBuffer[1]=0x01;
	 bFlashBuffer[2]=0x02;
	 bFlashBuffer[3]=0x03;
	 SPIFlashWrite(0x00,0xD0,0x00,4, &bFlashBuffer[0]);
	#endif

	CustomerResponseArray((BYTE *)CustomRes4Cmd15,4, RESET_RXIDX);
}
void CustomHfunc4Cmd1E()
{
	BYTE bTmpBuf[] = {0x05,0x0a};
	#ifdef SPI_API_TEST		
	SPIFlashSE();	
	#endif
	CustomerResponseArray(bTmpBuf,2, RESET_RXIDX); 
}
void CustomHfunc4Cmd22()
{
	BYTE bTmpBuf[] = {0xff};			
	CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
}

#ifdef SPI_API_TEST
void CustomHfunc4Cmd2A()
{ 	

		  BYTE bTmpBuf[] = {0x01,0xe0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x4c,\
										0x47,0x30,0x33,0x32,0x37,0x2d,0x30,0x31}; 	
		
      // Testcmd.unionCmd.CmdHF=I2CCmd[bDebugCNT].CmdHF;
	      SPIFlashRead(0x00,0xD0,0x00,8, &bFlashBuffer[0]);

			bTmpBuf[0]=bFlashBuffer[0];  //HIBYTE(wSizeI2CCmd);
			bTmpBuf[1]=bFlashBuffer[1]; //LOBYTE(wSizeI2CCmd);
			bTmpBuf[2]=bFlashBuffer[2]; //Testcmd2.unionCmd.addr[0];
			bTmpBuf[3]=bFlashBuffer[3]; //Testcmd2.unionCmd.addr[1];
			bTmpBuf[4]=bFlashBuffer[4]; //Testcmd2.Cmdkey[0];
			bTmpBuf[5]=bFlashBuffer[5]; //Testcmd2.Cmdkey[1];
			bTmpBuf[6]=bFlashBuffer[6]; //bSizebTestcmd2;
			bTmpBuf[7]=bFlashBuffer[7]; //Testcmd.unionCmd.addr[0];
			bTmpBuf[8]=bFlashBuffer[8];
			
			bTmpBuf[9]=0xAA; //bSizebTestcmd2Cmdkey;
			bTmpBuf[10]=CustomerVar.bDebugBuf[10]; //bSizebTestcmd2unionCmd;
			bTmpBuf[11]=CustomerVar.bDebugBuf[11]; //bSizebTest2cmd;
      bTmpBuf[12]=CustomerVar.bDebugBuf[12];
			bTmpBuf[13]= CustomerVar.bDebugBuf[13];
			bTmpBuf[14]= CustomerVar.bDebugBuf[14];
			bTmpBuf[15]= CustomerVar.bDebugBuf[15];						
     
		  CustomerResponseArray((BYTE *)bTmpBuf,21, RESET_RXIDX);

			//CustomerResponseArray((BYTE *)CustomRes4Cmd2A,21, RESET_RXIDX);  
}


#else
void CustomHfunc4Cmd2A()
{ 	
	CustomerResponseArray((BYTE *)CustomRes4Cmd2A,21, RESET_RXIDX);  
}
#endif

void CustomHfunc4Cmd2501()
{       
	BYTE bTmpBuf[] = {0x01};			
	CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
	I2C_INT_LOW();
}
void CustomHfunc4Cmd45()
{
	BYTE bTmpBuf[] = {0x00};
	CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);

}
void CustomHfunc4Cmd47()
{
	BYTE bTmpBuf[] = {0x01};			
	CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
}
void CustomHfunc4Cmd4B()
{
	CustomerResponseArray((BYTE *)CustomRes4Cmd4B,8, RESET_RXIDX);
}
void CustomHfunc4Cmd4E()
{	
	CustomerResponseArray((BYTE *)CustomRes4Cmd4E,6, RESET_RXIDX);
}
void CustomHfunc4Cmd51()
{
	BYTE bTmpBuf[] = {0x20};			
	CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
}
void CustomHfunc4CmdEE()
{
	 	if((CustomerVar.bCustomCmd00eeCnt==0)||(CustomerVar.bCustomCmd00eeCnt==5))
	 	{
			CustomerResponseArray((BYTE *)CustomRes4CmdEE, 24, RESET_RXIDX);
	 	}

		CustomerVar.bCustomCmd00eeCnt++;
		//[LM], move from Tx_Isr
	 	if(CustomerVar.bCustomCmd00eeCnt == 2)
		{
		CustomerVar.bINTtriggerCnt = 3;
		}
}
void CustomHfunc4CmdFF00()
{
	BYTE bTmpBuf[] = {0x00};			
	CustomerResponseArray(bTmpBuf,1, RESET_RXIDX);
}
void CustomHfunc4CmdFF01()
{
	CustomerResponseArray((BYTE *)CustomRes4CmdFF01, 10, RESET_RXIDX);
}
void CustomHfunc4CmdFF02()
{
	CustomerResponseArray((BYTE *)CustomRes4CmdFF02, 7, RESET_RXIDX);
}
void CustomHfunc4CmdFF03()
{
	CustomerResponseArray((BYTE *)CustomRes4CmdFF03,12, RESET_RXIDX);
}
void CustomHfunc4CmdFF04()
{
	CustomerResponseArray((BYTE *)CustomRes4CmdFF04,12, RESET_RXIDX);
}

void CustomHfunc4CmdFFF101()
{
        BYTE bTmpByte[8];
        BYTE bCnt;
        ZetVar.bWorkingState=ZetVar.bI2CRxBuf[2];
 
        CustomerVar.bDebugBuf[5]=ZetVar.bWorkingState;		 
        for(bCnt=0; bCnt<8; bCnt++)
        {
            bTmpByte[bCnt]=CustomerVar.bDebugBuf[bCnt];
        }
        CustomerResponseArray(bTmpByte,8, RESET_RXIDX);
}
void CustomHfunc4CmdFFF102()
{
  CustomHfunc4CmdFFF101();
}
void CustomHfunc4CmdFFF103()
{
	CustomHfunc4CmdFFF101();
}
void CustomHfunc4CmdFFFF()
{
  BYTE bTmpByte[8];
  BYTE bCnt;
  CustomerVar.bDebugBuf[5]=ZetVar.bWorkingState;
  for(bCnt=0; bCnt<8; bCnt++)
  {
      bTmpByte[bCnt]=CustomerVar.bDebugBuf[bCnt];
  }
  CustomerResponseArray(bTmpByte,8, RESET_RXIDX);
}

/**###################################
INT Control in TxIsr
##################################**/

void CustomerTxIsrINTControl()
{
	if(ZetVar.bI2CCmd == 0x05)		// 0502 0501 
	{
		if(I2C_INT() == FALSE)
		{ 					 
			I2C_INT_HIGH();
		}
	}
}

/**###################################
main parsing loop
##################################**/

void I2CDispatchCustomerCmd()
{
  //BYTE i;	
	WORD j;
	BYTE k;
  //BYTE *pTmpCmdkey;
	void (*pTmpCmdHF)();
	BYTE bHitCmdFlag;
	BYTE bLocalNonHitKeyFlag;
	I2CCmdType *pI2CCmd;
	BYTE btmpCmdKey;
 
	pI2CCmd=(I2CCmdType *)I2CCmd;
  if(ZetVar.wI2cRxIdx==1) bHitCmdFlag=0; //initial
	 
	 for(j=0;j<wCustomCmdElementNum;j++)
   {      
       if(I2CCmd[j].Cmdkey[0]==(BYTE)(ZetVar.wI2cRxIdx)) //size matched
			 {			
			   bLocalNonHitKeyFlag=0;
			   for(k=0;k<(BYTE)ZetVar.wI2cRxIdx;k++)
			   {	
	           btmpCmdKey=I2CCmd[j].Cmdkey[k+1];						 
		         if(k==0)
		         {
	              if(btmpCmdKey!=ZetVar.bI2CCmd)
	             	{
	                 bLocalNonHitKeyFlag=1;
									 break;
	             	}
		         }
						 else 
						 { 
								if(btmpCmdKey!=ZetVar.bI2CRxBuf[k])
								 {										       
                   bLocalNonHitKeyFlag=1;
									 break;
								 }
						 	}
			   }

				 //Hit command
				 if(bLocalNonHitKeyFlag==0)
				 {  
              bHitCmdFlag=1;
							pTmpCmdHF=I2CCmd[j].CmdHF;
							(pTmpCmdHF)();
							// ZetVar.wI2cRxIdx=0;   // consider 01 02 & 01 02 07, if Rxidx set as 0, 01 02 07 will never hit 
							break;
				 }				 
			 }
       pI2CCmd++;
   }

	 //check bHitKeyFlag when max KeyOrder, reset RxIdx
	 if((BYTE)ZetVar.wI2cRxIdx >=bCustomMaxKeyLength && bHitCmdFlag==0) 
	 //if(bHitCmdFlag==0) 
	 {
  //    ZetVar.wI2cRxIdx=0;  // unnecessary, it's enough to be reset by I2CTxRxReset
	 } 
}

#else

void CustomerTxIsrINTControl()
{   
	 if((I2C_INT() == TRUE) && (!(ZetVar.bI2cStatus & I2C_STA_SRAM_RW_MODE))&&(CustomerVar.bCustomCmd5901Cnt>=1))
		{
				I2CDataFormatReset();
		}

		//INT high after Tx 2nd BYTE at 59 01 command
		if((I2C_INT() == FALSE) && CustomerVar.bLastCustomCmdBuf[0]==0x59 &&CustomerVar.bLastCustomCmdBuf[1]==0x01 && ZetVar.wI2cTxIdx>=2)
		{
				I2C_INT_HIGH();
				CustomerVar.bLastCustomCmdBuf[0]=0;
				CustomerVar.bLastCustomCmdBuf[1]=0;
		}

		//INT high after Tx 3rd BYTE at 58 01 command
		if((I2C_INT() == FALSE) && CustomerVar.bLastCustomCmdBuf[0]==0x58 &&CustomerVar.bLastCustomCmdBuf[1]==0x01 && ZetVar.wI2cTxIdx>=3)
		{
				I2C_INT_HIGH();
				CustomerVar.bLastCustomCmdBuf[0]=0;
				CustomerVar.bLastCustomCmdBuf[1]=0;
		}

		//INT low after Tx last BYTE at  58 01 command triggered (in Normal mode)
		if((I2C_INT() == TRUE) && CustomerVar.bLastCustomCmdBuf[3]==0x58 &&CustomerVar.bLastCustomCmdBuf[4]==0x01 && ZetVar.wI2cTxIdx>=10)
		{
				I2C_INT_LOW();
				CustomerVar.bLastCustomCmdBuf[3]=0;
				CustomerVar.bLastCustomCmdBuf[4]=0;
		}

		//INT low after Tx last BYTE at  59 01 command triggered (in Normal mode)
		if((I2C_INT() == TRUE) && CustomerVar.bLastCustomCmdBuf[3]==0x59 &&CustomerVar.bLastCustomCmdBuf[4]==0x01 && ZetVar.wI2cTxIdx>=ZetVar.wI2cTxLen)
		{
				I2C_INT_LOW();
				CustomerVar.bLastCustomCmdBuf[3]=0;
				CustomerVar.bLastCustomCmdBuf[4]=0;
		}
}

void I2CDispatchCustomerCmd()
{
    // use multi-level BYTE match to parsing
    if(ZetVar.bI2CCmd == 0x00)
    {
        if((ZetVar.wI2cRxIdx==2) &&
                (ZetVar.bI2CRxBuf[1]==0x00)	&&
                (CustomerVar.bCustomCmd0000Cnt==0))
        {
            // BYTE bTmpBuf[]={0x82,0x2C,0x30,0xAA,0xE1,0x1E,0x12,0x22};
            BYTE bTmpBuf[]= {0x82,0x2C,0x30,0xAA,0x1E,0x12,0x22};
            CustomerResponseArray(bTmpBuf, 7, RESET_RXIDX);
            CustomerVar.bCustomCmd0000Cnt++;
            //	I2C_INT_LOW();
        }
    }
    else if(ZetVar.bI2CCmd == 0x07)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x00)
        {
#if 0
            BYTE bCustomCmd0700Cnt0Buf[]= {0x25,0xD6,0x00,0x81,0x00,0x00,0x2C,0x58,0x01,0x00,0x00,0x00,0x05,0x59,0x01,0x09,0x00,0x00,0x06,0x63, \
                                           0x01,0x06,0x00,0x01,0x26,0x6A,0x01,0x07,0x00,0x00,0x47,0x72,0x01,0x6F,0x00,0x00,0x07,0xE2,0x01,0x03, \
                                           0x00,0x00,0x08,0xE6,0x01,0x0D,0x00,0x00,0x0F,0xF4,0x01,0x0A,0x00,0x01,0x12,0xFF,0x01,0x01,0x00,0x00, \
                                           0x13,0x01,0x02,0x05,0x00,0x01,0x17,0x07,0x02,0x0F,0x00,0x01,0x19,0x17,0x02,0x14,0x00,0x01,0x28,0x2C, \
                                           0x02,0x04,0x00,0x00,0x2A,0x31,0x02,0x0C,0x00,0x00,0x2E,0x3E,0x02,0x09,0x00,0x01,0x2F,0x48,0x02,0x19, \
                                           0x00,0x00,0x37,0x62,0x02,0x06,0x00,0x00,0x38,0x69,0x02,0x23,0x00,0x01,0x3D,0x8D,0x02,0x04,0x01,0x01, \
                                           0x41,0x97,0x02,0x13,0x00,0x01,0x42,0xAB,0x02,0x02,0x00,0x01,0x45,0xAE,0x02,0x08,0x00,0x01,0x46,0xB7, \
                                           0x02,0x09,0x07,0x01,0x48,0x07,0x03,0x4F,0x00,0x01,0x4E,0x57,0x03,0x07,0x00,0x00,0x50,0x5F,0x03,0x06, \
                                           0x00,0x00,0x54,0x66,0x03,0x03,0x00,0x01,0x64,0x6A,0x03,0x35,0x00,0x0C,0x65,0xA0,0x03,0x18,0x00,0x00, \
                                           0x66,0xB9,0x03,0x1C,0x00,0x01,0x67,0xD6,0x03,0x0D,0x01,0x01,0x68,0xF2,0x03,0x0A,0x00,0x00,0x69,0xFD, \
                                           0x03,0x11,0x00,0x00
                                          };
            CustomerResponseArray(bCustomCmd0700Cnt0Buf, 204, RESET_RXIDX);
#else
            ZetVar.wI2cTxIdx= 0;
            ZetVar.wI2cTxLen = 204;
            ZetVar.wI2cRxIdx = 0;
            ZetVar.pI2CData = (BYTE *)(&bCustomCmd0700Cnt0Buf[0]);
#endif
        }
    }
    else if(ZetVar.bI2CCmd == 0x01)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x02)
        {
            if((CustomerVar.bCustomCmd0102Cnt%3)==1)
            {
                BYTE bTmpByte[]= {0x07};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
                CustomerVar.bCustomCmd0102Cnt++;
            }
            else if((CustomerVar.bCustomCmd0102Cnt%3)==2)
            {
                BYTE bTmpByte[]= {0x03};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
                CustomerVar.bCustomCmd0102Cnt++;
            }
        }
        //else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x02 && ZetVar.bI2CRxBuf[2]==0x07 && (ZetVar.bCustomCmd0102Cnt%3)==0)
        else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x02 && ZetVar.bI2CRxBuf[2]==0x07)
        {
            CustomerVar.bCustomCmd0102Cnt=1;	//reset to 1
            ZetVar.wI2cRxIdx = 0;
            ZetVar.bI2cRxLen = 0;
        }
    }
    else if(ZetVar.bI2CCmd == 0x04)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x00)
        {
            BYTE bTmpByte[]= {0x1E};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x05)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x00)
        {
            BYTE bTmpByte[]= {0x12};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x57)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
            BYTE bTmpByte[]= {0x00};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x58)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
        {
            //make sure no other 58 01 xx command
            CustomerVar.bLastCustomCmdBuf[0]=0x58;
            CustomerVar.bLastCustomCmdBuf[1]=0x01;
            if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_INITIAL)
            {
                // if(CustomerVar.bCustomCmd5801Cnt>=1 &&CustomerVar.bCustomCmd5801Cnt<=2)
                // if(CustomerVar.bCustomCmd5801Cnt>=1 &&CustomerVar.bCustomCmd5801Cnt<=4)
                if(CustomerVar.bCustomCmd5801Cnt>=0 && CustomerVar.bCustomCmd5801Cnt<=3)
                {
                    CustomerVar.bINTtriggerCnt=1; // ~10ms, a little long...
                    //CustomerVar.bLastCustomCmdBuf[3]=0x58;  //trigger INT_LOW after tx 58 01 response data
                    //CustomerVar.bLastCustomCmdBuf[4]=0x01;
                    // I2C_INT_LOW();
                }

                // if(CustomerVar.bCustomCmd5801Cnt==3)  CustomerVar.bINTtriggerCnt=6;

                if(CustomerVar.bCustomCmd5801Cnt==0)
                {
                    //BYTE bTmpByte[]={0x01,0x23,0x00,0x03,0x00,0xF0,0x05,0x00,0x00,0x00};
#if FEATURE_BM_NEW
                    BYTE bTmpByte[]= {0x01,0x23,0x00,0x03,0x00,0x80,0x08,0x00,0x00,0x00}; //Atmel MainBoard
#else
                    //BYTE bTmpByte[]={0x01,0x23,0x00,0x03,0x00,0xE0,0x06,0x00,0x00,0x00}; //ST MainBoard
                    BYTE bTmpByte[]= {0x05,0x01,0x80,0x66,0xE9,0x25,0x00,0x00,0x00,0x00}; //ST MainBoard
#endif

                    if(CustomerVar.bCustomerUpgradeFlag==1)
                    {
                        //BYTE bTmpByte2[]={0x07,0x01,0x80,0x66,0xE9,0x25,0x00,0x00,0x00,0x00}; //Upgrade case
                        CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    }
                    else
                    {
                        CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    }

                    if(CustomerVar.bCustomCmd5801Cnt<250)
                    {
                        CustomerVar.bCustomCmd5801Cnt++;
                    }

                }
                else if(CustomerVar.bCustomCmd5801Cnt==1)
                {
                    //BYTE bTmpByte[]={0x01,0x01,0x40,0x66,0xE9,0x25,0x00,0x00,0x00,0x00};
                    BYTE bTmpByte[]= {0x01,0x23,0x00,0x03,0x00,0xD0,0x07,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    if(CustomerVar.bCustomCmd5801Cnt<250)
                    {
                        CustomerVar.bCustomCmd5801Cnt++;
                    }
                }
                else if(CustomerVar.bCustomCmd5801Cnt==2)
                {
                    BYTE bTmpByte[]= {0x01,0x01,0x00,0x66,0xE9,0x25,0x00,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    if(CustomerVar.bCustomCmd5801Cnt<250)
                    {
                        CustomerVar.bCustomCmd5801Cnt++;
                    }
                }
                else if(CustomerVar.bCustomCmd5801Cnt==3)
                {
                    BYTE bTmpByte[]= {0x02,0x01,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    if(CustomerVar.bCustomCmd5801Cnt<250)
                    {
                        CustomerVar.bCustomCmd5801Cnt++;
                    }
                }
                else if(CustomerVar.bCustomCmd5801Cnt==4)
                {
                    BYTE bTmpByte[]= {0x01,0x01,0x00,0x66,0xE9,0x25,0x00,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    if(CustomerVar.bCustomCmd5801Cnt<250)
                    {
                        CustomerVar.bCustomCmd5801Cnt++;
                    }
                }
                else
                {
                    BYTE bTmpByte[]= {0x01,0x01,0x00,0x66,0xE9,0x25,0x00,0x00,0x00,0x00};
                    //		BYTE bTmpByte[]={0x01,0x01,0x40,0x66,0xE9,0x25,0x00,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    if(CustomerVar.bCustomCmd5801Cnt<250)
                    {
                        CustomerVar.bCustomCmd5801Cnt++;
                    }
                }

                if(CustomerVar.bCustomCmd5801Cnt >4) ZetVar.bWorkingState=WORKING_STATE_CUSTOMER_NORMAL;

            }
            else if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL)
            {
                //Store Coord. data into Tx buffer for 58 01 cmd

                // BYTE bTmpByte[]={0x01,0x23,0x00,0x03,0x00,0x50,0x07,0x00,0x00,0x00};
                BYTE bTmpByte[]= {0x01,0x01,0x00,0x66,0xE9,0x25,0x00,0x00,0x00,0x00};
                //special cmd 65 01 behind 58 01, need response special pattern
                if(CustomerVar.bLastCustomCmdBuf[5]==0x65&&CustomerVar.bLastCustomCmdBuf[6]==0x01)
                {
                    if(CustomerVar.bLastCustomCmdBuf[7]==0x01)
                    {
                        bTmpByte[2]=0x10;             //Need to DO!!!
                    }
                    CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                    CustomerVar.bLastCustomCmdBuf[5]=0x00;
                    CustomerVar.bLastCustomCmdBuf[6]=0x00;
                    CustomerVar.bLastCustomCmdBuf[7]=0xFF;
                }
#if defined(FEATURE_REAL_KEY) ||defined(FEATURE_VIRTUAL_KEY)
                //report Key information first
                else if(CustomerVar.bCustomerKeyReportFlag[CustomerVar.bDoubleBufferIdx])
                {
                    BYTE bTmpBuf[]= {0x01,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
                    if(CustomerVar.bCustomerKeyValidByte[CustomerVar.bDoubleBufferIdx])
                    {
                        bTmpBuf[2]=0x80;
                        bTmpBuf[3]=CustomerVar.bCustomerKeyValidByte[CustomerVar.bDoubleBufferIdx];
                        //swap Key mapping for right & left key
                        bTmpBuf[3]=(bTmpBuf[3]&0xFA);
                        bTmpBuf[3]=bTmpBuf[3]|((CustomerVar.bCustomerKeyValidByte[CustomerVar.bDoubleBufferIdx]&0x01)<<2);
                        bTmpBuf[3]=bTmpBuf[3]|((CustomerVar.bCustomerKeyValidByte[CustomerVar.bDoubleBufferIdx]&0x04)>>2);
                    }

                    CustomerResponseArray(bTmpBuf, 10 ,RESET_RXIDX);
                    CustomerVar.bCustomerKeyReportFlag[CustomerVar.bDoubleBufferIdx]=0;

                    //To trigger INT LOW, after 58 01 last BYTE sent
                    //if any point need report ,trigger again after Key packet sent
                    if(CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][0]>0)
                    {
                        CustomerVar.bLastCustomCmdBuf[3]=0x58;
                        CustomerVar.bLastCustomCmdBuf[4]=0x01;
                    }
                    // CustomerVar.bLastCustomCmdBuf[3]=0x58;
                    // CustomerVar.bLastCustomCmdBuf[4]=0x01;

                }
#endif
                //report Coord. information
                else if(CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][0]>0)
                {
                    /*
                    BYTE Idx;
                    for(Idx=0; Idx<10; Idx++)
                    {
                        bTmpByte[Idx] = CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][Idx];
                    }
                    CustomerResponseArray(bTmpByte, 10 ,RESET_RXIDX);
										*/
                    ZetVar.wI2cTxIdx= 0;
                    ZetVar.wI2cTxLen = 10;
			              ZetVar.pI2CData = (BYTE *)(&CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][0]);
			              ZetVar.wI2cRxIdx= 0;

                    //CustomerResponseArray(CustomerVar.bDoubleBuffer[ZetVar.bDoubleBufferIdx][0], 10);

                    //real count-down after 58 01 cmd to get Coord. Buffer data
                    // if(CustomerVar.bCustomerReSendCNT>0) CustomerVar.bCustomerReSendCNT--;

                    //touch number >1, remain data need to be accessed by 59 01,
                    if(CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][0]>1)
                    {
                        //To trigger INT LOW, after 58 01 last BYTE sent
                        CustomerVar.bLastCustomCmdBuf[3]=0x58;
                        CustomerVar.bLastCustomCmdBuf[4]=0x01;
                    }

                }
                else
                {
                    CustomerResponseArray(bTmpByte,10 ,RESET_RXIDX);
                }
                //CustomerVar.bI2CKeepSendflag=1;

                ZetVar.bI2CRxBuf[1]=0xFF; //clear sub-command buffer
            }

        }
    }
    else if(ZetVar.bI2CCmd == 0x59)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
        {
            //make sure No other 59 01 xx command!!!
            //trigger INT HIGH after read
            CustomerVar.bLastCustomCmdBuf[0]=0x59;
            CustomerVar.bLastCustomCmdBuf[1]=0x01;

            if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_INITIAL)
            {

                if(CustomerVar.bWakeUpFlag==1)
                {
                    //wake-up pattern!!, may also add some condition
                    BYTE bTmpBuf[]= {0xFF,0x00,0x66,0xF9,0x25,0x00,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpBuf, 9 ,RESET_RXIDX);
                    CustomerVar.bWakeUpFlag=0;
                }
                else if(CustomerVar.bCustomCmd5901Cnt==0)
                {
#if 0

#ifdef FEATURE_BM_NEW
                    //Atmel MainBoard
                    BYTE bCustomCmd5901Cnt0Buf[]= {0x01,0x80,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01, \
                                                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x10,0x66,0xE9, \
                                                   0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00, \
                                                   0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00, \
                                                   0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF, \
                                                   0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66, \
                                                   0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25, \
                                                   0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00, \
                                                   0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00, \
                                                   0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                                   0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9, \
                                                   0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00, \
                                                   0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9, \
                                                   0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                                   0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9, \
                                                   0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00, \
                                                   0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00,0xFF,0x10,0x66,0xE9,0x25
                                                  };
#else //ST Mainboard
                    /*
                    BYTE bCustomCmd5901Cnt0Buf[]={0x01,0x80,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01, \
                    0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x10,0x6F,0xB9, \
                    0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                    0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00, \
                    0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF, \
                    0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F, \
                    0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99, \
                    0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00, \
                    0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00, \
                    0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10, \
                    0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
                    0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                    0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00, \
                    0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF, \
                    0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F, \
                    0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99, \
                    0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00};
                    */
                    //Atmel Mainboard response pattern before upgrade procedure

                    BYTE bCustomCmd5901Cnt0Buf[]= {0x01,0x80,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x01, \
                                                   0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x23,0x00,0x02,0x01,0x00,0x00,0x00,0x00,0x00,0x01,0x10,0x6F,0xB9, \
                                                   0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                                                   0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00, \
                                                   0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF, \
                                                   0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F, \
                                                   0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99, \
                                                   0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00, \
                                                   0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00, \
                                                   0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                                   0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
                                                   0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                                                   0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
                                                   0xFF ,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10, \
                                                   0x6F,0xB9,0x99,0x00,	0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9, \
                                                   0x99,0x00,0x00,0x00,	0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99,0x00, \
                                                   0x00,0x00,0x00,0xFF,	0x10,0x6F,0xB9,0x99,0x00,0x00,0x00,0x00,0xFF,0x10,0x6F,0xB9,0x99
                                                  };

#endif
                    CustomerResponseArray(bCustomCmd5901Cnt0Buf, 333 ,RESET_RXIDX);

#else
                    ZetVar.wI2cTxIdx= 0;
                    ZetVar.wI2cTxLen = 333;
                    ZetVar.wI2cRxIdx = 0;
                    ZetVar.pI2CData = (BYTE *)(&bCustomCmd5901Cnt0Buf[0]);
#endif



                    if(CustomerVar.bCustomCmd5901Cnt <250)
                    {
                        CustomerVar.bCustomCmd5901Cnt++;
                    }
                    CustomerVar.bI2CKeepSendflag=1;
                    ZetVar.bI2CRxBuf[1]=0xFF; //clear sub-command buffer

                }
                else if(CustomerVar.bCustomCmd5901Cnt==1)
                {
                    BYTE bTmpBuf[]= {0x03,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                     0x07,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                     0x23,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00, \
                                     0x01,0x10,0x66,0xE9,0x25,0x00,0x00,0x00,0x00
                                    };

                    CustomerResponseArray(bTmpBuf, 54 ,RESET_RXIDX);

                    if(CustomerVar.bCustomCmd5901Cnt==1)
                    {
                        CustomerVar.bINTtriggerCnt=8;
                    }

                    if(CustomerVar.bCustomCmd5901Cnt <250)
                    {
                        CustomerVar.bCustomCmd5901Cnt++;
                    }
                }
                else if(CustomerVar.bCustomCmd5901Cnt==2)
                {
                    BYTE bTmpBuf[]= {0x23,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpBuf, 9 ,RESET_RXIDX);

                    if(CustomerVar.bCustomCmd5901Cnt==2)
                    {
                        CustomerVar.bINTtriggerCnt=20;
                    }
                    if(CustomerVar.bCustomCmd5901Cnt <250)
                    {
                        CustomerVar.bCustomCmd5901Cnt++;
                    }

                }
                else
                {

                    if(CustomerVar.bWakeUpFlag==1)
                    {
                        //wake-up pattern!!, may also add some condition
                        BYTE bTmpBuf[]= {0xFF,0x00,0x66,0xF9,0x25,0x00,0x00,0x00,0x00};
                        CustomerResponseArray(bTmpBuf, 9 ,RESET_RXIDX);
                        CustomerVar.bWakeUpFlag=0;
                    }
                    else //avoid case miss
                    {
                        // BYTE bTmpBuf[]={0x23,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00};
                        BYTE bTmpBuf[]= {0xFF,0x00,0x66,0xF9,0x25,0x00,0x00,0x00,0x00};
                        CustomerResponseArray(bTmpBuf, 9 ,RESET_RXIDX);
                    }

                    if(CustomerVar.bCustomCmd5901Cnt <250)
                    {
                        CustomerVar.bCustomCmd5901Cnt++;
                    }
                }

            }
            else if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL)
            {
                if(CustomerVar.bWakeUpFlag==1)
                    //if(ZetVar.bWakeUpFlag==1&&ZetVar.bCustomerReSendCNT==0)
                {
                    //wake-up pattern!!, may also add some condition
                    BYTE bTmpBuf[]= {0xFF,0x00,0x66,0xF9,0x25,0x00,0x00,0x00,0x00};
                    CustomerResponseArray(bTmpBuf, 9 ,RESET_RXIDX);
                    CustomerVar.bWakeUpFlag=0;
                }
                else
                {
                    // if touch number >1 or need to resend, Store Coord. Data into Tx buffer for 59 01 cmd
                    if(CustomerVar.bCustomerReSendCNT>0)
                    {
                        BYTE bTmpSize;
                        //size = (touch_number-1) * 9
                        bTmpSize=(CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][0]-1)*9;
                        //CustomerResponseArray((BYTE *)(&CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][10]), bTmpSize, RESET_RXIDX);
                        ZetVar.wI2cTxIdx= 0;
                    		ZetVar.wI2cTxLen = bTmpSize;
			              		ZetVar.pI2CData = (BYTE *)(&CustomerVar.bDoubleBuffer[CustomerVar.bDoubleBufferIdx][10]);
			              		ZetVar.wI2cRxIdx= 0;												
                    }
                    else
                    {
                        //wake-up pattern!!, may also add some condition
                        BYTE bTmpBuf[]= {0xFF,0x00,0x66,0xF9,0x25,0x00,0x00,0x00,0x00};
                        CustomerResponseArray(bTmpBuf, 9, RESET_RXIDX);

                        
                        CustomerVar.bWakeUpFlag=0;
                    }
                }
            }
        }
    }
    else if(ZetVar.bI2CCmd == 0x63)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
            BYTE bTmpByte[]= {0x03};
            CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
        }
        else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x03 && ZetVar.bI2CRxBuf[2]==0x01 )
        {
            ZetVar.wI2cRxIdx = 0;
        }
    }
    else if(ZetVar.bI2CCmd == 0x64)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
        {
            BYTE bTmpByte[]= {0x00};
            CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
        }
        else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && ZetVar.bI2CRxBuf[2]==0x55 )
        {
            ZetVar.wI2cRxIdx = 0;
        }
    }
    else if(ZetVar.bI2CCmd == 0x65) // 65 01, 65 01 01
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01&&CustomerVar.bCustomCmd6501Cnt>0)
        {
            if((CustomerVar.bCustomCmd6501Cnt%3)==1)
            {
                BYTE bTmpByte[]= {0x01};
                CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
                // CustomerVar.bINTtriggerCnt=0x13;
                I2C_INT_LOW();
                CustomerVar.bCustomCmd6501Cnt++;
                CustomerVar.bLastCustomCmdBuf[7]=0x01;
            }
            else if((CustomerVar.bCustomCmd6501Cnt%3)==2)
            {
                BYTE bTmpByte[]= {0x00};
                CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
                // CustomerVar.bINTtriggerCnt=0x13;
                I2C_INT_LOW();
                CustomerVar.bCustomCmd6501Cnt=0;
                CustomerVar.bLastCustomCmdBuf[7]=0x00;
            }
            //special command,
            CustomerVar.bLastCustomCmdBuf[5]=0x65;
            CustomerVar.bLastCustomCmdBuf[6]=0x01;

        }
        else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && ZetVar.bI2CRxBuf[2]==0x01)
        {
            ZetVar.wI2cRxIdx = 0;
            ZetVar.bI2cRxLen = 0;
            CustomerVar.bCustomCmd6501Cnt++;

        }
    }
    else if(ZetVar.bI2CCmd == 0x68) //68 01 , 68 01 01, 68 01 10, 68 01 11, 68 01 FC
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
        {
            if(CustomerVar.bCustomCmd6801Cnt>1)
            {
                if(CustomerVar.bCustomCmd6801nnCnt==1)
                {
                    BYTE bTmpByte[]= {0x10};
                    CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
                    if(CustomerVar.bCustomCmd6801Cnt>0)
                    {
                        CustomerVar.bCustomCmd6801Cnt--;
                    }
                }
                else
                {
                    BYTE bTmpByte[]= {0x01};
                    CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
                    if(CustomerVar.bCustomCmd6801Cnt>0)
                    {
                        CustomerVar.bCustomCmd6801Cnt--;
                    }
                }
            }
            else if(CustomerVar.bCustomCmd6801Cnt==1)
            {
                //  if(CustomerVar.bCustom_Cmd680101_Cnt==1)
                {
                    BYTE bTmpByte[]= {0x00};
                    CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
                    CustomerVar.bCustomCmd6801Cnt=0;
                }
            }
        }
        else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && (ZetVar.bI2CRxBuf[2]==0x10||ZetVar.bI2CRxBuf[2]==0x01||ZetVar.bI2CRxBuf[2]==0x11))
        {
            //  BYTE bTmpCNT[]={40,43,43,44,42,43,44,43,   57,47,48,43,40,41,42,40,   61, 42, 41, 42, 44, 43, 43};
            BYTE bTmpCNT[]= {24,25,26,25,22,23,22,36,25,25};

            //CustomerVar.bCustomCmd6801Cnt=40; //Default value set as 40
            CustomerVar.bCustomCmd6801Cnt=24; //Default value set as 40
            //if(CustomerVar.bCustomCmd6801nnCnt<23)
            if(CustomerVar.bCustomCmd6801nnCnt<10)
            {
                CustomerVar.bCustomCmd6801Cnt=bTmpCNT[CustomerVar.bCustomCmd6801nnCnt];
            }
            CustomerVar.bCustomCmd6801Cnt++;

            //Enter Normal mode !!!
            if(CustomerVar.bCustomCmd6801nnCnt> 0)
            {
                //ZetVar.bWorkingState=WORKING_STATE_CUSTOMER_NORMAL;
            }

            ZetVar.wI2cRxIdx = 0;
            ZetVar.bI2cRxLen = 0;
            CustomerVar.bCustomCmd6801nnCnt++;
        }

    }

    else if(ZetVar.bI2CCmd == 0x6A)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
        {
            BYTE bTmpBuf[]= {0x00};
            CustomerResponseArray(bTmpBuf, 1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x6B)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
#if FEATURE_BM_NEW
            BYTE bTmpByte[]= {0x32}; //Atmel MainBoard
#else
            BYTE bTmpByte[]= {0x33}; //ST MainBoard
#endif

            if(CustomerVar.bCustomerUpgradeFlag==1)
            {
                bTmpByte[0]=0x32;
            }

            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x6D)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
            BYTE bTmpByte[]= {0x06};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x77)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
            BYTE bTmpByte[]= {0x7F};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x78)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
            BYTE bTmpByte[]= {0x07};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x82)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
            BYTE bTmpByte[]= {0x37};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0x83)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
        {
            BYTE bTmpByte[]= {0x04};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
    }
    else if(ZetVar.bI2CCmd == 0xAB) // AB 02 00, AB 02 03
    {
        if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x02 && (ZetVar.bI2CRxBuf[2]==0x03||ZetVar.bI2CRxBuf[2]==0x00))
        {
            ZetVar.wI2cRxIdx = 0;
            ZetVar.bI2cRxLen = 0;
        }
    }
    else if(ZetVar.bI2CCmd == 0xBA)
    {
        if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x03 &&ZetVar.bI2CRxBuf[2]==0x01)
        {
            ZetVar.wI2cRxIdx = 0;
            ZetVar.bI2cRxLen = 0;
            CustomerVar.bINTtriggerCnt=9; //11, 13
        }
    }
    else if(ZetVar.bI2CCmd == 0xD3)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x00)
        {
            BYTE bTmpBuf[]= {0xEB,0x36,0x56};
            CustomerResponseArray(bTmpBuf, 3, UNCHANGE_IDX);
        }
        else if((ZetVar.wI2cRxIdx>=3) &&
                (ZetVar.bI2CRxBuf[1]==0x00) &&
                (ZetVar.bI2CRxBuf[2]==0x00||ZetVar.bI2CRxBuf[2]==0x01||ZetVar.bI2CRxBuf[2]==0x02||ZetVar.bI2CRxBuf[2]==0x03))
        {
            //do nothing or clear whole buffer, let whole Write command go through...
            ZetVar.wI2cRxIdx=4; //keep over-write buffer[4] to avoid buffer overflow
            CustomerVar.bCustomerUpgradeFlag=1;
        }
    }
    else if(ZetVar.bI2CCmd == 0xD5) // D5 03, D5 03 3F, D5 03 C6
    {

        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03 && CustomerVar.bCustomCmd5901Cnt==1)
        {
            BYTE bTmpByte[]= {0xC6};
            CustomerResponseArray(bTmpByte,1, RESET_RXIDX);
        }
        else if((ZetVar.wI2cRxIdx==3) &&
                (ZetVar.bI2CRxBuf[1]==0x03) &&
                (ZetVar.bI2CRxBuf[2]==0x3F||ZetVar.bI2CRxBuf[2]==0xC6))
        {
            if(ZetVar.bI2CRxBuf[2]==0x3F)
            {
                CustomerVar.bINTtriggerCnt=1;
                //   if(CustomerVar.bCustomCmd6801nnCnt>5)   // trigger to enter Normal Mode
                //ZetVar.bWorkingState=WORKING_STATE_CUSTOMER_NORMAL;
            }
            ZetVar.wI2cRxIdx = 0;
            ZetVar.bI2cRxLen = 0;
        }

    }
    else if(ZetVar.bI2CCmd == 0xD8)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x00)
        {
#if 0
            if((CustomerVar.bCustomCmd6801nnCnt%9)==1)
            {
                BYTE bCustomCmdD801Cnt1Buf[]= {0x04,0x00,0x03,0x00,0x11,0x00,0x10,0x00,0x04,0x00,0x0C,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x06,0x00, \
                                               0x08,0x00,0x12,0x00,0x17,0x00,0x0A,0x00,0x10,0x00,0x1D,0x00,0x00,0x00,0x00,0x00,0x16,0x00,0x13,0x00, \
                                               0x13,0x00,0x19,0x00,0x0E,0x00,0x0F,0x00,0x1E,0x00,0xFD,0xFF,0x07,0x00,0x14,0x00,0x06,0x00,0x1A,0x00, \
                                               0x18,0x00,0x08,0x00,0x18,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x0A,0x00,0x06,0x00,0x07,0x00,0x09,0x00, \
                                               0x0B,0x00,0x12,0x00,0x09,0x00,0x04,0x00,0x11,0x00,0x05,0x00,0x05,0x00,0x0C,0x00,0x0A,0x00,0x04,0x00, \
                                               0x09,0x00,0x1C,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x01,0x00,0x12,0x00,0x08,0x00,0xFB,0xFF,0x0B,0x00, \
                                               0x0D,0x00,0x00,0x00,0x0F,0x00,0xFE,0xFF
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt1Buf,128, RESET_RXIDX);
            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==2)
            {
                BYTE bCustomCmdD801Cnt2Buf[]= {0x07,0x00,0x0B,0x00,0x0D,0x00,0x15,0x00,0x0E,0x00,0x0D,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x02,0x00, \
                                               0x06,0x00,0x0C,0x00,0x00,0x00,0x08,0x00,0x06,0x00,0x06,0x00,0x1F,0x00,0x0B,0x00,0x0F,0x00,0x12,0x00, \
                                               0x0C,0x00,0x16,0x00,0x0C,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x06,0x00,0x0B,0x00,0x01,0x00, \
                                               0x00,0x00,0x0D,0x00,0x02,0x00,0x0D,0x00,0x1A,0x00,0x06,0x00,0x1C,0x00,0x0D,0x00,0x14,0x00,0x07,0x00, \
                                               0x13,0x00,0x0F,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x14,0x00,0x1D,0x00,0x0F,0x00,0xFF,0xFF,0x03,0x00, \
                                               0x17,0x00,0x09,0x00,0x16,0x00,0x14,0x00,0x17,0x00,0x12,0x00,0x18,0x00,0x1A,0x00,0x15,0x00,0x14,0x00, \
                                               0x00,0x00,0x00,0x00,0x0C,0x00,0x1B,0x00
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt2Buf,128, RESET_RXIDX);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==3)
            {
                BYTE bCustomCmdD801Cnt3Buf[]= {0x0B,0x00,0x04,0x00,0xFB,0xFF,0x06,0x00,0x13,0x00,0x18,0x00,0x1D,0x00,0x10,0x00,0x12,0x00,0x18,0x00, \
                                               0x13,0x00,0x0A,0x00,0x18,0x00,0x15,0x00,0x00,0x00,0x00,0x00,0x11,0x00,0x04,0x00,0x12,0x00,0x01,0x00, \
                                               0xF9,0xFF,0x0F,0x00,0x04,0x00,0x1E,0x00,0x14,0x00,0x13,0x00,0x0D,0x00,0x19,0x00,0x0D,0x00,0x07,0x00, \
                                               0x06,0x00,0x0A,0x00,0x00,0x00,0x00,0x00,0x12,0x00,0x15,0x00,0x0A,0x00,0x0E,0x00,0x05,0x00,0x17,0x00, \
                                               0x20,0x00,0x55,0x00,0x30,0x00,0x13,0x00,0x19,0x00,0x13,0x00,0x04,0x00,0x1F,0x00,0x15,0x00,0x08,0x00, \
                                               0x00,0x00,0x00,0x00,0x02,0x00,0x09,0x00,0x00,0x00,0xFD,0xFF,0x0A,0x00,0x28,0x00,0x68,0x00,0xE2,0x01, \
                                               0x84,0x01,0x46,0x00,0x18,0x00,0x16,0x00
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt3Buf,128, RESET_RXIDX);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==4)
            {
                BYTE bCustomCmdD801Cnt4Buf[]= {0x01,0x00,0x09,0x00,0xFA,0xFF,0x0C,0x00,0x00,0x00,0x00,0x00,0x0B,0x00,0x01,0x00,0xED,0xFF,0xFD,0xFF, \
                                               0x00,0x00,0x14,0x00,0x9C,0x00,0x25,0x03,0xF7,0x02,0x84,0x01,0x26,0x00,0x0B,0x00,0x08,0x00,0x01,0x00, \
                                               0xFF,0xFF,0xFD,0xFF,0x00,0x00,0x00,0x00,0x05,0x00,0x06,0x00,0x01,0x00,0x03,0x00,0x08,0x00,0x02,0x00, \
                                               0x2B,0x00,0x56,0x01,0x2A,0x02,0xD0,0x00,0x17,0x00,0x14,0x00,0xFF,0xFF,0x08,0x00,0x06,0x00,0x06,0x00, \
                                               0x00,0x00,0x00,0x00,0x24,0x00,0x1D,0x00,0x22,0x00,0x24,0x00,0x22,0x00,0x0C,0x00,0x3D,0xFF,0x6A,0xFD, \
                                               0x6B,0xFE,0xF2,0xFF,0x08,0x00,0x0A,0x00,0x16,0x00,0x15,0x00,0x0F,0x00,0x1A,0x00,0x00,0x00,0x00,0x00, \
                                               0x27,0x00,0x26,0x00,0x25,0x00,0x1F,0x00
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt4Buf,128, RESET_RXIDX);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==5)
            {
                BYTE bCustomCmdD801Cnt5Buf[]= {0x23,0x00,0x16,0x00,0x78,0xFF,0xB6,0xFD,0x2D,0xFE,0xD2,0xFF,0x10,0x00,0x15,0x00,0x1D,0x00,0x14,0x00, \
                                               0x19,0x00,0x1B,0x00,0x00,0x00,0x00,0x00,0x21,0x00,0x1D,0x00,0x28,0x00,0x1D,0x00,0x1A,0x00,0x18,0x00, \
                                               0xFC,0xFF,0xC8,0xFF,0xD7,0xFF,0x08,0x00,0x0A,0x00,0x0E,0x00,0x10,0x00,0x06,0x00,0x21,0x00,0x0D,0x00, \
                                               0x00,0x00,0x00,0x00,0x15,0x00,0x1D,0x00,0x14,0x00,0x10,0x00,0x1F,0x00,0x12,0x00,0x0D,0x00,0x17,0x00, \
                                               0x26,0x00,0x28,0x00,0x0A,0x00,0x06,0x00,0x18,0x00,0x02,0x00,0x12,0x00,0x09,0x00,0x00,0x00,0x00,0x00, \
                                               0x05,0x00,0x0B,0x00,0x06,0x00,0x15,0x00,0x10,0x00,0x15,0x00,0x13,0x00,0x10,0x00,0x11,0x00,0x16,0x00, \
                                               0x0D,0x00,0x0C,0x00,0x13,0x00,0x12,0x00
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt5Buf,128, RESET_RXIDX);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==6)
            {
                BYTE bCustomCmdD801Cnt6Buf[]= {0x02,0x00,0x0B,0x00,0x00,0x00,0x00,0x00,0x09,0x00,0xFB,0xFF,0x0F,0x00,0x0E,0x00,0x0D,0x00,0x19,0x00, \
                                               0x10,0x00,0x0E,0x00,0x26,0x00,0x16,0x00,0x0C,0x00,0x0F,0x00,0x0C,0x00,0x0D,0x00,0x09,0x00,0x0C,0x00, \
                                               0x00,0x00,0x00,0x00,0x01,0x00,0x0D,0x00,0x07,0x00,0x11,0x00,0x0A,0x00,0x14,0x00,0x0D,0x00,0x01,0x00, \
                                               0x11,0x00,0x12,0x00,0x07,0x00,0x11,0x00,0x09,0x00,0x0D,0x00,0x0B,0x00,0x0D,0x00,0x00,0x00,0x00,0x00, \
                                               0x03,0x00,0x1F,0x00,0x13,0x00,0x20,0x00,0x18,0x00,0x17,0x00,0x1A,0x00,0x13,0x00,0x1D,0x00,0x17,0x00, \
                                               0x0A,0x00,0x1B,0x00,0x15,0x00,0x11,0x00,0x1C,0x00,0x0B,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x18,0x00, \
                                               0x17,0x00,0x15,0x00,0x0E,0x00,0x1A,0x00
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt6Buf,128, RESET_RXIDX);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==7)
            {
                BYTE bCustomCmdD801Cnt7Buf[]= {0x0F,0x00,0x0B,0x00,0x28,0x00,0x1C,0x00,0x04,0x00,0x08,0x00,0x09,0x00,0x07,0x00,0x0E,0x00,0x11,0x00, \
                                               0x00,0x00,0x00,0x00,0x06,0x00,0x05,0x00,0x1B,0x00,0x19,0x00,0x22,0x00,0x20,0x00,0x18,0x00,0x0B,0x00, \
                                               0x20,0x00,0x28,0x00,0xFE,0xFF,0x09,0x00,0x0F,0x00,0x06,0x00,0x12,0x00,0x14,0x00,0x00,0x00,0x00,0x00, \
                                               0x06,0x00,0x0C,0x00,0x14,0x00,0x15,0x00,0x19,0x00,0x19,0x00,0x17,0x00,0x13,0x00,0x16,0x00,0x1A,0x00, \
                                               0x08,0x00,0x12,0x00,0xFE,0xFF,0x1C,0x00,0x08,0x00,0x11,0x00,0x00,0x00,0x00,0x00,0x0E,0x00,0x02,0x00, \
                                               0x0F,0x00,0x16,0x00,0x1F,0x00,0x24,0x00,0x1C,0x00,0x10,0x00,0x13,0x00,0x19,0x00,0x00,0x00,0x14,0x00, \
                                               0xFF,0xFF,0x09,0x00,0x0E,0x00,0x08,0x00
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt7Buf,128, RESET_RXIDX);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==8)
            {
                BYTE bCustomCmdD801Cnt8Buf[]= {0x00,0x00,0x00,0x00,0x04,0x00,0x0F,0x00,0x08,0x00,0x1C,0x00,0x15,0x00,0x1B,0x00,0x0F,0x00,0xFC,0xFF, \
                                               0x1D,0x00,0x25,0x00,0x19,0x00,0x0C,0x00,0x20,0x00,0x15,0x00,0x11,0x00,0x12,0x00,0x00,0x00,0x00,0x00, \
                                               0x02,0x00,0x01,0x00,0x0B,0x00,0x02,0x00,0x11,0x00,0x12,0x00,0x0C,0x00,0xFB,0xFF,0x18,0x00,0x1A,0x00, \
                                               0x15,0x00,0x11,0x00,0x10,0x00,0x0A,0x00,0x0C,0x00,0x16,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,0xFF,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                                              };
                CustomerResponseArray(bCustomCmdD801Cnt8Buf,128, RESET_RXIDX);

            }
            else // if(CustomerVar.bCustomCmd6801nnCnt==9)
            {

                BYTE bCustomCmdD801Cnt0Buf[]= {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFD,0xFF,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, \
                                               0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
                                              };
                //check if bCustomCmd6801nnCnt need to reset as 0
                CustomerResponseArray(bCustomCmdD801Cnt0Buf,128, RESET_RXIDX);

            }
#else
            if((CustomerVar.bCustomCmd6801nnCnt%9)==1)
            {
                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt1Buf[0]);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==2)
            {

                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt2Buf[0]);
            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==3)
            {

                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt3Buf[0]);
            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==4)
            {

                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt4Buf[0]);
            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==5)
            {

                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt5Buf[0]);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==6)
            {
                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt6Buf[0]);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==7)
            {
                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt7Buf[0]);

            }
            else if((CustomerVar.bCustomCmd6801nnCnt%9)==8)
            {
                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt8Buf[0]);

            }
            else // if(CustomerVar.bCustomCmd6801nnCnt==9)
            {
                ZetVar.wI2cTxIdx= 0;
                ZetVar.wI2cTxLen = 128;
                ZetVar.wI2cRxIdx = 0;
                ZetVar.pI2CData = (BYTE *)(&bCustomCmdD801Cnt0Buf[0]);
            }

        }


#endif



        }
        else if(ZetVar.bI2CCmd == 0xE2) // E2 01, E2 01 0C, E2 01 00 (Wake-up  command)
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
            {
                BYTE bTmpBuf[]= {0x0C};
                CustomerResponseArray(bTmpBuf, 1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && (ZetVar.bI2CRxBuf[2]==0x0C||ZetVar.bI2CRxBuf[2]==0x00))
            {
                CustomerVar.bWakeUpFlag=1;
                ZetVar.wI2cRxIdx=0;

                if(CustomerVar.bCustomCmd5901WakeupCnt<250)
                {
                    CustomerVar.bCustomCmd5901WakeupCnt++;
                }

                if(CustomerVar.bCustomCmd5901WakeupCnt>0)
                {
                    ZetVar.bWorkingState=WORKING_STATE_CUSTOMER_NORMAL;
                }

                //ZetVar.bINTtriggerCnt=0; //11, 13

            }
        }
        else if(ZetVar.bI2CCmd == 0xE3) // E3 01, E3 01 05
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
            {
                BYTE bTmpBuf[]= {0x05};
                CustomerResponseArray(bTmpBuf, 1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && ZetVar.bI2CRxBuf[2]==0x05)
            {
                ZetVar.wI2cRxIdx=0;
                ZetVar.bI2cRxLen = 0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xE4) //E4 01, E4 01 19
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
            {
                BYTE bTmpByte[]= {0x19};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && ZetVar.bI2CRxBuf[2]==0x19)
            {
                ZetVar.wI2cRxIdx=0;
                ZetVar.bI2cRxLen = 0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xEC) //EC 01, EC 01 FF, EC 01 05
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01 && CustomerVar.bCustomCmd5901Cnt==1)
            {
                BYTE bTmpByte[]= {0x05};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && (ZetVar.bI2CRxBuf[2]==0xFF||ZetVar.bI2CRxBuf[2]==0x05))
            {
                ZetVar.wI2cRxIdx = 0;
                ZetVar.bI2cRxLen = 0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xED) //ED 01, ED 01 01, ED 01 0E
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01&&CustomerVar.bCustomCmd5901Cnt==1)
            {
                BYTE bTmpByte[]= {0x0E};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && (ZetVar.bI2CRxBuf[2]==0x01||ZetVar.bI2CRxBuf[2]==0x0E))
            {
                ZetVar.wI2cRxIdx = 0;
                ZetVar.bI2cRxLen = 0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xEE) //EE 01, EE 01 00,
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01&&CustomerVar.bCustomCmd5901Cnt==1)
            {
                BYTE bTmpByte[]= {0x00};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && ZetVar.bI2CRxBuf[2]==0x00)
            {
                ZetVar.wI2cRxIdx = 0;
                ZetVar.bI2cRxLen = 0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xEF) //EF 01, EF 01 00,
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
            {
                BYTE bTmpByte[]= {0x00};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x01 && ZetVar.bI2CRxBuf[2]==0x00)
            {
                ZetVar.wI2cRxIdx = 0;
                ZetVar.bI2cRxLen = 0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xF4) //F4 03, F4 03 78, F4 03 33
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
            {
                BYTE bTmpByte[]= {0x78};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x03 && (ZetVar.bI2CRxBuf[2]==0x78||ZetVar.bI2CRxBuf[2]==0x33))
            {
                ZetVar.wI2cRxIdx=0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xF6) //F6 03, F6 03 08, F6 03 0C
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x03)
            {
                BYTE bTmpByte[]= {0x0C};
                CustomerResponseArray(bTmpByte,1, UNCHANGE_IDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x03 && (ZetVar.bI2CRxBuf[2]==0x08||ZetVar.bI2CRxBuf[2]==0x0C))
            {
                ZetVar.wI2cRxIdx=0;
            }
        }
        else if(ZetVar.bI2CCmd == 0xF9) //conflict with ZetTouch command TPCMD_F9_REVISION_READ
        {
            if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0x03 && (ZetVar.bI2CRxBuf[2]==0x78||ZetVar.bI2CRxBuf[2]==0x33))
            {
                ZetVar.wI2cRxIdx=0;
                //force to normal mode
                // ZetVar.bWorkingState=WORKING_STATE_CUSTOMER_NORMAL;
            }
        }
        else if(ZetVar.bI2CCmd == 0xFF)  //Debug command FF FF, FF F1 01, FF F1 02, FF F1 03,
        {
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0xFF)
            {
                BYTE bTmpByte[8];
                BYTE bCnt;
                for(bCnt=0; bCnt<8; bCnt++)
                {
                    bTmpByte[bCnt]=CustomerVar.bDebugBuf[bCnt];
                }
                //bTmpByte[5]=0xFF;
                CustomerVar.bDebugBuf[5]=ZetVar.bWorkingState;
                CustomerResponseArray(bTmpByte,8, RESET_RXIDX);
            }
            else if(ZetVar.wI2cRxIdx==3 && ZetVar.bI2CRxBuf[1]==0xF1)
            {
                BYTE bTmpByte[8];
                BYTE bCnt;
                ZetVar.bWorkingState=ZetVar.bI2CRxBuf[2];

                //if(ZetVar.bI2CRxBuf[2]==WORKING_STATE_ZET_CMD_STATE)
                ///{
                ///	ZetVar.bWorkingState=WORKING_STATE_ZET_CMD_STATE;
                ///}
                ///else if(ZetVar.bI2CRxBuf[2]==WORKING_STATE_CUSTOMER_INITIAL)
                ///{
                ///	ZetVar.bWorkingState=WORKING_STATE_CUSTOMER_INITIAL;
                ///}
                ///else if(ZetVar.bI2CRxBuf[2]==WORKING_STATE_CUSTOMER_NORMAL)
                ///{
                ///	ZetVar.bWorkingState=WORKING_STATE_CUSTOMER_NORMAL;
                ///}

                CustomerVar.bDebugBuf[5]=ZetVar.bWorkingState;
                for(bCnt=0; bCnt<8; bCnt++)
                {
                    bTmpByte[bCnt]=CustomerVar.bDebugBuf[bCnt];
                }
                CustomerResponseArray(bTmpByte,8, RESET_RXIDX);
            }
        }
        else
        {
            //if no command pattern matched, clear Rx buffer
            //ZetVar.wI2cRxIdx = 0;
            //ZetVar.bI2cRxLen = 0;
            //   ZetVar.wI2cTxIdx = 0;
            //   ZetVar.wI2cTxLen = 0;
        }



    }

#endif



#endif


#ifdef FORCE_SENSOR_PROTOCOL
void I2CDispatchCustomerForceSensorCmd()
{

		if(ZetVar.bI2CCmd == 0x00)
    {
        if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
        {
            //for 00 01 83 02, no handle 
        }
				else if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x02)
				{
             BYTE bTmpByte[]= {0x07,0x00};
             CustomerResponseArray(bTmpByte,2, UNCHANGE_IDX);
				}
				else if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0xBF)
				{
					   BYTE bTmpByte[]= {0x00,0x04};
						 CustomerResponseArray(bTmpByte,2, UNCHANGE_IDX);

				}
				else if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0xBB)
				{
					   CustomerForceSensorVar.bCmdRemapEnableFlag=(CustomerForceSensorVar.bCmdRemapEnableFlag+1)%2;
				}				
				else if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0xBC)
				{
						 CustomerForceSensorVar.bCmdPatternCheckEnableFlag=(CustomerForceSensorVar.bCmdPatternCheckEnableFlag+1)%2;
				}				
				else if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0xC0)
				{
	           ZetVar.wI2cTxIdx= 0;
             ZetVar.wI2cTxLen = (12*8)*2;
						 ZetVar.pI2CData = (BYTE *)(&CustomerForceSensorVar.wCustomerForceSensorAdBase[CustomerForceSensorVar.bDoubleBufferSendIdx][0]);
						 I2C_INT_LOW();
				}
		}

}
#endif

/**
 * @brief  I2CDispatchCmd()
 *
 *  Dispatch Cmd
 *
 * @return NULL
 *
 */
void I2CDispatchCmd()
{
#ifdef FEATURE_I2C_CMD_FB_DEVICE_NAME
    BYTE	data i;
#endif

#ifdef FEATURE_CUSTOMER_PROTOCOL     
 			#if 1  
			if(ZetVar.bI2CCmd == 0xFF) //new reserve cmd(switching mode): FF FF FF FF, FF FF nn FF, 
			{
				if((ZetVar.wI2cRxIdx>=2||ZetVar.wI2cRxIdx<=4) && ZetVar.bI2CRxBuf[1]==0xFF)
				{
					if((ZetVar.wI2cRxIdx==4) && ZetVar.bI2CRxBuf[3]==0xFF)
					{	
	          BYTE bTmpByte[8];
				    BYTE bCnt;
	          if(ZetVar.bI2CRxBuf[2]!=0xFF)
	          {
							ZetVar.bWorkingState=ZetVar.bI2CRxBuf[2];
	          }
						CustomerVar.bDebugBuf[5]=ZetVar.bWorkingState;
						
						// CustomerVar.bDebugBuf[6]=ZetVar.wI2cRxIdx;
						// CustomerVar.bDebugBuf[0]=0xF1;
						for(bCnt=0; bCnt<8; bCnt++)
						{
							bTmpByte[bCnt]=CustomerVar.bDebugBuf[bCnt];
						}
						CustomerResponseArray(bTmpByte,8, UNCHANGE_IDX); 
						I2C_INT_LOW();
	          return;
					}
				}			 
			}
			#else 
			 if(ZetVar.bI2CCmd == 0xFF) //reserve cmd(switching mode): FF FF, FF F1 nn, 
			 {
					 if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0xFF)
					 {
							 BYTE bTmpByte[8];
							 BYTE bCnt;

							 CustomerVar.bDebugBuf[5]=ZetVar.bWorkingState; 		
							// CustomerVar.bDebugBuf[6]=ZetVar.wI2cRxIdx; 										 
							// CustomerVar.bDebugBuf[0]=0xF2; 
							 for(bCnt=0; bCnt<8; bCnt++)
							 {
									bTmpByte[bCnt]=CustomerVar.bDebugBuf[bCnt];
									
							 }									 
															 
							 CustomerResponseArray(bTmpByte,8, RESET_RXIDX);    
							 I2C_INT_LOW();
							 return;
					 }
					 else if((ZetVar.wI2cRxIdx ==2||ZetVar.wI2cRxIdx ==3) && ZetVar.bI2CRxBuf[1]==0xF1)
					 {
							 BYTE bTmpByte[8];
							 BYTE bCnt;		
							 if(ZetVar.wI2cRxIdx==3)
								 {                         
							
									 ZetVar.bWorkingState=ZetVar.bI2CRxBuf[2];
									 CustomerVar.bDebugBuf[5]=ZetVar.bWorkingState;
									// CustomerVar.bDebugBuf[6]=ZetVar.wI2cRxIdx;
									// CustomerVar.bDebugBuf[0]=0xF1;
									 for(bCnt=0; bCnt<8; bCnt++)
									 {
											 bTmpByte[bCnt]=CustomerVar.bDebugBuf[bCnt];
									 }
									 CustomerResponseArray(bTmpByte,8, RESET_RXIDX); 
									 I2C_INT_LOW();
								 }
						 return;  // Match FF F1, seen as hit  
					 }					 
			 }
			#endif

    //other cmd
    if((ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_INITIAL)	||
       (ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_NORMAL))
    {        				             
			I2CDispatchCustomerCmd();		         
    }
		#ifdef FORCE_SENSOR_PROTOCOL
		else if(ZetVar.bWorkingState==WORKING_STATE_CUSTOMER_FORCETOUCH) //switch to Zetouch mode
		{
			I2CDispatchCustomerForceSensorCmd();
		}
		#endif
    else if(ZetVar.bWorkingState==WORKING_STATE_ZET_CMD_STATE) //switch to Zetouch mode
#endif
    {
        if(ZetVar.bI2CCmd == TPCMD_A0_INIT_SCAN_AD)
        {
            ZetVar.bI2cRxLen = TP_CMD_A0_CMD_LEN;
            ZetVar.wI2cTxLen = 2*(ZetVar.bSenseMax + ZetVar.bDriveMax);

            /// Test Mode Enabled
            ZetVar.wTestMode = (TP_TEST_FPC_SHORT_EN);
            ZetVar.wSysMode |= (SYS_MODE_TP_TEST_EN);
            ZetVar.wSysMode2 |= SYS_MODE2_ZET7100_FORCE_EVENODD_SCAN;
            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&pGenBuf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
        else if(ZetVar.bI2CCmd == TPCMD_A1_INIT_SCAN_DV)
        {
            ZetVar.bI2cRxLen = TP_CMD_A1_CMD_LEN;
            ZetVar.wI2cTxLen = ZetVar.bSenseMax + ZetVar.bDriveMax;

            /// Test Mode Enabled
            ZetVar.wTestMode = (TP_TEST_FPC_OPEN_EN);
            ZetVar.wSysMode |= (SYS_MODE_TP_TEST_EN);
            ZetVar.wSysMode2 |= SYS_MODE2_ZET7100_FORCE_EVENODD_SCAN;
            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();
            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&pGenBuf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
#ifdef FEATURE_I2C_CMD_A2_RELEASE_TEST
        else if(ZetVar.bI2CCmd == TPCMD_A2_RELEASE_TEST)
        {
            ZetVar.bI2cRxLen = TP_CMD_A2_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_A2_TX_DATA_LEN;

            /// Test Mode Disabled
            ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&pGenBuf[0]);
            ZetVar.wI2cRxIdx = 0;
            /// Cancel the previous interrupt, if any
            #ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
            I2C_INT_HIGH();
        }
#endif
        else if(ZetVar.bI2CCmd == TPCMD_A3_INIT_SCAN_DV)
        {
            ZetVar.bI2cRxLen = TP_CMD_A3_CMD_LEN;
            ZetVar.wI2cTxLen = (ZetVar.bSenseMaxAlg * ZetVar.bDriveMaxAlg)*2;

            /// Test Mode Enabled
            if(ZetVar.wTestMode == TP_TEST_ITO_SENSOR_SWITCH)
            {
                ZetVar.wTestMode = (TP_TEST_ITO_SENSOR | TP_TEST_ITO_SENSOR_SWITCH);
            }
            else
            {
                ZetVar.wTestMode = (TP_TEST_ITO_SENSOR);
            }

            ZetVar.bScanMethod = METHOD_SCAN_FINISH;
            IntAdcDisable();
            ZetVar.wSysMode |= (SYS_MODE_TP_TEST_EN);
            //ZetVar.wSysMode2 &= ~SYS_MODE2_ROUND_RUNNING;
            //CLR_BIT(REG32_TCON, TMR_EN);

            SYSWatchDogDisable();
            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&AlgorithmDataPtr->sDevAlloc[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif

        }
        else if(ZetVar.bI2CCmd == TPCMD_A4_MUTUAL_DEV)
        {
            I2C_INT_HIGH();
            ZetVar.bI2cRxLen = TP_CMD_A4_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_A4_TX_DATA_LEN;
            ZetVar.bTranType = TRAN_TYPE_MUTUAL_SCAN_DEV;

            /// Test Mode Disabled
            ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;
            /// Cancel the previous interrupt, if any
            /// Link the buffer
            ZetVar.pI2CData =(BYTE *) (&AlgorithmDataPtr->sDevAlloc[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
        else if(ZetVar.bI2CCmd == TPCMD_A5_MUTUTAL_PIN_SWITCH)
        {
            ZetVar.bI2cRxLen = TP_CMD_A5_CMD_LEN;
            ZetVar.wI2cTxLen = (ZetVar.bSenseMaxAlg * ZetVar.bDriveMaxAlg)*2;

            /// Test Mode Enabled
            ZetVar.wTestMode = (TP_TEST_ITO_SENSOR_SWITCH);
            ZetVar.wSysMode |= (SYS_MODE_TP_TEST_EN);

            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData =(BYTE *) (&AlgorithmDataPtr->sDevAlloc[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
        else if(ZetVar.bI2CCmd == TPCMD_AA_INIT_ENHANCE_SCAN_DV)
        {
            /// The last command bytes
            if(ZetVar.wI2cRxIdx  == 1)
            {
                ZetVar.bI2cRxLen = TP_CMD_AA_CMD_LEN;
            }
            else if(ZetVar.wI2cRxIdx == TP_CMD_AA_CMD_LEN)
            {
                ZetVar.wI2cRxIdx = 0;
            }
        }
        else if(ZetVar.bI2CCmd == TPCMD_AB_KEY_SCAN_AD)
        {
            ZetVar.bI2cRxLen = TP_CMD_AB_CMD_LEN;
            ZetVar.wI2cTxLen = 2*KEY_MAX_NUM; ///< For SW Easy Array Re-use;

            /// Test Mode Enabled
            ZetVar.wTestMode = (TP_TEST_KEY_AD_EN);
            ZetVar.wSysMode |= (SYS_MODE_TP_TEST_EN);

            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&pGenBuf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
        else if(ZetVar.bI2CCmd == TPCMD_AC_RAW_DEV)
        {
            ZetVar.bDynamicHopDataOutSel = (ZetVar.bDynamicHopDataOutSel+1)%3;
            ///------------------------------------------///
            ///    To display mutual raw dev at mutual dev mode
            ///------------------------------------------///
            if(ZetVar.wSysMode2 & SYS_MODE2_RAW_MUTUAL_DEV)
            {
                ZetVar.wSysMode2 &= ~SYS_MODE2_RAW_MUTUAL_DEV;
            }
            else
            {
                ZetVar.wSysMode2 |= SYS_MODE2_RAW_MUTUAL_DEV;
            }
            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
        else if(ZetVar.bI2CCmd == TPCMD_B0_RESET)
        {
            ZetVar.bI2cRxLen = TP_CMD_B0_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_B0_TX_DATA_LEN;


            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif

            /// Relese the interrupt
            CLR_BIT(REG32_I2CON, STROBE_PEND);
            CLR_BIT(REG32_I2CON, I2C_STOP);
            CLR_BIT(REG32_I2C_RX_IF, I2CRX_IF);

            /// Do the softreset
            SYSSoftResetInt();
        }
        else if(ZetVar.bI2CCmd == TPCMD_B1_DEEP_SLEEP)
        {
            ZetVar.bI2cRxLen = TP_CMD_B1_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_B1_TX_DATA_LEN;
                
						/// Test Mode Enabled
            ZetVar.wSysMode |= (SYS_MODE_DEEP_SLEEP);
            /// Test Mode Disabled
            ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;
        


            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
        else if(ZetVar.bI2CCmd == TPCMD_B2_PANEL_INFO)
        {
            ZetVar.bI2cRxLen = TP_CMD_B2_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_B2_TX_DATA_LEN;

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
            I2C_INT_LOW();
        }
        else if(ZetVar.bI2CCmd == TPCMD_B3_IDLE)
        {
            ZetVar.bI2cRxLen = TP_CMD_B3_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_B3_TX_DATA_LEN;
#ifdef FEATURE_RAW_DEV_IMPORT
				ZetVar.bImportFlowCtrl |=  (IMPORT_CTRL_WAIT_CMD | IMPORT_CTRL_START);
#else
            /// Test Mode Enabled
            ZetVar.wSysMode |= (SYS_MODE_IDLE);
            /// Test Mode Disabled
            ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;
#endif	

            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
					
        }
        else if(ZetVar.bI2CCmd == TPCMD_B4_WAKE)
        {
            ZetVar.bI2cRxLen = TP_CMD_B4_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_B4_TX_DATA_LEN;

            /// Wake up the system
            ZetVar.wSysMode &= ~(SYS_MODE_IDLE | SYS_MODE_DEEP_SLEEP);

            /// Test Mode Disabled
            ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;
            /// Gesture Function Disable
            if(ZetVar.wSysMode2 & SYS_MODE2_DEEP_SLEEP_GESTURE)
            {
#ifdef FEATURE_GESTURE_WAKEUP
                ZetVar.bGestureStatus = 0;
                ZetVar.bGestureCount = 0;
#endif
                ZetVar.wSysMode2 &= ~(SYS_MODE2_DEEP_SLEEP_GESTURE);
                ZetVar.wGreenModeCounter = 0;
                ZetVar.wSysMode2 &= ~SYS_MODE2_GREEN_MODE;
                ZetVar.bTimerStatus = (TIMER_TO_NORMAL  | TIMER_RELOAD_FLAG);
            }
            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
         else if(ZetVar.bI2CCmd == TPCMD_B5_CHARGER_MODE_ENABLE)
        {
            SYSChargerModeEnable();

            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();
#ifdef 	REPORT_GESTURE_POINTS_LOG_METHOD
            if(ZetVar.bTranType !=TRAN_TYPE_GESTURE_POINTS_LOG)
#endif
            {
                ZetVar.bI2cRxLen = TP_CMD_B5_CMD_LEN;
                ZetVar.wI2cTxLen = TP_CMD_B5_TX_DATA_LEN;
                /// Link the buffer
                ZetVar.pI2CData =(BYTE *) (&ZetVar.bB2Buf[0]);
                ZetVar.wI2cRxIdx = 0;
								#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
								ZetVar.wI2cTxIdx = 0;
								#endif
            }

        }
        else if(ZetVar.bI2CCmd == TPCMD_B5_CHARGER_MODE_DISABLE)
        {
            SYSChargerModeDisable();
            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();
#ifdef 	REPORT_GESTURE_POINTS_LOG_METHOD
            if(ZetVar.bTranType !=TRAN_TYPE_GESTURE_POINTS_LOG)
#endif
            {
                ZetVar.bI2cRxLen = TP_CMD_B5_CMD_LEN;
                ZetVar.wI2cTxLen = TP_CMD_B5_TX_DATA_LEN;
                /// Link the buffer
                ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
                ZetVar.wI2cRxIdx = 0;
								#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
								ZetVar.wI2cTxIdx = 0;
								#endif
            }
        }
#ifdef FEATURE_GESTURE_WAKEUP
        else if(ZetVar.bI2CCmd == TPCMD_B7_DEEP_SLEEP_GESTURE)
        {
            ZetVar.bI2cRxLen = TP_CMD_B7_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_B7_TX_DATA_LEN;

            /// Test Mode Enabled
            ZetVar.wSysMode2 |= (SYS_MODE2_DEEP_SLEEP_GESTURE);
            /// Test Mode Disabled
            ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;

            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();

            /// Set Gesture Reload Timer
            ZetVar.bTimerStatus = (TIMER_TO_GESTURE  | TIMER_RELOAD_FLAG);
            /// Link the buffer
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
#endif ///< for FEATURE_GESTURE_WAKEUP
#ifdef FEATURE_CHECK_SUM
        else if(ZetVar.bI2CCmd == TPCMD_B8_CHECKSUM_READ)
        {
            /// Cancel the previous interrupt, if any
            I2C_INT_HIGH();
            ZetVar.bI2cRxLen = TP_CMD_B8_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_B8_TX_DATA_LEN;
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
            CLR_BIT(REG32_I2CON, STROBE_PEND);
            CLR_BIT(REG32_I2CON, I2C_STOP);
            SYSWatchDogDisable();
            ALCheckSumProcess();
            SYSWatchDogEnable();
            DFCheckSumData();

        }
#endif ///< for FEATURE_CHECK_SUM
        else if (ZetVar.bI2CCmd == TPCMD_C0_ADC_CTRL0_SET)
        {
            /// The last command bytes
            if(ZetVar.wI2cRxIdx  == 1)
            {
                ZetVar.bI2cRxLen = TP_CMD_C0_CMD_LEN;
            }
            else if(ZetVar.wI2cRxIdx == TP_CMD_C0_CMD_LEN)
            {
                ZetVar.wI2cRxIdx = 0;
            }
        }
        else if (ZetVar.bI2CCmd == TPCMD_C1_VEN_CMD_SET)
        {
            /// The last command bytes
            if(ZetVar.wI2cRxIdx  == 1)
            {
                ZetVar.bI2cRxLen = TP_CMD_C1_CMD_LEN;
            }
            else if(ZetVar.wI2cRxIdx == TP_CMD_C1_CMD_LEN)
            {
                I2CDispatchVenCmd();
            }
        }
#ifdef 	REPORT_GESTURE_POINTS_LOG_METHOD
        else if (ZetVar.bI2CCmd == 0xD0)
        {
            /// The last command bytes
            if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x01)
            {
                ZetVar.bTranType =TRAN_TYPE_GESTURE_POINTS_LOG;
                bGesturePointBuffer[0]=0xEE;
                bGesturePointBuffer[1]=0x00;

#if 1 //Reduce scan rate to TIMER_PERIOD_GESTURE
                /// Gesture sleeping Mode Enabled
                ZetVar.wSysMode2 |= (SYS_MODE2_DEEP_SLEEP_GESTURE);
                /// Test Mode Disabled
                ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;

                /// Set Gesture Reload Timer
                ZetVar.bTimerStatus = (TIMER_TO_GESTURE  | TIMER_RELOAD_FLAG);
#endif



                //bDoubleClickState=0;
                //bGesturePointState=GESTURE_POINT_NONE_STATE;

                //ZetVar.wI2cTxLen = 1;
                //ZetVar.wI2cTxIdx = 0;
                //bGesturePointBuffer[0]=0x01;
                //ZetVar.pI2CData = (BYTE xdata *)(&bGesturePointBuffer[0]);
                //ZetVar.wI2cRxIdx = 0;
                //I2C_INT_LOW();
            }
            else if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x00)
            {
                WORD j;
                bGesturePointBuffer[0]=0xEE;
                for(j=1; j<600; j++) bGesturePointBuffer[j]=0x00;

                ZetVar.bTranType =TRAN_TYPE_DYNAMIC;

#if 1 // back to normal scan
                /// Gesture sleeping Mode Disabled
                ZetVar.wSysMode2 &=~(SYS_MODE2_DEEP_SLEEP_GESTURE);
                /// Test Mode Enabled
                ZetVar.wSysMode |= (SYS_MODE_TP_TEST_EN);

                /// Set Normal Reload Timer
                ZetVar.bTimerStatus = (TIMER_TO_NORMAL  | TIMER_RELOAD_FLAG);
#endif
            }
            else if(ZetVar.wI2cRxIdx==2 && ZetVar.bI2CRxBuf[1]==0x40)
            {
#if 1 //Reduce scan rate to TIMER_PERIOD_GESTURE
                /// Gesture sleeping Mode Enabled
                ZetVar.wSysMode2 |= (SYS_MODE2_DEEP_SLEEP_GESTURE);
                /// Test Mode Disabled
                ZetVar.wSysMode &= ~SYS_MODE_TP_TEST_EN;

                /// Set Gesture Reload Timer
                ZetVar.bTimerStatus = (TIMER_TO_GESTURE  | TIMER_RELOAD_FLAG);
#endif
            }
        }
        else if (ZetVar.bI2CCmd == 0xD3)
        {

            /// The last command bytes
            if(bCmdD3Cnt ==0)
            {
                ZetVar.wI2cTxLen = 8; //600;
            }
            else if(bCmdD3Cnt ==1)
            {
                ZetVar.wI2cTxLen = (WORD)(bGesturePointBuffer[1])*4+8; //600;
            }

            //LM, Test
            bGesturePointBuffer[2]=HIBYTE(ZetVar.wI2cTxLen);
						bGesturePointBuffer[3]=LOBYTE(ZetVar.wI2cTxLen);
            bGesturePointBuffer[4]=bDoubleClickState;
            bGesturePointBuffer[5]=ZetVar.bIntLowTimeout;
            bGesturePointBuffer[6]=bGesturePointState;
            bGesturePointBuffer[7]=bCmdD3Cnt;


            ZetVar.wI2cTxIdx=0;
            ZetVar.pI2CData = (BYTE xdata *)(&bGesturePointBuffer[0]);
            ZetVar.wI2cRxIdx = 0;
            //  I2C_INT_HIGH();
        }
#endif
#ifdef FEATURE_SRAM_READ_WRITE
        else if (ZetVar.bI2CCmd == TPCMD_F3_SRAM32_READ)
        {
            ZetVar.bI2cRxLen = TP_CMD_F3_CMD_LEN;

            /// The last command bytes
            if(ZetVar.wI2cRxIdx == (TP_CMD_F3_CMD_LEN))
            {
                MEMCPY((void*)&ZetVar.dwSramAddr, (void*)&ZetVar.bI2CRxBuf[1], 4);
               // ZetVar.wI2cTxLen = *(WORD *)&ZetVar.bI2CRxBuf[TP_CMD_F3_CMD_LEN-2];
                ZetVar.wI2cTxLen = *(WORD *)(&ZetVar.bI2CRxBuf[TP_CMD_F3_CMD_LEN-2]);
                ZetVar.pI2CData = (BYTE xdata *)(uintptr_t)(ZetVar.dwSramAddr);
                ZetVar.wI2cRxIdx = 0;
								#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
								ZetVar.wI2cTxIdx = 0;
								#endif
                I2C_INT_LOW();
            }
        }
        else if (ZetVar.bI2CCmd == TPCMD_F4_SRAM32_WRITE)
        {
            /// The last command bytes
            if(ZetVar.wI2cRxIdx  == 1)
            {
                ZetVar.bI2cRxLen = TP_CMD_F4_CMD_LEN;
            }
            if(ZetVar.wI2cRxIdx == TP_CMD_F4_CMD_LEN)
            {
                MEMCPY((void*)&ZetVar.dwSramAddr, (void*)&ZetVar.bI2CRxBuf[1], 4);
                /// Write Data to sram
                WRITE_XDATA((uintptr_t)ZetVar.dwSramAddr, ZetVar.bI2CRxBuf[(TP_CMD_F4_CMD_LEN-1)]);
                ZetVar.dwSramAddr = ZetVar.dwSramAddr + 1;
                ZetVar.wI2cRxIdx = 0;
            }
        }
#endif
#ifdef FEATURE_I2C_CMD_F7_ENABLE
        else if (ZetVar.bI2CCmd == TPCMD_F7_CALIBRATE)
        {
            ZetVar.bI2cRxLen = TP_CMD_F7_CMD_LEN;
            ZetVar.wI2cTxLen = TP_CMD_F7_TX_DATA_LEN;
            ZetVar.wSysMode &=~(SYS_MODE_CALIBRATED);
            ZetVar.bCalibrationCtrl |= BASE_RE_CALIBRATION;
            ZetVar.wI2cRxIdx = 0;
        }
#endif
#ifdef FEATURE_I2C_CMD_F8_ENABLE
        else if (ZetVar.bI2CCmd == TPCMD_F8_WDT)
        {
            /// The last command bytes
            if(ZetVar.wI2cRxIdx  == 1)
            {
                ZetVar.bI2cRxLen = TP_CMD_F8_CMD_LEN;
            }
            else if(ZetVar.wI2cRxIdx == TP_CMD_F8_CMD_LEN)
            {
                if(ZetVar.bI2CRxBuf[1] == TRUE)
                {
                    /// Enable WDT
                    SYSWatchDogEnable();
                }
                else
                {
                    /// Disable  WDT
                    SYSWatchDogDisable();
                }
                ZetVar.wI2cRxIdx = 0;
            }
        }
#endif
        else if (ZetVar.bI2CCmd == TPCMD_F9_REVISION_READ)
        {
            ZetVar.bI2cRxLen = TP_CMD_F9_CMD_LEN;

            /// The last command bytes
            //if(ZetVar.wI2cRxIdx == (TP_CMD_F9_CMD_LEN))
            {
                //WORD data wFlashVersion = BE2LE(ZetDF.cDevData.scDevData.wDataFlashVersion);
                ZetVar.bF9Buf[0] = LOBYTE(FW_VERSION);
                ZetVar.bF9Buf[1] = HIBYTE(FW_VERSION);
                ZetVar.bF9Buf[2] = LOBYTE(ZetDF.cDevData.scDevData.wDataFlashVersion);
                ZetVar.bF9Buf[3] = HIBYTE(ZetDF.cDevData.scDevData.wDataFlashVersion);

                ZetVar.wI2cTxLen = TP_CMD_F9_TX_DATA_LEN;
                ZetVar.pI2CData = (BYTE xdata *)(& ZetVar.bF9Buf[0]);
                ZetVar.wI2cRxIdx = 0;
								#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
								ZetVar.wI2cTxIdx = 0;
								#endif
                I2C_INT_LOW();
            }
        }
#ifdef FEATURE_I2C_CMD_FA_CALIB_BASETRACK_CTRL
        else if (ZetVar.bI2CCmd == TPCMD_FA_CALIB_BASETRACK_CTRL)
        {
            /// The last command bytes
            if(ZetVar.wI2cRxIdx  == 1)
            {
                ZetVar.bI2cRxLen = TP_CMD_FA_CMD_LEN;
            }
            else if(ZetVar.wI2cRxIdx == TP_CMD_FA_CMD_LEN)
            {
                if(ZetVar.bI2CRxBuf[1] == TRUE)
                {
                    ZetVar.bCalibrationCtrl |= BASE_TRACK_RECALIBRAION_TOTAL_CTRL;
                }
                else
                {
                    ZetVar.bCalibrationCtrl &= ~BASE_TRACK_RECALIBRAION_TOTAL_CTRL;
                }
                ZetVar.wI2cRxIdx = 0;
            }
        }
#endif
#ifdef FEATURE_I2C_CMD_FB_DEVICE_NAME
        else if (ZetVar.bI2CCmd == TPCMD_FB_DEVICE_NAME_READ)
        {
            ZetVar.bI2cRxLen = TP_CMD_FB_CMD_LEN;

            /// The last command bytes
            //if(ZetVar.wI2cRxIdx == (TP_CMD_F9_CMD_LEN))
            {
                for(i=0; i<FB_BUF_LEN; i++)
                {
                    ZetVar.bFBBuf[i] = ZetVar.CompileDeviceName[i];//(ZetDF.cDevData.scDevData.pDeviceName[i]);
                }

                ZetVar.wI2cTxLen = TP_CMD_FB_TX_DATA_LEN;
                ZetVar.pI2CData = (BYTE xdata *)(& ZetVar.bFBBuf[0]);
                ZetVar.wI2cRxIdx = 0;
								#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
								ZetVar.wI2cTxIdx = 0;
								#endif
                I2C_INT_LOW();
            }
        }
#endif
#ifdef FEATURE_CMD_SWITCH_DEBUG
        else if (ZetVar.bI2CCmd == TPCMD_FF_SWITCH_DEBUG_CTRL)
        {
            ZetVar.bDebugCtrl = (ZetVar.bDebugCtrl+1)%2;
            I2C_INT_HIGH();
            ZetVar.pI2CData = (BYTE *)(&ZetVar.bB2Buf[0]);
            ZetVar.wI2cRxIdx = 0;
						#ifdef FEATURE_ZETOUCHCMD_CLEAR_TXIDX
						ZetVar.wI2cTxIdx = 0;
						#endif
        }
#endif
        else if((ZetVar.bI2CCmd & 0xF0) == TPCMD_80_SRAM_ACCESS)
        {
            if(ZetVar.wI2cRxIdx  == 1)
            {
                ZetVar.dwSramAddr = BASE_SRAM_BA | ((ZetVar.bI2CCmd & 0x0F)<<8);
            }
            else if(ZetVar.wI2cRxIdx == 2)
            {
                ZetVar.dwSramAddr |= ZetVar.bI2cData;
                ZetVar.pI2CData = (BYTE xdata *)(uintptr_t)(ZetVar.dwSramAddr);
                ZetVar.wI2cTxIdx = 0;
                ZetVar.bI2cStatus |= I2C_STA_SRAM_RW_MODE; ///< 1: enable SRAM Read Mode
                //ZetVar.wI2cRxIdx = 0;
                //I2C_INT_LOW();
            }
            else
            {
                WRITE_XDATA((uintptr_t)ZetVar.dwSramAddr, ZetVar.bI2cData);
                ZetVar.dwSramAddr++;
            }
            I2C_INT_HIGH();
        }
    }
}

void I2C_INT_LOW(void)
{
    CLR_BIT(BASE_GPIO_BA + INTPortReg,INTPinBit);
    //CLR_BIT(0x0018C040,INT_PIN);
    //CLR_BIT(INT_PORT, INT_PIN);

}
void I2C_INT_HIGH(void)
{
    SET_BIT(BASE_GPIO_BA + INTPortReg,INTPinBit);
    //SET_BIT(0x0018C040,INT_PIN);
    //SET_BIT(INT_PORT, INT_PIN);
}

#ifdef FEATURE_MCU_LIB_ENABLE
BOOL I2C_INT(void)
{
  if(READ_REG(BASE_GPIO_BA + INTPortReg) & INTPinBit)
  {
      return TRUE;
  }
  else
  {
      return FALSE;
  }
}
#endif

#ifdef SPI_FLASH_WR_ENABLE 
void SPIEnable(void)
{	
	SET_BIT(SPI_STATUS,SPI_ENABLE); /// SPI enable	
	WRITE_REG(SPI_SHIFT,0x00); /// set bit[1:0]=00  ,data format 1 byte
}


void SetFlashSIData(BYTE bData)
{	
	WRITE_REG(SPI_DATA, bData); ///  FLASH command, Data, or Address	
	SET_BIT(SPI_STATUS,SPI_SHIFT_START);	 /// spi shift start 	
	while( (READ_REG(SPI_STATUS)	) != 0x81); /// wait for ready
	WRITE_REG(SPI_IF,0x00); 	///clear interrupt flag
}


void SetFlashAddress(BYTE bAddrH,BYTE bAddrM,BYTE bAddrL)
{   	 
	 SetFlashSIData(bAddrH);/// Second Data prepare , address 23~16 bit 
	 SetFlashSIData(bAddrM); /// 3rd		Data prepare, address 15~8 bit 	
	 SetFlashSIData(bAddrL); /// 4th		Data prepare, address 7~0 bit
}

 
void SPI_Test(void)
{
	BYTE xdata FlashID;
	////////////  SPI configuration	
	SPIEnable();  /// SPI enable
	CustomerVar.bDebugBuf[10]=0xDD;

	///////////  SPI communication start	
	CLR_BIT(SPI_STATUS,SPI_CSB); /// csb go low, enable slave 
	
	SetFlashSIData(FLASH_RDID); /// command data, FLASH ID read command
	SetFlashSIData(0xaa);	  /// Second Data prepare , dummy data
	FlashID=READ_REG(SPI_DATA);
	CustomerVar.bDebugBuf[11]=FlashID;	
	SetFlashSIData(0x55);   /// 3rd    Data prepare, dummy data
	FlashID=READ_REG(SPI_DATA);
	CustomerVar.bDebugBuf[12]=FlashID;
	SetFlashSIData(0x00); 	/// 4th    Data prepare, Dummy data
	FlashID=READ_REG(SPI_DATA);
	CustomerVar.bDebugBuf[13]=FlashID;
	
	SET_BIT(SPI_STATUS,SPI_CSB);  /// CSB go High disable slave
}



/**
 * @brief  SPIFlashRead()
 *
 *  Read flash data and store into the pool buffer which pFlashBuffer indicate
 *
 * @return NULL
 *
 */


void SPIFlashRead(BYTE AddrH,BYTE AddrM,BYTE AddrL, WORD wSize, BYTE *pFlashBuffer)
{
	WORD i;

	////////////  SPI configuration
	
	SPIEnable();   /// SPI enable

	///////////  SPI communication start
	CLR_BIT(SPI_STATUS,SPI_CSB);	/// csb go low, enable slave 
	
	SetFlashSIData(FLASH_RD);	/// command data, FLASH read data command	
	SetFlashAddress(AddrH, AddrM,AddrL);
	for(i=0;i< wSize;i++)
	{
     SetFlashSIData(0xaa); //set dummy data
	   *pFlashBuffer=READ_REG(SPI_DATA);
		 pFlashBuffer++;
	}		

	SET_BIT(SPI_STATUS,SPI_CSB);	/// CSB go High disable slave

}
/**
 * @brief  SPIFlashSE()
 *
 *  Erase one sector flash data in fixed address 0x000D00, Never to change address!!!
 *  It need about 200ms to finish erase, it will not allow any write in this duration!!! 
 * 
 *  @return NULL
 */

//Section Erase, Fixed Erase Address 0x000D00 in flash
void SPIFlashSE(void)
{

///////////  SPI communication start
		CLR_BIT(SPI_STATUS,SPI_CSB);  /// csb go low, enable slave 
		SetFlashSIData(FLASH_WREN);   /// command data, FLASH  command
		SET_BIT(SPI_STATUS,SPI_CSB);  /// CSB go High disable slave

		CLR_BIT(SPI_STATUS,SPI_CSB);		/// csb go low, enable slave 
		SetFlashSIData(FLASH_SE);		/// command data, FLASH Sector Erase command
		SetFlashAddress(0x00, 0xD0,0x00);	
		SET_BIT(SPI_STATUS,SPI_CSB);	/// CSB go High disable slave

		CLR_BIT(SPI_STATUS,SPI_CSB);		/// csb go low, enable slave 
		SetFlashSIData(FLASH_WRDI);		/// command data, FLASH  command
		SET_BIT(SPI_STATUS,SPI_CSB);		/// CSB go High disable slave

}


/**
 * @brief  SPIFlashWrite()
 *
 *  Write data into specified flash address from the pool buffer which pFlashBuffer indicate
 *
 * @return NULL
 *
 */


void SPIFlashWrite(BYTE AddrH,BYTE AddrM,BYTE AddrL, WORD wSize, BYTE *pFlashBuffer)
{
	BYTE bBYTE;
	WORD i;

	////////////  SPI configuration
	SPIEnable();	/// SPI enable

	///////////  SPI communication start
	CLR_BIT(SPI_STATUS,SPI_CSB);	/// csb go low, enable slave 
	SetFlashSIData(FLASH_WREN);	/// command data, FLASH  command
	SET_BIT(SPI_STATUS,SPI_CSB);	/// CSB go High disable slave


	CLR_BIT(SPI_STATUS,SPI_CSB);	/// csb go low, enable slave 
	SetFlashSIData(FLASH_PP);	/// command data, FLASH PP command
	SetFlashAddress(AddrH, AddrM, AddrL);
	for(i=0;i< wSize;i++)
	{
	     bBYTE=*pFlashBuffer;
	     SetFlashSIData(bBYTE);	
			 pFlashBuffer++;
	}	
	SET_BIT(SPI_STATUS,SPI_CSB);	/// CSB go High disable slave

	CLR_BIT(SPI_STATUS,SPI_CSB);	/// csb go low, enable slave 
	SetFlashSIData(FLASH_WRDI);	/// command data, FLASH  command
	SET_BIT(SPI_STATUS,SPI_CSB);	/// CSB go High disable slave

}




#endif

