#include "Command.h"
#include "CreateFigureCommand.h"
#include "GroupFiguresCommand.h"
#include "MoveFigureCommand.h"
#include "PaintFrame.h"

Command* Command::createCommand(MyPoint start, MyEvent e, PaintFrame* frame) {
	MyPoint end = e.getPos();

	if (start == end) {
		return nullptr;
	}

	if (e.isLButtonUp() && e.isCtrlKeyDown()) {
		return new MoveFigureCommand(start, end, frame);
	}
	else if (e.isLButtonUp() && e.isShiftKeyDown()) {
		return new GroupFiguresCommand(start, end, frame);
	}
	else if (e.isLButtonUp() && frame->getFigureType() != Figure::Type::None) {
		return new CreateFigureCommand(start, end, frame);
	}
	return nullptr;
}

void Command::redo() {
	execute();
}