#include "Windows.h"
#include "myrectangle.h"

MyRectangle::MyRectangle(MyPoint start, MyPoint end, COLORREF color) : Figure(start, end, color) { }

void MyRectangle::paintFigure(HDC hDC)
{
	Rectangle(hDC, start_.x_, start_.y_, end_.x_, end_.y_);
}