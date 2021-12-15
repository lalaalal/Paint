#include "FigureManager.h"
#include "box.h"

void FigureManager::addFigure(Figure* figure) {
	if (figure != nullptr) {
		figures_.push_back(figure);
	}
}

void FigureManager::addFigures(const std::list<Figure*>& figures) {
	for (Figure* figure : figures) {
		addFigure(figure);
	}
}

void FigureManager::removeFigure(Figure* figure) {
	figures_.remove(figure);
}


FigureManager::Preference FigureManager::getPreference() const {
	return preference_;
}

FigureManager::Preference::Position FigureManager::getMovePosition() const {
	return preference_.position_;
}

FigureManager::Preference::Tool FigureManager::getTool() const {
	return preference_.tool_;
}

Figure::Type FigureManager::getFigureType() const {
	return preference_.figureType_;
}

void FigureManager::setPreference(Preference preference) {
	preference_ = preference;
}

void FigureManager::setMovePosition(Preference::Position position) {
	preference_.position_ = position;
}

void FigureManager::setTool(Preference::Tool tool) {
	preference_.tool_ = tool;
}

void FigureManager::setFigureType(Figure::Type type) {
	preference_.figureType_ = type;
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

void FigureManager::moveFigure(Figure* target, MyPoint delta) {
	if (target != nullptr) {
		target->move(delta);
	}
}

void FigureManager::moveFigureFront(Figure* target) {
	figures_.remove(target);
	figures_.push_back(target);
}

void FigureManager::moveFigureBack(Figure* target) {
	figures_.remove(target);
	figures_.push_front(target);
}

Box* FigureManager::groupFigures(const std::list<Figure*>& figures) {
	for (Figure* figure : figures) {
		figures_.remove(figure);
	}

	Box* box = new Box(figures);
	addFigure(box);

	return box;
}

void FigureManager::unGroupFigures(Box* box) {
	for (Figure* figure : figures_) {
		if (figure == box) {
			figures_.remove(box);
			std::list<Figure*> children = box->getChildren();
			figures_.splice(figures_.end(), children);
			return;
		}
	}
}

std::list<Figure*> FigureManager::getFigures() const {
	return figures_;
}

void FigureManager::setFigures(const std::list<Figure*>& figures) {
	figures_ = figures;
}
