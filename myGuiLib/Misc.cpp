#include <cmath>

#include "Misc.h"

MyPoint::MyPoint(int x, int y) : x_(x), y_(y) {

}

MyPoint::MyPoint() : x_(0), y_(0) {

}

double MyPoint::Abs() const {
	return std::sqrt(x_ * x_ + y_ * y_);
}

MyPoint MyPoint::operator-() const {
	return MyPoint(-x_, -y_);
}

MyPoint MyPoint::operator+(const MyPoint& rhs) const {
	return MyPoint(x_ + rhs.x_, y_ + rhs.y_);
}

MyPoint MyPoint::operator-(const MyPoint& rhs) const {
	return *this + -rhs;
}

const MyPoint& MyPoint::operator+=(const MyPoint& rhs) {
	this->x_ += rhs.x_;
	this->y_ += rhs.y_;

	return *this;
}

const MyPoint& MyPoint::operator-=(const MyPoint& rhs) {
	return *this += -rhs;
}

bool MyPoint::operator==(const MyPoint& rhs) const {
	return x_ == rhs.x_ && y_ == rhs.y_;
}

bool MyPoint::operator!=(const MyPoint& rhs) const {
	return !(* this == rhs);
}

MyEvent::MyEvent(UINT msg, WPARAM wParam, LPARAM lParam) :
	msg_(msg), wParam_(wParam), lParam_(lParam) 
{
	//  Nothing to do here.
}

bool MyEvent::isLButtonDown() {
	return msg_ == WM_LBUTTONDOWN;
}
bool MyEvent::isLButtonUp() {
	return msg_ == WM_LBUTTONUP;
}
bool MyEvent::isRButtonDown() {
	return msg_ == WM_RBUTTONDOWN;
}
bool MyEvent::isRButtonUp() {
	return msg_ == WM_RBUTTONUP;
}
bool MyEvent::isCtrlKeyDown() {
	return wParam_ & MK_CONTROL;
}
bool MyEvent::isShiftKeyDown() {
	return wParam_ & MK_SHIFT;
}

int MyEvent::getX() {
	return LOWORD(lParam_);
}

int MyEvent::getY() {
	return HIWORD(lParam_);
}

MyPoint MyEvent::getPos() {
	return MyPoint(LOWORD(lParam_), HIWORD(lParam_));
}
