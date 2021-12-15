#pragma once

#include "Misc.h"
#include "OnClickListener.h"
#include "figure.h"

#include "FigureManager.h"

class Label;
class CommandManager;
class Button;

class FigureButtonListener : public OnClickListener {
public:
	FigureButtonListener(FigureManager* figureManager, Figure::Type type);
	FigureButtonListener(FigureManager* figureManager, Label* label, Figure::Type type);
	void onClick(MyEvent e) override;

private:
	FigureManager* figureManager_;
	Label* label_;
	const Figure::Type TYPE;
};

class UndoButtonListener : public OnClickListener {
public:
	UndoButtonListener(CommandManager* commandManager);
	void onClick(MyEvent e) override;

	static const std::string UNDO_TEXT;
	static const std::string UNDOABLE_TEXT;
private:
	CommandManager* commandManager_;
};

class RedoButtonListener : public OnClickListener {
public:
	RedoButtonListener(CommandManager* commandManager);
	void onClick(MyEvent e) override;

	static const std::string REDO_TEXT;
	static const std::string REDOABLE_TEXT;
private:
	CommandManager* commandManager_;
};

class SetToolButtonListener : public OnClickListener {
public:
	SetToolButtonListener(FigureManager* figureManager, PaintTool tool);
	void onClick(MyEvent e) override;

private:
	FigureManager* figureManager_;
	const PaintTool TOOL;
};

class MovePositionButtonListener : public OnClickListener {
public:
	MovePositionButtonListener(FigureManager* figureManager, FigureMovePosition position);
	void onClick(MyEvent e) override;

private:
	FigureManager* figureManager_;
	const FigureMovePosition POSITION;
};