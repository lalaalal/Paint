#include "Windows.h"
#include "myrectangle.h"

MyRectangle::MyRectangle(MyPoint start, MyPoint end) : Figure(start, end) { }

void MyRectangle::paint(HDC hDC)
{
	Rectangle(hDC, start_.x_, start_.y_, end_.x_, end_.y_);
}