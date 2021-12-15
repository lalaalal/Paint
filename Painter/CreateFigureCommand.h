#pragma once

#include "Misc.h"
#include "Command.h"

class PaintFrame;
class Figure;

class CreateFigureCommand : public Command {
public:
	CreateFigureCommand(MyPoint start, MyPoint end, FigureManager* figureManager);
	~CreateFigureCommand();
	void execute() override;
	void undo() override;
	void redo() override;

private:
	MyPoint start_;
	MyPoint end_;
	FigureManager* figureManager_;
	Figure* figure_ = nullptr;
};

