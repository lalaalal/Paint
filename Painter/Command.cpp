#include "Command.h"
#include "CreateFigureCommand.h"
#include "GroupFiguresCommand.h"
#include "MoveFigureCommand.h"
#include "FigureManager.h"

Command* Command::createCommand(MyPoint start, MyEvent e, FigureManager* figureManager) {
	MyPoint end = e.getPos();

	if (start == end) {
		return nullptr;
	}

	if (e.isLButtonUp() && e.isCtrlKeyDown()) {
		return new MoveFigureCommand(start, end, figureManager);
	}
	else if (e.isLButtonUp() && e.isShiftKeyDown()) {
		return new GroupFiguresCommand(start, end, figureManager);
	}
	else if (e.isLButtonUp() && figureManager->getFigureType() != Figure::Type::None) {
		return new CreateFigureCommand(start, end, figureManager);
	}
	return nullptr;
}

void Command::redo() {
	execute();
}