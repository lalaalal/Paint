#pragma once

#include <list>

#include "Command.h"

class Box;

class GroupFiguresCommand : public Command {
public:
	GroupFiguresCommand(MyPoint start, MyPoint end, FigureManager* figureManager);
	void execute() override;
	void undo() override;
private:
	MyPoint start_;
	MyPoint end_;
	FigureManager* figureManager_;
	Box* group_ = nullptr;

};
