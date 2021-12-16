#pragma once

#include "Misc.h"
#include "figure.h"

class MyEllipse : public Figure
{
public:
	MyEllipse(MyPoint start, MyPoint end, COLORREF color = RGB(0, 0, 0));

protected:
	void paintFigure(HDC hDC);
};