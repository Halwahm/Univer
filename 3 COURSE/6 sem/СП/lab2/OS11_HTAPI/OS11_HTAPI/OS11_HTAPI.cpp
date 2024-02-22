// OS11_HTAPI.cpp : Определяет экспортируемые функции для DLL.
//

#include "pch.h"
#include "framework.h"
#include "OS11_HTAPI.h"


// Пример экспортированной переменной
OS11HTAPI_API int nOS11HTAPI=0;

// Пример экспортированной функции.
OS11HTAPI_API int fnOS11HTAPI(void)
{
    return 0;
}

// Конструктор для экспортированного класса.
COS11HTAPI::COS11HTAPI()
{
    return;
}
