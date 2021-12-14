#pragma once

#include "Misc.h"
#include "figure.h"

class MyEllipse : public Figure
{
public:
	MyEllipse(MyPoint start, MyPoint end);
	void paint(HDC hDC);
};