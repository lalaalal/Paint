#include "UnGroupFiguresCommand.h"
#include "FigureManager.h"
#include "figure.h"

UnGroupFiguresCommand::UnGroupFiguresCommand(Box* box, FigureManager* figureManager)
	: box_(box), figureManager_(figureManager) { }

void UnGroupFiguresCommand::execute() {
	backup_ = figureManager_->getFigures();
	figureManager_->unGroupFigures(box_);
}

void UnGroupFiguresCommand::undo() {
	figureManager_->setFigures(backup_);
}