#pragma once

#include <list>

#include "figure.h"

class FigureManager;

class Box : public Figure {
public:
	Box(std::list<Figure*> figures, const FigureManager* figureManager);
	virtual ~Box();
	void paintFigure(HDC hDC) override;
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
	const FigureManager* figureManager_;
	std::list<Figure*> children_;
};
