#pragma once

#include "Command.h"

class MoveFigureCommand : public Command {
public:
	MoveFigureCommand(MyPoint from, MyPoint to, FigureManager* figureManager);
	void execute() override;
	void undo() override;

private:
	MyPoint from_;
	MyPoint to_;
	FigureManager* figureManager_;
};

