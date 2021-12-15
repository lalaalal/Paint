#pragma once

#include "Misc.h"

class FigureManager;

class Command {
public:
	virtual void execute() = 0;
	virtual void undo() = 0;
	virtual void redo();

	static Command* createCommand(MyPoint start, MyEvent e, FigureManager* figureManager);
};

