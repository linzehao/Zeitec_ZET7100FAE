::==================================================================::
:: File  : JLINK.BAT
:: Author: JLJuang
:: E-Mail: JLJuang@csie.nctu.edu.tw
:: NOTE  : All copy rights reserved (c) since 2003
::==================================================================::
@ECHO OFF 
@echo ##################################################
@echo #                 LINK OBJECTS                   #
@echo ##################################################

SET OPTIZE_LEVEL=%1


::------------------------::
:: Set Target
::------------------------::

SET TARGET=%PROJECT_NAME%
SET SAG_FILE=%PROJECT_NAME%.sag
SET LD_FILE=%PROJECT_NAME%.ld

:SET LINK_LIST= Adc.o Algorithm.o CodeTbl.o Coordinate.o Calibration.o DataFormat.o Hover.o Nds.o Sys.o Task.o Timer.o TpCmd.o ZET7100_FrequencyHop.o ZET7100_InitScan.o ZET7100_KeyScan.o ZET7100_MutualScan.o ZET7100_Region.o ZET7100_Trace.o
IF "%COMPILE_TARGET_IC%" == "ZET7100" (
SET LINK_LIST= Nds.o ZET7100_Trace.o Calibration.o TpCmd.o Hover.o ZET7100_KeyScan.o ZET7100_Region.o Algorithm.o DataFormat.o Adc.o ZET7100_InitScan.o ZET7100_MutualScan.o Task.o Timer.o Sys.o CodeTbl.o Coordinate.o ZET7100_FrequencyHop.o
) 

IF "%COMPILE_TARGET_IC%" == "ZET6275" (
SET LINK_LIST= Nds.o ZET7100_Trace.o Calibration.o TpCmd.o Hover.o ZET6275_KeyScan.o ZET6275_Region.o Algorithm.o DataFormat.o Adc.o ZET6275_InitScan.o ZET6275_MutualScan.o Task.o Timer.o Sys.o CodeTbl.o Coordinate.o ZET6275_FrequencyHop.o
)
SET LIB_FILE=..\LIB\%PROJECT_NAME%_%DEF_NAME%_LIB.a
SET AR_LIB_FILE=../LIB/%PROJECT_NAME%_%DEF_NAME%_LIB.a
SET LIB_OBJ_LIST= I2c.o Isr.o Main.o Customer.o %AR_LIB_FILE%

::------------------------::
:: Linker flags
::------------------------::
SET LDFLAGS=-%OPTIZE_LEVEL% -nostartfiles -static -T"%LD_FILE%" -Wl,--gc-sections

::------------------------::
:: Link the data flash
::------------------------::
IF "%COMPILE_TARGET_IC%" == "ZET7100"  goto LABEL_ZET7100_SETUP
IF "%COMPILE_TARGET_IC%" == "ZET6275"  goto LABEL_ZET6275_SETUP

:LABEL_ZET7100_SETUP    
  SET LDFLAGS=%LDFLAGS%,--section-start=.DATA_ROM=0xE000,--section-start=.PROJ_ROM=0x00DFFC
  ::SET LDFLAGS=%LDFLAGS%,--section-start=.DATA_ROM=0xEC00,--section-start=.PROJ_ROM=0x00DFFC
  :: SET LDFLAGS=%LDFLAGS%,--section-start=.DATA_ROM=0x9C00,--section-start=.PROJ_ROM=0x009BFC
	GOTO LABEL_SETUP_END	
		
:LABEL_ZET6275_SETUP	 

  SET LDFLAGS=%LDFLAGS%,--section-start=.DATA_ROM=0x9C00,--section-start=.PROJ_ROM=0x009BFC
	GOTO LABEL_SETUP_END		

:LABEL_SETUP_END:


::------------------------::
:: LINK SECTION
::------------------------::
IF "%COMPILE_TARGET_IC%" == "ZET7100"  goto LABEL_ZET7100_LINK_SETUP
IF "%COMPILE_TARGET_IC%" == "ZET6275"  goto LABEL_ZET6275_LINK_SETUP
:LABEL_ZET7100_LINK_SETUP  
SET RMSEC=
::CALL JLS .MEM_ZETVAR 	 0x100800
CALL JLS .REG_TRUMA0   	 0x194004
CALL JLS .REG_TRUMB0   	 0x194024

::CALL JLS .MEM_ZETVARPARA 	 0x100800
CALL JLS .MEM_ZETVARPARA 	 00100000

GOTO LABEL_LINK_SETUP_END	  


:LABEL_ZET6275_LINK_SETUP  
SET RMSEC=
::CALL JLS .MEM_ZETVAR 	 0x100800
::CALL JLS .REG_ADBASE 	 0x1BC050
CALL JLS .REG_ADC   	 0x1BC090
CALL JLS .REG_DEV   	 0x1BC0F0
CALL JLS .REG_AVGDEV   0x1BC140
::CALL JLS .REG_GPIO     0x18C040
GOTO LABEL_LINK_SETUP_END


:LABEL_LINK_SETUP_END:


::------------------------::
:: HEX to BIN
::------------------------::
SET OBJCOPYFLAGS=-O binary -S -R .note -R .comment -R .MEM 
SET OBJCOPYFLAGS=%OBJCOPYFLAGS% %RMSEC%
REM SET NMFLAGS = -B -n -c -l -v --numeric-sort
SET NMFLAGS= -B -n -l -S


::===============================================::
:: 1. Create LD
::===============================================::
%LDSAG% %SAG_FILE% -o %BIN_PATH%\%LD_FILE%
REM COPY %PROJECT_NAME%.LD %BIN_PATH%\ 
ECHO OFF

::===============================================::
:: 2. link
::===============================================::
@CD %BIN_PATH%\
echo OFF
%CC% %LDFLAGS%  %LIB_OBJ_LIST%  -o %TARGET%.elf   -lnds32_isr -lm
echo OFF

::===============================================::
:: 3. Dump BIN
::===============================================::
IF NOT EXIST %TARGET%.elf (GOTO LABEL_FAIL_END)


::===============================================::
:: 4. For Code debug dump out
::===============================================::
 %OBJDUMP% -D %TARGET%.elf > %TARGET%.S
REM  %OBJDUMP% -x -d -C %TARGET%.elf > %TARGET%.MAP

:: For designer simulation
REM %OBJDUMP% -D %TARGET%.elf > %TARGET%.S

%OBJCOPY% %OBJCOPYFLAGS% %TARGET%.elf JOUT.bin 
%NM% %NMFLAGS% %TARGET%.elf > %TARGET%.NM
%SIZE% %TARGET%.elf

@CD..
ECHO  OFF
GOTO LABEL_END

::===============================================::
:: FAIL END
::===============================================::
:LABEL_FAIL_END
@cd ..
SET	SUCCESS=FALSE2

::===============================================::
:: END
::===============================================::
:LABEL_END
