#include "FigureManager.h"
#include "box.h"

void FigureManager::addFigure(Figure* figure) {
	if (figure != nullptr) {
		std::list<Figure*>::iterator i;
		for (i = figures_.begin(); i != figures_.end(); i++) {
			if ((*i)->getIndex() > figure->getIndex()) {
				break;
			}
		}
		figures_.insert(i, figure);
		if (figure->getIndex() == INT_MAX) {
			figure->setIndex((int)figures_.size());
		}
	}
}

void FigureManager::addFigures(std::list<Figure*> figures) {
	for (Figure* figure : figures) {
		addFigure(figure);
	}
}

void FigureManager::removeFigure(Figure* figure) {
	figures_.remove(figure);
}

void FigureManager::setFigureType(Figure::Type type) {
	type_ = type;
}

Figure::Type FigureManager::getFigureType() const {
	return type_;
}

std::list<Figure*> FigureManager::findFigures(MyPoint start, MyPoint end) const {
	std::list<Figure*> figures;
	if (start.x_ > end.x_) {
		std::swap(start.x_, end.x_);
	}
	if (start.y_ > end.y_) {
		std::swap(start.y_, end.y_);
	}

	for (Figure* figure : figures_) {
		if (figure->isInArea(start, end)) {
			figures.push_back(figure);
		}
	}

	return figures;
}

Figure* FigureManager::findFigure(MyPoint at) const {
	for (auto i = figures_.rbegin(); i != figures_.rend(); ++i) {
		if ((*i)->isInFigure(at)) {
			return *i;
		}
	}

	return nullptr;
}

void FigureManager::moveFigure(MyPoint from, MyPoint to) {
	Figure* figure = findFigure(from);
	if (figure != nullptr) {
		figure->move(to - from);
	}
}

Box* FigureManager::groupFigures(MyPoint start, MyPoint end) {
	std::list<Figure*> figures = findFigures(start, end);

	for (Figure* figure : figures) {
		figures_.remove(figure);
	}

	Box* box = new Box(figures);
	figures_.push_back(box);

	return box;
}

void FigureManager::unGroupFigures(Box* box) {
	for (Figure* figure : figures_) {
		if (figure == box) {
			figures_.remove(box);
			std::list<Figure*> children = box->getChildren();
			addFigures(box->getChildren());
			return;
		}
	}
}

std::list<Figure*> FigureManager::getFigures() const {
	return figures_;
}