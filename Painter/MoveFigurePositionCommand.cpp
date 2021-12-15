#include "MoveFigurePositionCommand.h"
#include "FigureManager.h"

MoveFigurePositionCommand::MoveFigurePositionCommand(Figure* figure, FigureManager* figureManager, FigureMovePosition position)
	: figure_(figure), figureManager_(figureManager), POSITION(position) { }

void MoveFigurePositionCommand::execute() {
	backup_ = figureManager_->getFigures();
	if (POSITION == FigureMovePosition::Front) {
		figureManager_->moveFigureFront(figure_);
	}
	else {
		figureManager_->moveFigureBack(figure_);
	}
}

void MoveFigurePositionCommand::undo() {
	figureManager_->setFigures(backup_);
}