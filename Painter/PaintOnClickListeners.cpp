#include "PaintOnClickListeners.h"
#include "PaintFrame.h"
#include "Label.h"
#include "Button.h"
#include "CommandManager.h"

FruitButtonListener::FruitButtonListener(Label* label, std::string text)
	: label_(label), text_(text) { }

void FruitButtonListener::onClick(MyEvent e) {
	if (label_ != nullptr) {
		label_->setText(text_);
	}
}

FigureButtonListener::FigureButtonListener(PaintFrame* frame, Figure::Type type)
	: frame_(frame), label_(nullptr), type_(type) { }

FigureButtonListener::FigureButtonListener(PaintFrame* frame, Label* label, Figure::Type type)
	: frame_(frame), label_(label), type_(type) { }

void FigureButtonListener::onClick(MyEvent e) {
	frame_->setFigureType(type_);

	if (label_ != nullptr) {
		std::string text = Figure::TYPE_NAME[(unsigned char)type_];
		label_->setText(text);
	}
}

UndoButtonListener::UndoButtonListener(CommandManager* commandManager)
	: commandManager_(commandManager) { }

void UndoButtonListener::onClick(MyEvent e) {
	if (commandManager_->undoable()) {
		commandManager_->undo();
	}
}

RedoButtonListener::RedoButtonListener(CommandManager* commandManager)
	: commandManager_(commandManager) { }

void RedoButtonListener::onClick(MyEvent e) {
	if (commandManager_->redoable()) {
		commandManager_->redo();
	}
}