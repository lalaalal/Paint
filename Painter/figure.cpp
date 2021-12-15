#include <algorithm>

#include "figure.h"
#include "myellipse.h"
#include "myrectangle.h"

const std::string Figure::TYPE_NAME[] = {
		"None", "Rectangle", "Ellipse"
};

Figure* Figure::createFigure(MyPoint start, MyPoint end, Type type) {
	if (start == end) {
		return nullptr;
	}
	switch (type) {
	case Type::RectangleType:
		return new MyRectangle(start, end);
	case Type::EllipseType:
		return new MyEllipse(start, end);
	default:
		break;
	}
	return nullptr;
}

Figure::Figure()
	: start_(MyPoint(0, 0)), end_(MyPoint(0, 0)) { }

Figure::Figure(MyPoint start, MyPoint end) 
	: start_(start), end_(end) {
	if (start.x_ > end.x_) {
		std::swap(start_.x_, end_.x_);
	}
	if (start.y_ > end.y_) {
		std::swap(start_.y_, end_.y_);
	}
}

bool Figure::isInArea(MyPoint start, MyPoint end) const {
	return (start.x_ <= start_.x_ && start.y_ <= start_.y_)
		&& (end.x_ >= end_.x_ && end.y_ >= end_.y_);
}

bool Figure::isInFigure(MyPoint at) const {
	return (at.x_ >= start_.x_ && at.x_ <= end_.x_)
		&& (at.y_ >= start_.y_ && at.y_ <= end_.y_);
}

void Figure::move(MyPoint delta) {
	start_ += delta;
	end_ += delta;
}

int Figure::getLeft() const {
	return start_.x_;
}

int Figure::getTop() const {
	return start_.y_;
}

int Figure::getRight() const {
	return end_.x_;
}

int Figure::getBottom() const {
	return end_.y_;
}

MyPoint Figure::getStartPoint() const {
	return start_;
}