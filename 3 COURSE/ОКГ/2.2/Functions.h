#pragma once
#include <math.h>
#include "CMatrix.h"
#include <afxwin.h>

struct CSizeD
{
	double cx;
	double cy;
};
struct CRectD
{
	double left;
	double top;
	double right;
	double bottom;
	CRectD()
	{
		left = top = right = bottom = 0;
	}
	CRectD(double l, double t, double r, double b);
	void setRectD(double l, double t, double r, double b);
	CSizeD SizeD();
};
struct CMyPen
{

	int PenStyle;
	COLORREF PenColor;
	int PenWidth;
public:
	CMyPen()
	{
		PenStyle = PS_SOLID;
		PenWidth = 1;
		PenColor = RGB(0, 0, 0);
	}
	void Set(int PS, int PW, COLORREF PC)
	{
		PenStyle = PS;
		PenWidth = PW;
		PenColor = PC;
	}
};

CMatrix SpaceToWindow(CRectD& rs, CRect& rw);
// ���������� ������� ��������� ��������� �� ������� � �������
// rs - ������� � ������� ����������� - double
// rw - ������� � ������� ����������� - int
class CPlot2D
{
	CMatrix X;				// ��������
	CMatrix Y;				// �������
	CMatrix K;				// ������� ��������� ��������
	CRect RW;				// ������������� � ����
	CRectD RS;				// ������������� ������� � ���
	CMyPen PenLine;                         // ���� ��� �����
	CMyPen PenAxis;                        // ���� ��� ����
public:
	CPlot2D(){ K.RedimMatrix(3, 3); };          //����������� �� ���������
	void SetParams(CMatrix& XX, CMatrix& YY, CRect& RWX); // ���������
	// ���������� �������
	void SetWindowRect(CRect& RWX);	//��������� ������� � ���� ��� ����������� 
	//�������
	void GetWindowCoords(double xs, double ys, int &xw, int &yw); //��������
	//���������� ����� �� ��� � ���
	void SetPenLine(CMyPen& PLine);	// ���� ��� ��������� �������
	void SetPenAxis(CMyPen& PAxis);	// ���� ��� ���� ���������
	void Draw(CDC& dc, int Ind1, int Int2);	// ��������� � ��������������� ����������
	//���������
};

class CChildView
{
public:
	double MyF1(double x)
	{
		return (sin(x) / x);
	}
	double MyF2(double x)
	{
		return (sqrt(x)*sin(x));
	}
};