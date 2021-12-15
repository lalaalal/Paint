#pragma once

#include <string>

#include "Misc.h"
#include <limits>

class Figure
{
public:
	enum class Type : unsigned char {
		None = 0, RectangleType, EllipseType
	};

	static const std::string TYPE_NAME[];

	static Figure* createFigure(MyPoint start, MyPoint end, Type type);

	Figure();
	Figure(MyPoint start, MyPoint end);
	virtual void paint(HDC hDC) = 0;
	bool isInArea(MyPoint start, MyPoint end) const;
	bool isInFigure(MyPoint at) const;
	virtual void move(MyPoint delta);

	virtual int getLeft() const;
	virtual int getTop() const;
	virtual int getRight() const;
	virtual int getBottom() const;
	int getIndex() const;
	void setIndex(int index);
protected:
	MyPoint start_;
	MyPoint end_;

	int index_;
};