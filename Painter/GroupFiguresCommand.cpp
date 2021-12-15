#include "GroupFiguresCommand.h"
#include "FigureManager.h"

GroupFiguresCommand::GroupFiguresCommand(std::list<Figure*> figures, FigureManager* figureManager)
	: figures_(figures), figureManager_(figureManager) { }

void GroupFiguresCommand::execute() {
	backup_ = figureManager_->getFigures();
	figureManager_->groupFigures(figures_);
}

void GroupFiguresCommand::undo() {
	figureManager_->setFigures(backup_);
}