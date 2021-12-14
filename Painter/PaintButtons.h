#pragma once

#include "Misc.h"
#include "button.h"
#include "Observer.h"

class CommandManager;

class UndoButton : public Button, public Observer {
public:
	UndoButton(int width, int height, CommandManager* commandManager);
	void update() override;

	static const std::string UNDO_TEXT;
	static const std::string UNDOABLE_TEXT;
private:
	CommandManager* commandManager_;
};

class RedoButton : public Button, public Observer {
public:
	RedoButton(int width, int height, CommandManager* commandManager);
	void update() override;

	static const std::string REDO_TEXT;
	static const std::string REDOABLE_TEXT;
private:
	CommandManager* commandManager_;
};

