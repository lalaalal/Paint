#pragma once

#include <stack>

#include "Subject.h"

class Command;

class CommandManager : public Subject {
public:
	~CommandManager();

	void execute(Command* command);
	void undo();
	void redo();
	
	bool undoable() const;
	bool redoable() const;
private:
	void clearStack(std::stack<Command*>& stack);

	std::stack<Command*> undoStack_;
	std::stack<Command*> redoStack_;
};

