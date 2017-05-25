SET "DEF_SEL=%1"
:LABEL_CHECK_DEF
::=========================================================================
IF "%DEF_SEL%" == "1"  goto LABEL_HTPYE_LARGE_PITCH
IF "%DEF_SEL%" == "2"  goto LABEL_LTPYE_LARGE_PITCH
IF "%DEF_SEL%" == "3"  goto LABEL_1T2R_LARGE_PITCH
IF "%DEF_SEL%" == "4"  goto LABEL_HTPYE_SMALL_PITCH
IF "%DEF_SEL%" == "5"  goto LABEL_LTPYE_SMALL_PITCH
IF "%DEF_SEL%" == "6"  goto LABEL_1T2R_SMALL_PITCH
IF "%DEF_SEL%" == "7"  goto LABEL_F3D_LARGE_PITCH
IF "%DEF_SEL%" == "8"  goto LABEL_F3D_SMALL_PITCH
IF "%DEF_SEL%" == "9"  goto LABEL_FORCE_LARGE_PITCH
IF "%DEF_SEL%" == "10" goto LABEL_FORCE_LARGE_PITCH
IF "%DEF_SEL%" == "11" goto LABEL_1T2R_SMALL_PITCH_CUSTOMER
IF "%DEF_SEL%" == "12" goto LABEL_1T2R_SMALL_PITCH_CUSTOMER_REDUCE
::=========================================================================
		ECHO ------------------------------------------------------------------	
		ECHO Please select the compile option
		ECHO ------------------------------------------------------------------	
		ECHO [#] = 1  : H-type        + Large pitch : 
		ECHO [#] = 2  : L-type        + Large pitch : 
		ECHO [#] = 3  : 1T2R-type     + Large pitch : 
		ECHO [#] = 4  : H-type        + Small pitch : 
		ECHO [#] = 5  : L-type        + Small pitch : 
		ECHO [#] = 6  : 1T2R-type     + Small pitch : 	
		ECHO [#] = 7  : 3D Foce Touch + Large pitch : 			
		ECHO [#] = 8  : 3D Foce Touch + Small pitch : 			
		ECHO [#] = 9  : Foce Touch    + Large pitch : 			
		ECHO [#] = 10 : Foce Touch    + Small pitch : 	
		ECHO [#] = 11 : 1T2R-type     + Small pitch Customer: 		
		ECHO [#] = 12 : 1T2R-type     + Small pitch Customer Reduce: 
		ECHO ------------------------------------------------------------------
  	SET INPUT=
		SET /P INPUT=Please select target:%=% 
		SET DEF_SEL=%INPUT%
		
		GOTO LABEL_CHECK_DEF
		
::=========================================================================	
:LABEL_HTPYE_LARGE_PITCH:
::=========================================================================	
	SET "DEF_NAME=Htype-LPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_HTYPE_DEV_RE_MAPPING"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%	
	GOTO LABEL_LARGE_PITCH	
	
::=========================================================================	
:LABEL_HTPYE_SMALL_PITCH:
::=========================================================================	
	SET "DEF_NAME=Htype-SPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_HTYPE_DEV_RE_MAPPING"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%
	GOTO LABEL_SMALL_PITCH
		
::=========================================================================	
:LABEL_LTPYE_LARGE_PITCH:
::=========================================================================	
	SET "DEF_NAME=Ltype-LPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_LTYPE_DEV_RE_MAPPING"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%	
	GOTO LABEL_LARGE_PITCH	
	
::=========================================================================	
:LABEL_LTPYE_SMALL_PITCH:
::=========================================================================	
	SET "DEF_NAME=Ltype-SPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_LTYPE_DEV_RE_MAPPING"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%
	GOTO LABEL_SMALL_PITCH

::=========================================================================	
:LABEL_1T2R_LARGE_PITCH:
::=========================================================================	
	SET "DEF_NAME=1T2R-LPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_1T2R_ARCHITECTURE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%	
	GOTO LABEL_LARGE_PITCH	
	
::=========================================================================	
:LABEL_1T2R_SMALL_PITCH:
::=========================================================================	
	SET "DEF_NAME=1T2R-SPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_1T2R_ARCHITECTURE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%
	GOTO LABEL_SMALL_PITCH
	
::=========================================================================	
:LABEL_1T2R_SMALL_PITCH_CUSTOMER:
::=========================================================================	
	SET "DEF_NAME=1T2R-SP-C"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_1T2R_ARCHITECTURE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	SET "FEATURE=FEATURE_FORCE_TOUCH"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	SET "FEATURE=FEATURE_CUSTOMER_PROTOCOL"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	GOTO LABEL_SMALL_PITCH

::=========================================================================	
:LABEL_1T2R_SMALL_PITCH_CUSTOMER_REDUCE:
::=========================================================================	
	SET "DEF_NAME=1T2R-SP-CR"
	SET "DEF_TYPE=-D FEATURE_NONE"

	SET "FEATURE=FEATURE_1T2R_ARCHITECTURE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	SET "FEATURE=FEATURE_FORCE_TOUCH"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	SET "FEATURE=FEATURE_CUSTOMER_PROTOCOL"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	SET "FEATURE=FEATURE_REDUCE_CODESIZE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	GOTO LABEL_SMALL_PITCH


::=========================================================================	
:LABEL_F3D_LARGE_PITCH:
::=========================================================================	
	SET "DEF_NAME=F3D-LPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"

	
	SET "FEATURE=FEATURE_FORCE_TOUCH"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%
	
	GOTO LABEL_LARGE_PITCH

::=========================================================================	
:LABEL_F3D_SMALL_PITCH:
::=========================================================================	
	SET "DEF_NAME=F3D-SPitch"
	SET "DEF_TYPE=-D FEATURE_NONE"
		
	SET "FEATURE=FEATURE_FORCE_TOUCH"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%
	
	GOTO LABEL_SMALL_PITCH

::=========================================================================	
:LABEL_FORCE_LARGE_PITCH:
::=========================================================================	
	SET "DEF_NAME=ForceTouch"
	SET "DEF_TYPE=-D FEATURE_NONE"

  :: for Force Touch C1 detect
	SET "FEATURE=FEATURE_FORCE_TOUCH"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%

	:: for Force Touch C2 detect
	SET "FEATURE=FEATURE_PRESS_TOUCH"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%
	
	GOTO LABEL_SMALL_PITCH
	
::=========================================================================	
:LABEL_LARGE_PITCH:
	SET "FEATURE=FEATURE_NINE_SQUARE_ENABLE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%	
	GOTO LABEL_END

:LABEL_SMALL_PITCH:
	SET "FEATURE=FEATURE_CLUSTER_ENABLE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%	
	GOTO LABEL_END	
  
  
:LABEL_END:		
	SET "FEATURE=FEATURE_MCU_LIB_ENABLE"	
	SET "DEF_TYPE=%DEF_TYPE% -D %FEATURE%"
	ECHO  + %FEATURE%	

	SET "FEATURE=%COMPILE_TARGET_IC%"	
	SET "DEF_TYPE=%DEF_TYPE% -D FEATURE_PROJECT_%FEATURE%"
	ECHO  + FEATURE_PROJECT_%FEATURE%	
	
	::ECHO %DEF_TYPE%
				