#include "PaintButtons.h"
#include "CommandManager.h"

const std::string UndoButton::UNDO_TEXT = "undo";
const std::string UndoButton::UNDOABLE_TEXT = "undo*";

UndoButton::UndoButton(MyPoint at, int width, int height, CommandManager* commandManager)
	: Button(at, width, height, UNDO_TEXT), commandManager_(commandManager) { }

void UndoButton::update() {
	if (commandManager_->undoable()) {
		setText(UNDOABLE_TEXT);
	}
	else {
		setText(UNDO_TEXT);
	}
}

const std::string RedoButton::REDO_TEXT = "redo";
const std::string RedoButton::REDOABLE_TEXT = "redo*";

RedoButton::RedoButton(MyPoint at, int width, int height, CommandManager* commandManager)
	: Button(at, width, height, REDO_TEXT), commandManager_(commandManager) { }

void RedoButton::update() {
	if (commandManager_->redoable()) {
		setText(REDOABLE_TEXT);
	}
	else {
		setText(REDO_TEXT);
	}
}