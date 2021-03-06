#pragma once

#include "Command.h"

class Figure;

class MoveFigureCommand : public Command {
public:
	MoveFigureCommand(Figure* figure, MyPoint delta, FigureManager* figureManager);
	void execute() override;
	void undo() override;

private:
	Figure* figure_;
	MyPoint delta_;
	FigureManager* figureManager_;
};
