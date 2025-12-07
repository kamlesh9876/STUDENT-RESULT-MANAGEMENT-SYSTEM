@echo off
echo Running Student Marks Management System...
echo.

REM Check if executable exists
if not exist "build\bin\srms.exe" (
    echo Executable not found! Please build the project first using build.bat
    echo.
    pause
    exit /b 1
)

REM Navigate to bin directory
cd build\bin

REM Run the application
echo Starting application...
srms.exe

echo.
echo Application closed.
pause
