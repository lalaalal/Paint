#include "CreateFigureCommand.h"
#include "PaintFrame.h"

CreateFigureCommand::CreateFigureCommand(MyPoint start, MyPoint end, PaintFrame* frame)
	: start_(start), end_(end), frame_(frame) { }

CreateFigureCommand::~CreateFigureCommand() {
	if (figure_ != nullptr) {
		delete figure_;
	}
}

void CreateFigureCommand::execute() {
	figure_ = Figure::createFigure(start_, end_, frame_->getFigureType());
	frame_->addFigure(figure_);
}

void CreateFigureCommand::undo() {
	if (figure_ != nullptr) {
		frame_->removeFigure(figure_);
	}
}

void CreateFigureCommand::redo() {
	if (figure_ != nullptr) {
		frame_->addFigure(figure_);
	}
}