#include "afxwin.h"		//cdc
#include "atltypes.h"	//crect

#ifndef LIBGRAPH
#define LIBGRAPH 1
const double pi=3.14159;

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
  CRectD(){left=top=right=bottom=0;};
  CRectD(double l,double t,double r,double b);
  void SetRectD(double l,double t,double r,double b);
  CSizeD SizeD();
 }; 

CMatrix SpaceToWindow(CRectD& rs,CRect& rw);

CMatrix CreateViewCoord(double r,double fi,double q);
CMatrix VectorMult(CMatrix& V1,CMatrix& V2);
double ScalarMult(CMatrix& V1,CMatrix& V2);
CMatrix SphereToCart(CMatrix& PView);
#endif