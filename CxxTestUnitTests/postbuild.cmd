GOTO comment
//============================================================================
// File Name   : postbuild.cmd
// Authors     : Nikola Losic
// Version     : 1.0
// Copyright   : Nikola Losic ©. All rights reserved
// Description : Contains commands that are executed after building or rebuilding a project
//============================================================================
:comment

ECHO Compiling Tests

WHERE cl
IF %ERRORLEVEL% NEQ 0 GOTO Error

cl /GL /MD /Fo%1\ -o %1runner.exe ^
runner.cpp ^
HelpFunctions.cpp ^
/I..\ExternalLibs\cxxtest-4.4  ^
/I..\CommonLib ^
/I..\MatrixMultiplicationSerialLib\ ^
/I..\MatrixMultiplicationParallelLib\ ^
/I..\ExternalLibs\armadillo-7.100.3\include ^
%2CommonLib.lib ^
%2MatrixMultiplicationSerialLib.lib ^
%2MatrixMultiplicationParallelLib.lib ^
..\ExternalLibs\armadillo-7.100.3\lib_win64\blas_win64_MT.lib ^
..\ExternalLibs\armadillo-7.100.3\lib_win64\lapack_win64_MT.lib


ECHO -----------------------------------------------------------------------------------------------
ECHO Running Tests
ECHO -----------------------------------------------------------------------------------------------
%1runner.exe 
ECHO -----------------------------------------------------------------------------------------------
ECHO Tests Completed
ECHO -----------------------------------------------------------------------------------------------

GOTO End

:Error

ECHO ++++++++++++++++++++++++++++++++++++++++++ERROR++++++++++++++++++++++++++++++++++++++++++++++++
ECHO +                                                                                             +
ECHO +                                No cl compiler in the path                                   +
ECHO +                                                                                             +
ECHO ++++++++++++++++++++++++++++++++++++++++++ERROR++++++++++++++++++++++++++++++++++++++++++++++++


ECHO ERROR: No cl compiler in the path
  EXIT /b 1

:End