::
:: $Id: setenv.cmd 290 2012-06-15 23:36:47Z alba $
:: 
:: No "setlocal" since this file is called by other scripts. 

:: The special character "%" needs to be doubled in batch files.
if not defined GIGLGU_LOGFILE set "GIGLGU_LOGFILE=%%P-%%T.log"
if not defined CMAKE_INSTALL_PREFIX set "CMAKE_INSTALL_PREFIX=%~d0\opt\giglgu"
if not defined BOOST_INCLUDEDIR set "BOOST_INCLUDEDIR=%~d0\source\boost"

set "PWD="
for /f %%i in ('cd') do set "PWD=%%i"
