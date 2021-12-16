#pragma once

#include <list>

#include "Command.h"

class Box;
class FigureManager;
class Figure;

class UnGroupFiguresCommand : public Command {
public:
	UnGroupFiguresCommand(Box* box, FigureManager* figureManager);
	void execute() override;
	void undo() override;

private:
	Box* box_;
	FigureManager* figureManager_;
	std::list<Figure*> backup_;
};
