::==================================================================::
:: File  : Make All.BAT
:: Description: Make the Keil C source code 
:: Author: JLJuang
:: E-Mail: JLJuang@csie.nctu.edu.tw
:: NOTE  : All copy rights reserved (c) since 2003
::==================================================================::
@echo on
cls


IF "%COMPILE_TARGET_IC%" == "ZET7100"  goto LABEL_ZET7100_SETUP
IF "%COMPILE_TARGET_IC%" == "ZET6275"  goto LABEL_ZET6275_SETUP

:LABEL_ZET7100_SETUP  
	CALL JVER.BAT
	GOTO LABEL_SETUP_END	
		
:LABEL_ZET6275_SETUP	 
  DEL .\INC\Revision.h
  COPY ..\..\ZET6275\WORK\INC\Revision.h .\INC\
  GOTO LABEL_SETUP_END		

:LABEL_SETUP_END:



::CALL SETTING.BAT
::-----------------------------------------------------------------::
::    STEP 1: Clear all bin
::-----------------------------------------------------------------::
DEL %DEV_PATH%\%PROJECT_NAME%\%PANEL_TYPE%\*.bin

::-----------------------------------------------------------------::
::    STEP 2: make bin to ZET_DEFAULT 
::-----------------------------------------------------------------::

 ::[#] = 1  : H-type    + Large pitch   :   Htype-LPitch
 ::[#] = 2  : L-type    + Large pitch   :   Ltype-LPitch
 ::[#] = 3  : 1T2R-type + Large pitch   :   1T2R-LPitch 
 ::[#] = 4  : H-type    + Small pitch   :   Htype-SPitch
 ::[#] = 5  : L-type    + Small pitch   :   Ltype-SPitch
 ::[#] = 6  : 1T2R-type + Small pitch   : 	1T2R-SPitch 
 ::[#] = 7  : 3D Foce Touch+ Large pitch  : F3D-LPitch
 ::[#] = 8  : 3D Foce Touch+ Small pitch  : F3D-SPitch
 ::[#] = 9  : Foce Touch+ Large pitch : 		Force-LPitch //FEATURE_PRESS_TOUCH
 ::[#] = 10 : Foce Touch+ Small pitch : 		Force-SPitch
 ::[#] = 11 : 1T2R-type + Small pitch customer : 1T2R-SP-C
 ::[#] = 12 : 1T2R-type + Small pitch customer reduce : 1T2R-SP-CR
::------------------------------------------------------------------
::CALL nMAKE.BAT 1 1
::CALL nMAKE.BAT 1 2
::CALL nMAKE.BAT 1 3 
::CALL nMAKE.BAT 1 4
::CALL nMAKE.BAT 1 5
::CALL nMAKE.BAT 1 6
::CALL nMAKE.BAT 1 7
::CALL nMAKE.BAT 1 8
::CALL nMAKE.BAT 1 9
CALL nMAKE.BAT 1 11
CALL nMAKE.BAT 1 12

::CLEAN
