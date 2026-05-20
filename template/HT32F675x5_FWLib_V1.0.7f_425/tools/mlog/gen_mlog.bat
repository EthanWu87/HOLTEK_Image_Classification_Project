@echo off
::echo %1
::echo %2
::set projname = %2
::set rootpath = %3
::set keilpath = %1


::set projname = %1
::set rootpath = %2
 

%2\tools\mlog\gen_mlog_script.exe %1 1
if %ERRORLEVEL% neq 0 (
    echo "Make mlog error"
    goto PROC_ERR  
) else (
    echo "Make mlog success!"
    
)

::succeed
exit /b 0

:PROC_ERR
exit /b 2

