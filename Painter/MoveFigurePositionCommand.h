#pragma once

#include <list>

#include "Command.h"
#include "FigureManager.h"

class Figure;

class MoveFigurePositionCommand : public Command {
public:
	MoveFigurePositionCommand(Figure* figure, FigureManager* figureManager, FigureMovePosition position);
	void execute() override;
	void undo() override;

private:
	Figure* figure_;
	FigureManager* figureManager_;
	std::list<Figure*> backup_;
	const FigureMovePosition POSITION;
};
