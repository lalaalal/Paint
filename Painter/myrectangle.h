#pragma once

#include "Misc.h"
#include "figure.h"

class MyRectangle : public Figure
{
public:
	MyRectangle(MyPoint start, MyPoint end);
	void paint(HDC hDC) override;
};