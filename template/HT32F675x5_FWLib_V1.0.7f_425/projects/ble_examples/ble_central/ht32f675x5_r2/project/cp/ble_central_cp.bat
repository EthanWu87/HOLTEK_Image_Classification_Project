::after build for M0p

@echo off

set BIN2ARRAY=..\..\..\..\..\..\tools\bin2array\bin2array.exe



set AXF_FILE=%1
set AXF_FILE=%AXF_FILE:"=%

set FROMELF=%2

set AXF_SUFFIX=%AXF_FILE:~-4%
set FROMELF_SUFFIX=%FROMELF:"=%
set FROMELF_SUFFIX=%FROMELF_SUFFIX:~-11%


if "%AXF_SUFFIX%" neq ".axf" (
    if "%AXF_SUFFIX%" neq ".AXF" (
        echo "Axf file error!"
        goto PARAM_ERR
    ) else (
        echo "Axf file success!"
    )
)

if "%FROMELF_SUFFIX%" neq "fromelf.exe" (
    echo "fromelf file error"
    goto PARAM_ERR
) else (
    echo "Fromelf file valid!"
)

set PROJECT_NAME=%AXF_FILE:~0,-4%

set BIN_FILE=%PROJECT_NAME%.bin
set ASM_FILE=%PROJECT_NAME%.asm

::generate bin
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

::generate bin array
%BIN2ARRAY% -o "./app_code_cp.c" ^
-buf_name "g_u8CpAppCode" -section "__attribute__((section(\".cp.app.code\")))" ^
"%BIN_FILE%"
if %ERRORLEVEL% neq 0 (
    echo "Make app error"
    goto PROC_ERR
) else (
    echo "Make app success!"
)

echo "Make done!"

::succeed
exit /b 0

:PARAM_ERR
exit /b 1

:PROC_ERR
exit /b 2
