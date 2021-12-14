#pragma once

#include <list>

#include "figure.h"

class Box : public Figure {
public:
	Box();
	Box(std::list<Figure*> figures);
	virtual ~Box();
	void paint(HDC hDC) override;
	void move(MyPoint delta) override;
	void addChild(Figure* figure);
	void addChildren(std::list<Figure*> figures);
	std::list<Figure*> getChildren() const;
	void resize();

	int getLeft() const override;
	int getTop() const override;
	int getRight() const override;
	int getBottom() const override;

private:
	std::list<Figure*> children_;
};

