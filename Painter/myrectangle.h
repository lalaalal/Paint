#pragma once

#include "Misc.h"
#include "figure.h"

class MyRectangle : public Figure {
public:
	MyRectangle(MyPoint start, MyPoint end, COLORREF color = RGB(0, 0, 0));

protected:
	void paintFigure(HDC hDC) override;
};