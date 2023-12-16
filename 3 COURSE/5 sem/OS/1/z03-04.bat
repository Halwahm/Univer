@chcp 65001
@echo -- параметры: %1 %2 %3 %4 %5 %6 %7 %8 %9
@echo -- параметр 1: %1
@echo -- параметр 2: %2
@echo -- параметр 3: %3
@echo off
set /A a = %1%
set /A b = %2%
set /A c = %3%
set /A sum = a + b
set /A mul = a * b
set /A div = c / b
set /A min = b - a
set /A min2 = a - b
set /A expr = min * min2
@echo on
@echo %1 + %2 = %sum%
@echo %1 * %2 = %mul%
@echo %3 / %2 = %div%
@echo %2 - %1 = %min%
@echo (%2 - %1) * (%1 - %2) =%expr%
@pause