@echo off
::
:: $Id: build.cmd 288 2012-06-15 19:10:20Z alba $
:: 
setlocal

:: The special character "%" needs to be doubled in batch files.
if not defined GIGLGU_LOGFILE set "GIGLGU_LOGFILE=%%P-%%T.log"
if not defined CMAKE_INSTALL_PREFIX set "CMAKE_INSTALL_PREFIX=%~d0\opt\giglgu"
if not defined BOOST_INCLUDEDIR set "BOOST_INCLUDEDIR=%~d0\source\boost"

set "PWD="
for /f %%i in ('cd') do set "PWD=%%i"
if not defined PWD goto :EOF

set "BUILD_DIR=build-x64"
set "GENERATOR=Visual Studio 10 Win64"

set "BUILD_DIR=build-x86"
set "GENERATOR=Visual Studio 10"

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

devenv giglgu.sln /build Debug /project ALL_BUILD
if errorlevel 1 goto :EOF

setlocal
set "PATH=%PATH%;%PWD%\%BUILD_DIR%\\Debug;%PWD%\%BUILD_DIR%\windows\src\Debug;%PWD%\%BUILD_DIR%\logging\src\Debug;%PWD%\%BUILD_DIR%\base\src\Debug"
:: echo %PATH%
devenv giglgu.sln /build Debug /project RUN_TESTS
if errorlevel 1 goto :EOF
endlocal

devenv giglgu.sln /build Debug /project INSTALL
if errorlevel 1 goto :EOF