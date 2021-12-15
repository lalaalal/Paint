#pragma once

#include <list>

#include "Command.h"

class Figure;

class GroupFiguresCommand : public Command {
public:
	GroupFiguresCommand(std::list<Figure*> figures, FigureManager* figureManager);
	void execute() override;
	void undo() override;
private:
	std::list<Figure*> figures_;
	FigureManager* figureManager_;
	std::list<Figure*> backup_;
};
