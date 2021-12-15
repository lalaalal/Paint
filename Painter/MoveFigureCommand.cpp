#include "MoveFigureCommand.h"
#include "FigureManager.h"

MoveFigureCommand::MoveFigureCommand(Figure* figure, MyPoint delta, FigureManager* figureManager)
	: figure_(figure), delta_(delta), figureManager_(figureManager) { }

void MoveFigureCommand::execute() {
	figureManager_->moveFigure(figure_, delta_);
}

void MoveFigureCommand::undo() {
	figureManager_->moveFigure(figure_, -delta_);
}