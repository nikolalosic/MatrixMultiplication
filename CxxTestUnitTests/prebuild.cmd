GOTO comment
//============================================================================
// File Name   : prebuild.cmd
// Authors     : Nikola Losic
// Version     : 1.0
// Copyright   : Nikola Losic ©. All rights reserved
// Description : Contains commands that are executed before building or rebuilding a project
//============================================================================
:comment

ECHO Making runner file

WHERE python
IF %ERRORLEVEL% NEQ 0 GOTO Error


python ../ExternalLibs/cxxtest-4.4/bin/cxxtestgen --runner=ParenPrinter -o runner.cpp ^
MatrixTestSuite.h StrassenSerialTestSuite.h StrassenPrallelTestSuite.h

ECHO Making runner file completed

GOTO End

:Error

ECHO ++++++++++++++++++++++++++++++++++++++++++ERROR++++++++++++++++++++++++++++++++++++++++++++++++
ECHO +                                                                                             +
ECHO +                                No python in the path                                        +
ECHO +                                                                                             +
ECHO ++++++++++++++++++++++++++++++++++++++++++ERROR++++++++++++++++++++++++++++++++++++++++++++++++

ECHO ERROR: No python in the path
  EXIT /b 1

:End