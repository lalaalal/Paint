#pragma once
#include "Windows.h"


class MyPoint {
public:
	int x_, y_;
	MyPoint(int x, int y);
	MyPoint();

	double Abs() const;
	MyPoint operator-() const;
	MyPoint operator+(const MyPoint& rhs) const;
	MyPoint operator-(const MyPoint& rhs) const;
	const MyPoint& operator+=(const MyPoint& rhs);
	const MyPoint& operator-=(const MyPoint& rhs);
	bool operator==(const MyPoint& rhs) const;
	bool operator!=(const MyPoint& rhs) const;
};

class MyEvent {
private:
	UINT msg_;
	WPARAM wParam_;
	LPARAM lParam_;
public:
	MyEvent(UINT msg, WPARAM wParam, LPARAM lParam);
	bool isLButtonDown();
	bool isLButtonUp();
	bool isRButtonDown();
	bool isRButtonUp();
	bool isCtrlKeyDown();
	bool isShiftKeyDown();
	int getX();
	int getY();
	MyPoint getPos();
};