#include "CommandManager.h"
#include "Command.h"

CommandManager::~CommandManager() {
	clearStack(redoStack_);
	clearStack(undoStack_);

}

void CommandManager::execute(Command* command) {
	if (command != nullptr) {
		command->execute();

		undoStack_.push(command);
		clearStack(redoStack_);
	}
	notify();
}

void CommandManager::undo() {
	Command* command = undoStack_.top();
	if (command != nullptr) {
		undoStack_.pop();
		command->undo();
		redoStack_.push(command);
	}
	notify();
}

void CommandManager::redo() {
	Command* command = redoStack_.top();
	if (command != nullptr) {
		redoStack_.pop();
		command->redo();
		undoStack_.push(command);
	}
	notify();
}

bool CommandManager::undoable() const {
	return !undoStack_.empty();
}

bool CommandManager::redoable() const {
	return !redoStack_.empty();
}

void CommandManager::clearStack(std::stack<Command*>& stack) {
	while (!stack.empty()) {
		Command* command = stack.top();
		stack.pop();

		delete command;
	}
}
