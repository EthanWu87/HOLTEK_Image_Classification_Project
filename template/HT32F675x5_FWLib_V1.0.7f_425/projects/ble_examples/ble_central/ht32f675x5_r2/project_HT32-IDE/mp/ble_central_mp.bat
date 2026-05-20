:: After build script for GNU GCC Compiler

@echo off

set ELF_FILE=%1.elf
set ELF_FILE=%ELF_FILE:"=%
set ELF_SUFFIX=%ELF_FILE:~-4%


:: Check the suffix of ELF_FILE
if "%ELF_SUFFIX%" neq ".elf" (
    if "%ELF_SUFFIX%" neq ".ELF" (
        echo "Elf file error!"
        goto PARAM_ERR
    ) else (
        echo "Elf file success!"
    )
) else (
  echo "Elf file success!"
)


set PROJECT_NAME=%ELF_FILE:~0,-4%

set BIN_FILE=%PROJECT_NAME%.bin
set TEXT_FILE=%PROJECT_NAME%.text
set DST_FILE=%~n0
set DST_FILE=%DST_FILE:~0,-3%

::generate bin
arm-none-eabi-objcopy.exe -O binary "%ELF_FILE%" "%BIN_FILE%"
if %ERRORLEVEL% neq 0 (
    echo "Make bin error"
    goto PROC_ERR
) else (
    echo "Make bin success!"
)

::generate text
arm-none-eabi-objdump.exe -S "%1.elf"  > "%1.text"
if %ERRORLEVEL% neq 0 (
    echo "Make text error"
    goto PROC_ERR
) else (
    echo "Make text success!"
)

copy /y %PROJECT_NAME%.hex ..\..\..\hex\%DST_FILE%.hex

::pause
