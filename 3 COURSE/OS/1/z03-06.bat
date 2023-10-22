@echo off
@chcp 65001
@echo -- параметры: %*
@echo -- режим: %1
@echo -- название файла: %2

if "%1"=="" (goto case1) else (goto case2)
if "%2"=="" (
    @echo название файла не задано 
    goto exit
) else if "%1" neq "создать" or if "%1" neq "удалить" (
    @echo режим задан не корректно
    goto exit
)

:case1
    @echo режим = {создать,удалить}
    @echo файл = название файла 
    goto exit

:case2
    if "%2"=="" (goto case3) else (goto case4)

:case3
    @echo название файла не задано 
    goto exit

:case4
if "%1" == "создать" (goto create)
if "%1" == "удалить" (goto delete) else (goto operation)
:operation
    @echo режим задан не корректно
    goto exit

:create
if exist %2 (goto found)
copy NUL %2
@echo файл %2 создан
goto exit

:delete
if not exist %2 (goto notfound)
del %2
@echo файл %2 удалён
goto exit

:found
@echo файл %2 найден
goto exit

:notfound
@echo файл %2 не найден
goto exit

:exit
@pause