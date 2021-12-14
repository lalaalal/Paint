#pragma once

#include "Misc.h"
#include "Command.h"

class PaintFrame;
class Figure;

class CreateFigureCommand : public Command {
public:
	CreateFigureCommand(MyPoint start, MyPoint end, PaintFrame* frame);
	~CreateFigureCommand();
	void execute() override;
	void undo() override;
	void redo() override;

private:
	MyPoint start_;
	MyPoint end_;
	PaintFrame* frame_;
	Figure* figure_ = nullptr;
};

