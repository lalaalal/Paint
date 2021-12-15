#pragma once

#include "Misc.h"
#include "OnClickListener.h"
#include "figure.h"

class FigureManager;
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
	Figure::Type type_;
};

class FruitButtonListener : public OnClickListener {
public:
	FruitButtonListener(Label* label, std::string text);
	void onClick(MyEvent e) override;
private:
	Label* label_;
	std::string text_;
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