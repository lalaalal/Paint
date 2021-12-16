#include <Windows.h>
#include "myellipse.h"

MyEllipse::MyEllipse(MyPoint start, MyPoint end, COLORREF color) : Figure(start, end, color) { }

void MyEllipse::paintFigure(HDC hdc)
{
	Ellipse(hdc, start_.x_, start_.y_, end_.x_, end_.y_);
}