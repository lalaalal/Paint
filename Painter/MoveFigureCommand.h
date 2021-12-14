#pragma once

#include "Command.h"

class MoveFigureCommand : public Command {
public:
	MoveFigureCommand(MyPoint from, MyPoint to, PaintFrame* frame);
	void execute() override;
	void undo() override;

private:
	MyPoint from_;
	MyPoint to_;
	PaintFrame* frame_;
};

