#include "GroupFiguresCommand.h"
#include "FigureManager.h"

GroupFiguresCommand::GroupFiguresCommand(MyPoint start, MyPoint end, FigureManager* figureManager)
	: start_(start), end_(end), figureManager_(figureManager) { }

void GroupFiguresCommand::execute() {
	group_ = figureManager_->groupFigures(start_, end_);
}

void GroupFiguresCommand::undo() {
	figureManager_->unGroupFigures(group_);
}