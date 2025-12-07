@echo off
echo Building Student Marks Management System...
echo.

REM Check if build directory exists, create if not
if not exist "build" (
    echo Creating build directory...
    mkdir build
)

REM Navigate to build directory
cd build

REM Configure with CMake
echo Configuring with CMake...
cmake .. -G "MinGW Makefiles" || (
    echo CMake configuration failed!
    pause
    exit /b 1
)

REM Build the project
echo Building project...
cmake --build . --config Release || (
    echo Build failed!
    pause
    exit /b 1
)

REM Copy database.sql to bin directory
echo Copying database files...
copy ..\database.sql bin\ >nul

echo.
echo Build completed successfully!
echo Executable location: build\bin\srms.exe
echo.
pause
