@chcp 65001
@echo -- параметры: %*
@echo -- параметр 1: %1
@echo -- параметр 2: %2
@echo -- параметр 3: %3
@echo off
set /a res= %1 %3 %2
echo -- результат: %res%
@pause