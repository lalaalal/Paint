#pragma once

#include <list>

#include "Command.h"

class Figure;

class EraseFigureCommand : public Command {
public:
	EraseFigureCommand(Figure* figure, FigureManager* figureManager);
	void execute() override;
	void undo() override;
private:
	Figure* figure_;
	FigureManager* figureManager_;
	std::list<Figure*> backup_;
};
