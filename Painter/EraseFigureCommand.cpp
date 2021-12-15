#include "EraseFigureCommand.h"
#include "FigureManager.h"

EraseFigureCommand::EraseFigureCommand(Figure* figure, FigureManager* figureManager)
	: figure_(figure), figureManager_(figureManager) { }

void EraseFigureCommand::execute() {
	backup_ = figureManager_->getFigures();
	figureManager_->removeFigure(figure_);
}

void EraseFigureCommand::undo() {
	figureManager_->setFigures(backup_);
}