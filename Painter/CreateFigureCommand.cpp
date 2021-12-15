#include "CreateFigureCommand.h"
#include "FigureManager.h"

CreateFigureCommand::CreateFigureCommand(MyPoint start, MyPoint end, FigureManager* figureManager)
	: start_(start), end_(end), figureManager_(figureManager) { }

CreateFigureCommand::~CreateFigureCommand() {
	if (figure_ != nullptr) {
		delete figure_;
	}
}

void CreateFigureCommand::execute() {
	figure_ = Figure::createFigure(start_, end_, figureManager_->getFigureType());
	figureManager_->addFigure(figure_);
}

void CreateFigureCommand::undo() {
	if (figure_ != nullptr) {
		figureManager_->removeFigure(figure_);
	}
}

void CreateFigureCommand::redo() {
	if (figure_ != nullptr) {
		figureManager_->addFigure(figure_);
	}
}