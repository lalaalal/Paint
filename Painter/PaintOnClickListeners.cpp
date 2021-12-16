#include "PaintOnClickListeners.h"
#include "FigureManager.h"
#include "Label.h"
#include "Button.h"
#include "CommandManager.h"
#include "PaintFrame.h"

FigureButtonListener::FigureButtonListener(FigureManager* figureManager, Figure::Type type)
	: figureManager_(figureManager), label_(nullptr), TYPE(type) { }

FigureButtonListener::FigureButtonListener(FigureManager* figureManager, Label* label, Figure::Type type)
	: figureManager_(figureManager), label_(label), TYPE(type) { }

void FigureButtonListener::onClick(MyEvent e) {
	figureManager_->setFigureType(TYPE);

	if (label_ != nullptr) {
		std::string text = Figure::TYPE_NAME[(unsigned char)TYPE];
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

SetToolButtonListener::SetToolButtonListener(FigureManager* figureManager, PaintTool tool)
	: figureManager_(figureManager), TOOL(tool) { }

void SetToolButtonListener::onClick(MyEvent e) {
	figureManager_->setTool(TOOL);
}

MovePositionButtonListener::MovePositionButtonListener(FigureManager* figureManager, FigureMovePosition position)
	: figureManager_(figureManager), POSITION(position) { }

void MovePositionButtonListener::onClick(MyEvent e) {
	figureManager_->setMovePosition(POSITION);
}

GroupBorderCheckBoxListener::GroupBorderCheckBoxListener(FigureManager* figureManager, CheckBox* checkBox)
	: figureManager_(figureManager), checkBox_(checkBox) { }

void GroupBorderCheckBoxListener::onClick(MyEvent e) {
	FigureManager::Preference preference = figureManager_->getPreference();
	preference.boxBorder_ = checkBox_->isChecked();
	figureManager_->setPreference(preference);
}

SaveButtonListener::SaveButtonListener(PaintFrame* frame)
	: frame_(frame) { }

void SaveButtonListener::onClick(MyEvent e) {
	frame_->save();
}