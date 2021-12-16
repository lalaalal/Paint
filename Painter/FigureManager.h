#pragma once

#include <list>

#include "Misc.h"
#include "figure.h"

class Box;
class ColorMenu;

class FigureManager {
public:
	struct Preference {
	public:
		enum class Tool {
			Pen, Eraser, MovePosition, UnGroup
		};

		enum class Position {
			Front, Back
		};

		Tool tool_ = Tool::Pen;
		Position position_ = Position::Front;
		Figure::Type figureType_ = Figure::Type::None;
		COLORREF color_ = RGB(0, 0, 0);
	};

	void addFigure(Figure* figure);
	void addFigures(const std::list<Figure*>& figures);
	void removeFigure(Figure* figure);

	Preference getPreference() const;
	Preference::Position getMovePosition() const;
	Preference::Tool getTool() const;
	Figure::Type getFigureType() const;
	void setPreference(Preference preference);
	void setMovePosition(Preference::Position position);
	void setTool(Preference::Tool tool);
	void setFigureType(Figure::Type type);

	std::list<Figure*> findFigures(MyPoint start, MyPoint end) const;
	Figure* findFigure(MyPoint at) const;
	void moveFigure(Figure* target, MyPoint delta);
	void moveFigureFront(Figure* target);
	void moveFigureBack(Figure* target);
	Box* groupFigures(const std::list<Figure*>& figures);
	void unGroupFigures(Box* box);
	std::list<Figure*> getFigures() const;
	void setFigures(const std::list<Figure*>& figures);

	void setColorMenu(ColorMenu* colorMenu);
	COLORREF getSelectedColor() const;
private:
	std::list<Figure*> figures_;
	Preference preference_;
	ColorMenu* colorMenu_ = nullptr;
};

typedef FigureManager::Preference::Tool PaintTool;
typedef FigureManager::Preference::Position FigureMovePosition;