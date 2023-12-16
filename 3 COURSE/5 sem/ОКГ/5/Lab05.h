
// Lab05.h: основной файл заголовка для приложения Lab03
//
#pragma once

#ifndef __AFXWIN_H__
#error "включить stdafx.h до включения этого файла в PCH"
#endif

#include "resource.h"       // основные символы


// CLab05App:
// Сведения о реализации этого класса: Lab05.cpp
//

class CLab05App : public CWinApp
{
public:
	CLab05App() noexcept;

	// Переопределение
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	// Реализация

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab05App theApp;

