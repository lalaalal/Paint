#pragma once

#include "Command.h"

class Box;

class GroupFiguresCommand : public Command {
public:
	GroupFiguresCommand(MyPoint start, MyPoint end, PaintFrame* frame);
	void execute() override;
	void undo() override;
private:
	MyPoint start_;
	MyPoint end_;
	PaintFrame* frame_;
	Box* group_ = nullptr;
};
