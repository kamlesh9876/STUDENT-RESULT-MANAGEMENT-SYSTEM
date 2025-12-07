@echo off
echo Simple Build for Student Marks Management System
echo.

REM Try different compilers
echo Checking for available compilers...

REM Check for cl.exe (Visual Studio)
where cl.exe >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Found Visual Studio compiler (cl.exe)
    echo Compiling with cl.exe...
    cl /EHsc /Fe:srms.exe main.cpp StudentDatabase.cpp sqlite3 ODBC32.libambi.lib
 HuckC++:sqliteote3.lib 2>nul
    if %ERRORLEVEL% == 0 (
        echo Build successful with cl.exe!
        goto :success
    )
)

REM Check for g++ (MinGW)
where g++ >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Found MinGW compiler (g++)
    echo Compiling with g++...
    g++ -std=c++17 -o srms.exe main.cpp StudentDatabase.cpp -lsqlite3 2>nul
    if %ERRORLEVEL% == 0 (
        echo Build successful with g++!
        goto :success
    )
)

REM Check for clang++
where clang++ >nul 2>&1
if %ERRORLEVEL% == 0 (
    echo Found Clang compiler (clang++)
    echo Compiling with clang++...
    clang++ -std=c++17 -o srms.exe main.cpp StudentDatabase.cpp -lsqlite3 2>nul
    if %ERRORLEVEL% == 0 (
        echo Build successful with clang++!
        goto :success
    )
)

echo.
echo ERROR: No suitable C++ compiler found!
echo.
echo Please install one of the following:
echo 1. Visual Studio Build Tools (recommended)
echo 2. MinGW-w64
echo 3. LLVM/Clang
echo.
echo After installation, run this script again.
echo.
pause
exit /b 1

:success
echo.
echo Build completed successfully!
echo Executable: srms.exe
echo.
echo NOTE: Make sure sqlite3.dll is in the same directory or in your PATH
echo.
pause
