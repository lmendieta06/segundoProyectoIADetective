@echo off
echo ========================================
echo Compilando Motor de Inferencia...
echo ========================================
echo.

g++ -std=c++11 -c Logica.cpp
if errorlevel 1 goto error

g++ -std=c++11 -c MotorResolucion.cpp
if errorlevel 1 goto error

g++ -std=c++11 -c main.cpp
if errorlevel 1 goto error

g++ -std=c++11 -o detective.exe Logica.o MotorResolucion.o main.o
if errorlevel 1 goto error

echo.
echo ========================================
echo Compilacion exitosa!
echo ========================================
echo.
echo Ejecutando programa...
echo.
detective.exe
goto end

:error
echo.
echo ========================================
echo ERROR en la compilacion
echo ========================================
pause
exit /b 1

:end
echo.
pause