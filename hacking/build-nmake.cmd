@echo off
::
:: $Id: build-nmake.cmd 290 2012-06-15 23:36:47Z alba $
:: 
setlocal

call %~dp0setenv.cmd
if not defined PWD goto :EOF

set "BUILD_DIR=build-nmake"
set "GENERATOR=NMake Makefiles"

if "%1" == "rebuild" rmdir /q/s %BUILD_DIR% & rmdir /q/s %CMAKE_INSTALL_PREFIX%

mkdir %BUILD_DIR%
cd %BUILD_DIR%
if errorlevel 1 goto :EOF

cmake -Wdev ^
	-G "%GENERATOR%" ^
	"-DCMAKE_INSTALL_PREFIX=%CMAKE_INSTALL_PREFIX%" ^
	"-DBUILD_SHARED_LIBS=ON" ^
	"-DWITH_TESTING=ON" ^
	"-DWITH_SEPARATE_LIBS=OFF" ^
	..
if errorlevel 1 goto :EOF

nmake all
if errorlevel 1 goto :EOF

setlocal
set "PATH=%PATH%;%PWD%\%BUILD_DIR%"
nmake test
if errorlevel 1 goto :EOF
endlocal

nmake install
if errorlevel 1 goto :EOF
