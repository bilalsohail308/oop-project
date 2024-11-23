@echo off
rem Check if main filename is provided
if "%1"=="" (
    echo Please provide the main file name without extension.
    exit /b
)

rem Set SFML include and lib directories
set SFML_INCLUDE=C:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\include
set SFML_LIB=C:\SFML-Progs\SFML-2.5.1\SFML-2.5.1\lib

rem Files to compile
set FILES=main.cpp AuthScreen.cpp User.cpp FileDialog.cpp FormWindow.cpp Event.cpp

rem Compile each .cpp file
for %%F in (%FILES%) do (
    g++ -c %%F -I%SFML_INCLUDE% -std=c++17
    if %errorlevel% neq 0 (
        echo Compilation failed for %%F.
        exit /b
    )
)

rem Link all object files
g++ main.o AuthScreen.o User.o FileDialog.o FormWindow.o Event.o -o %1 -L%SFML_LIB% -lsfml-graphics -lsfml-window -lsfml-system -lcomdlg32

rem Notify if linking was successful
if %errorlevel% equ 0 (
    echo Linking successful.
    echo Executable created: %1.exe
) else (
    echo Linking failed.
    exit /b
)
