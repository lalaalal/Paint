#include "Command.h"
#include "CreateFigureCommand.h"
#include "GroupFiguresCommand.h"
#include "MoveFigureCommand.h"
#include "MoveFigurePositionCommand.h"
#include "UnGroupFiguresCommand.h"
#include "FigureManager.h"
#include "EraseFigureCommand.h"
#include "box.h"

Command* Command::createCommand(MyPoint start, MyEvent e, FigureManager* figureManager) {
	FigureManager::Preference preference = figureManager->getPreference();
	MyPoint end = e.getPos();
	MyPoint delta = end - start;
	int errorRange = figureManager->getErrorRange();

	if (delta.Abs() > errorRange
		&& e.isLButtonUp() && e.isCtrlKeyDown()) {
		Figure* figure = figureManager->findFigure(start);
		if (figure != nullptr) {
			return new MoveFigureCommand(figure, delta, figureManager);
		}
	}
	else if (e.isLButtonUp() && e.isShiftKeyDown()) {
		std::list<Figure*> figures = figureManager->findFigures(start, end);
		if (figures.size() != 0) {
			return new GroupFiguresCommand(figures, figureManager);
		}
	}

	switch (preference.tool_) {
	case PaintTool::MovePosition:
		
		if (delta.Abs() < errorRange) {
			Figure* figure = figureManager->findFigure(end);
			if (figure != nullptr) {
				return new MoveFigurePositionCommand(figure, figureManager, preference.position_);
			}
		}
		return nullptr;

	case PaintTool::Eraser:
		if (delta.Abs() < errorRange) {
			Figure* figure = figureManager->findFigure(end);
			if (figure != nullptr) {
				return new EraseFigureCommand(figure, figureManager);
			}
		}
		return nullptr;

	case PaintTool::Pen:
		if (delta.Abs() > errorRange && e.isLButtonUp()
			&& preference.figureType_ != Figure::Type::None) {
			return new CreateFigureCommand(start, end, figureManager);
		}
		return nullptr;
	case PaintTool::UnGroup:
		if (delta.Abs() < errorRange && e.isLButtonUp()) {
			Figure* figure = figureManager->findFigure(start);
			Box* box = dynamic_cast<Box*>(figure);
			if (box != nullptr) {
				return new UnGroupFiguresCommand(box, figureManager);
			}
		}
	default:
		return nullptr;
	}

	return nullptr;
}

void Command::redo() {
	execute();
}