#pragma once

#include <string>

#include "Misc.h"

class Figure {
public:
	enum class Type : unsigned char {
		None = 0, RectangleType, EllipseType
	};

	static const std::string TYPE_NAME[];

	static Figure* createFigure(MyPoint start, MyPoint end, COLORREF color, Type type);

	Figure();
	Figure(MyPoint start, MyPoint end, COLORREF color = RGB(0, 0, 0));
	void paint(HDC hDC);
	bool isInArea(MyPoint start, MyPoint end) const;
	bool isInFigure(MyPoint at) const;
	virtual void move(MyPoint delta);

	virtual int getLeft() const;
	virtual int getTop() const;
	virtual int getRight() const;
	virtual int getBottom() const;

	MyPoint getStartPoint() const;
	
protected:
	virtual void paintFigure(HDC hDC) = 0;

	MyPoint start_;
	MyPoint end_;
	COLORREF color_;
};