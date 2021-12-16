#pragma once

#include <list>

#include "Misc.h"
#include "figure.h"
#include "SpinButton.h"

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
		Figure::Type figureType_ = Figure::Type::RectangleType;
		COLORREF color_ = RGB(0, 0, 0);
		bool boxBorder_ = true;
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

	void setColorMenu(const ColorMenu* colorMenu);
	COLORREF getSelectedColor() const;

	void setErrorRangeSpinButton(const SpinButton* errorRangeSpinButton);
	int getErrorRange() const;

	static const int DEFAULT_ERROR_RANGE = 10;
private:
	std::list<Figure*> figures_;
	Preference preference_;
	const ColorMenu* colorMenu_ = nullptr;
	const SpinButton* errorRangeSpinButton_ = nullptr;
};

typedef FigureManager::Preference::Tool PaintTool;
typedef FigureManager::Preference::Position FigureMovePosition;