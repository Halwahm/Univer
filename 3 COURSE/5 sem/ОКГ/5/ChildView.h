// ChildView.h: интерфейс класса CChildView
//
#pragma once
// Окно CChildView

class CChildView : public CWnd
{
	// Создание
public:
	CChildView();

	// Атрибуты
public:
	double r, fi, q; // Сферические координаты точки наблюдения в МСК
	CRect WRect;
	int Index;	// Индикатор для OnPaint
	CPlot3D  Graph1, Graph2, Graph3;	// Объявление объектов типа CPlot3D
	// Операции
public:

	// Переопределение
protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	// Реализация
public:
	virtual ~CChildView();

	// Созданные функции схемы сообщений
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	// действия при выборе пункта меню
	afx_msg void OnCPlot3DDef();
	afx_msg void OnCplot3dFunc1();
	afx_msg void OnCplot3dFunc2();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

