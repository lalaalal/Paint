#pragma once

#include "frame.h"
#include "figure.h"

class MenuBar;
class Box;
class CommandManager;

class PaintFrame : public Frame {
public:
	PaintFrame(std::wstring title, int width, int height);
	virtual ~PaintFrame();

	void initialize() override;
	void eventHandler(MyEvent e) override;
	void repaint() override;

	void addFigure(Figure* figure);
	void removeFigure(Figure* figure);

	void setFigureType(Figure::Type type);
	Figure::Type getFigureType() const;
	std::list<Figure*> findFigures(MyPoint start, MyPoint end) const;
	Figure* findFigure(MyPoint at) const;
	void moveFigure(MyPoint from, MyPoint to);
	Box* groupFigures(MyPoint start, MyPoint end);
	void unGroupFigures(Box* box);
private:
	std::list<Figure*> figures_;

	// 응용을 위해 필요한 변수
	MyPoint start_;

	Figure::Type type_;

	MenuBar* menuBar_ = nullptr;
	CommandManager* commandManager_;
};
