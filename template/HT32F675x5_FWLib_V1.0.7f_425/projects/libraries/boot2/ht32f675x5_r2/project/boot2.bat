@echo off

set PATH_CRC_EXE=..\..\..\..\..\tools\boot2_pkg\boot2_pkg.exe


set AXF_FILE=%1
:: remove "
set AXF_FILE=%AXF_FILE:"=%
set AXF_SUFFIX=%AXF_FILE:~-4%

set FROMELF=%2
set FROMELF_SUFFIX=%FROMELF:"=%
set FROMELF_SUFFIX=%FROMELF_SUFFIX:~-11%

:: Check the suffix of AXF_FILE
if "%AXF_SUFFIX%" neq ".axf" (
    if "%AXF_SUFFIX%" neq ".AXF" (
        echo "Axf file error!"
        goto PARAM_ERR
    )
)

:: Check the suffix of FROMELF
if "%FROMELF_SUFFIX%" neq "fromelf.exe" (
    echo "fromelf file error"
    goto PARAM_ERR
)

set PROJECT_NAME=%AXF_FILE:~0,-4%
set BIN_FILE=%PROJECT_NAME%.bin
set ASM_FILE=%PROJECT_NAME%.asm
set DST_FILE=%PROJECT_NAME%_patch_lib

::generate bin
::fromelf.exe --bin -o "$L@L.asm"  "!L"
%FROMELF% --bin -o "%BIN_FILE%" "%AXF_FILE%"
if %ERRORLEVEL% neq 0 (
    echo "Make bin error"
    goto PROC_ERR
) else (
    echo "Make bin success!"
)

::generate asm
%FROMELF% --text -c -o "%ASM_FILE%"  "%AXF_FILE%"
if %ERRORLEVEL% neq 0 (
    echo "Make asm error"
    goto PROC_ERR
) else (
    echo "Make asm success!"
)

::calculate crc and output .c
%PATH_CRC_EXE% %BIN_FILE% %DST_FILE%
copy /y %DST_FILE%.c ..\..\..\..\..\libraries\boot2\ht32f675x5_boot2_lib_r2_v1.1.c

::succee
exit /b 0

:PARAM_ERR
exit /b 1

:PROC_ERR
exit /b 2


