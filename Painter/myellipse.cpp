#include <Windows.h>
#include "myellipse.h"

MyEllipse::MyEllipse(MyPoint start, MyPoint end) : Figure(start, end) { }

void MyEllipse::paint(HDC hdc)
{
	Ellipse(hdc, start_.x_, start_.y_, end_.x_, end_.y_);
}