@echo off
echo Compiling with Visual Studio Compiler...
echo.

REM Navigate to project directory
cd /d "C:\Users\kamle\.vscode\suyog\SRMS"

REM Download SQLite amalgamation if not exists
if not exist "sqlite3.c" (
    echo Downloading SQLite source...
    powershell -Command "Invoke-WebRequest -Uri 'https://www.sqlite.org/2023/sqlite3.c' -OutFile 'sqlite3.c'"
    powershell -Command "Invoke-WebRequest -Uri 'https://www.sqlite.org/2023/sqlite3.h' -OutFile 'sqlite3.h'"
)

REM Compile with Visual Studio
echo Compiling...
cl /EHsc /Fe:srms.exe main.cpp StudentDatabase.cpp sqlite3.c

if %ERRORLEVEL% == 0 (
    echo.
    echo Build successful!
    echo Executable: srms.exe
    echo.
    pause
) else (
    echo.
    echo Build failed!
    pause
)
