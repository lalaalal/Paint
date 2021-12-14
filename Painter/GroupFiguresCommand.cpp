#include "GroupFiguresCommand.h"
#include "PaintFrame.h"
#include <list>

GroupFiguresCommand::GroupFiguresCommand(MyPoint start, MyPoint end, PaintFrame* frame)
	: start_(start), end_(end), frame_(frame) { }

void GroupFiguresCommand::execute() {
	group_ = frame_->groupFigures(start_, end_);
}

void GroupFiguresCommand::undo() {
	frame_->unGroupFigures(group_);
}