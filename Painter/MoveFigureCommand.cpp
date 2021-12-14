#include "MoveFigureCommand.h"
#include "PaintFrame.h"

MoveFigureCommand::MoveFigureCommand(MyPoint from, MyPoint to, PaintFrame* frame)
	: from_(from), to_(to), frame_(frame) { }

void MoveFigureCommand::execute() {
	frame_->moveFigure(from_, to_);
}

void MoveFigureCommand::undo() {
	frame_->moveFigure(to_, from_);
}