@echo off
setlocal

echo ========================================
echo Compilando Motor de Inferencia...
echo ========================================

g++ -std=c++11 -c Logica.cpp || goto error
g++ -std=c++11 -c MotorResolucion.cpp || goto error
g++ -std=c++11 -c main.cpp || goto error
g++ -std=c++11 -o detective.exe Logica.o MotorResolucion.o main.o || goto error

echo.
echo ========================================
echo Compilacion exitosa!
echo ========================================
echo.

REM Ejecuta pasando opcionalmente el primer argumento al exe
if "%~1"=="" goto run_interactive

echo Ejecutando con archivo de clausulas: %~1
call "%~dp0detective.exe" "%~1"
goto end_run

:run_interactive
echo Ejecutando en modo interactivo (entrada manual)...
call "%~dp0detective.exe"

:end_run
endlocal
pause
goto :eof

:error
echo.
echo ========================================
echo ERROR en la compilacion
echo ========================================
pause
exit /b 1
echo.
pause
