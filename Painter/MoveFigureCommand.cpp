#include "MoveFigureCommand.h"
#include "FigureManager.h"

MoveFigureCommand::MoveFigureCommand(MyPoint from, MyPoint to, FigureManager* figureManager)
	: from_(from), to_(to), figureManager_(figureManager) { }

void MoveFigureCommand::execute() {
	figureManager_->moveFigure(from_, to_);
}

void MoveFigureCommand::undo() {
	figureManager_->moveFigure(to_, from_);
}