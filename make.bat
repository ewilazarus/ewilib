REM MUST BE TESTED IN A WINDOWS MACHINE

@echo off

set inputval=%1
if "%inputval%" == "" set inputval="cmake"

if "%inputval%" == "cmake" (
	REM create ./build if not exists and cds into it
	if not exist "%~dp0\build" mkdir "%~dp0\build"
	cd "%~dp0\build"

	REM it might be required to specify cmake's fullpath
	start "" "cmake.exe -G ""Visual Studio 12"" %~dp0"

	goto:eof
	)
if "%inputval%" == "clean" (
	REM deletes ./build if exist
	if exist "%~dp0\build" rd "%~dp0\build /s /q"

	goto:eof
	)

echo Usage:
echo make.bat [clean ^| cmake]
