#pragma once

#include <list>

#include "figure.h"

class Box;

class FigureManager {
public:
	void addFigure(Figure* figure);
	void addFigures(std::list<Figure*> figures);
	void removeFigure(Figure* figure);
	void setFigureType(Figure::Type type);
	Figure::Type getFigureType() const;
	std::list<Figure*> findFigures(MyPoint start, MyPoint end) const;
	Figure* findFigure(MyPoint at) const;
	void moveFigure(MyPoint from, MyPoint to);
	Box* groupFigures(MyPoint start, MyPoint end);
	void unGroupFigures(Box* box);
	std::list<Figure*> getFigures() const;
private:
	std::list<Figure*> figures_;
	Figure::Type type_ = Figure::Type::None;
};
