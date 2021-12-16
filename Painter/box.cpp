#include <climits>

#include "box.h"

Box::Box() { }

Box::Box(std::list<Figure*> figures) : children_(figures) {
	resize();
}

Box::~Box() {

}

void Box::paintFigure(HDC hDC) {
	Rectangle(hDC, start_.x_, start_.y_, end_.x_, end_.y_);
	for (Figure* figure : children_) {
		figure->paint(hDC);
	}
}

void Box::move(MyPoint delta) {
	for (Figure* figure : children_) {
		figure->move(delta);
	}

	resize();
}

void Box::addChild(Figure* figure) {
	children_.push_back(figure);

	resize();
}

void Box::addChildren(std::list<Figure*> figures) {
	for (Figure* figure : figures) {
		children_.push_back(figure);
	}

	resize();
}

std::list<Figure*> Box::getChildren() const {
	return children_;
}

void Box::resize() {
	start_.x_ = getLeft();
	start_.y_ = getTop();
	end_.x_ = getRight();
	end_.y_ = getBottom();
}

int Box::getLeft() const {
	int min = INT_MAX;
	for (Figure* figure : children_) {
		if (min > figure->getLeft()) {
			min = figure->getLeft();
		}
	}
	return min;
}

int Box::getTop() const {
	int min = INT_MAX;
	for (Figure* figure : children_) {
		if (min > figure->getTop()) {
			min = figure->getTop();
		}
	}
	return min;
}

int Box::getRight() const {
	int max = 0;
	for (Figure* figure : children_) {
		if (max < figure->getRight()) {
			max = figure->getRight();
		}
	}
	return max;
}

int Box::getBottom() const {
	int max = 0;
	for (Figure* figure : children_) {
		if (max < figure->getBottom()) {
			max = figure->getBottom();
		}
	}
	return max;
}