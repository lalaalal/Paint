#include <iostream>

#include "PaintFrame.h"
#include "Button.h"
#include "PaintOnClickListeners.h"
#include "Label.h"
#include "MenuBar.h"
#include "Menu.h"
#include "Command.h"
#include "CommandManager.h"
#include "PaintButtons.h"
#include "SubMenu.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "RadioButtonGroup.h"
#include "SelectionList.h"
#include "SelectionComponent.h"
#include "FigureManager.h"

PaintFrame::PaintFrame(std::wstring title, int width, int height)
	: Frame(title, width, height), commandManager_(new CommandManager()), figureManager_(new FigureManager()) { }

PaintFrame::~PaintFrame() {
	delete commandManager_;
}

void PaintFrame::initialize() {
	Frame::initialize();

	UndoButton* undoButton = new UndoButton(40, Component::WRAP_CONTENT, commandManager_);
	RedoButton* redoButton = new RedoButton(40, Component::WRAP_CONTENT, commandManager_);
	undoButton->setOnClickListener(new UndoButtonListener(commandManager_));
	redoButton->setOnClickListener(new RedoButtonListener(commandManager_));
	commandManager_->addObserver(undoButton);
	commandManager_->addObserver(redoButton);

	SelectionList* selectionList = new SelectionList(90, Component::WRAP_CONTENT, "Figure Type");
	SelectionComponent* rectangleButton = new SelectionComponent(90, Component::WRAP_CONTENT, "Rectangle");
	SelectionComponent* ellipseButton = new SelectionComponent(90, Component::WRAP_CONTENT, "Ellipse");
	rectangleButton->setOnClickListener(new FigureButtonListener(figureManager_, nullptr, Figure::Type::RectangleType));
	ellipseButton->setOnClickListener(new FigureButtonListener(figureManager_, nullptr, Figure::Type::EllipseType));
	selectionList->addChild(rectangleButton);
	selectionList->addChild(ellipseButton);

	menuBar_ = new MenuBar(hWnd_);
	menuBar_->setPadding(0);
	menuBar_->setBorder(true);	
	menuBar_->addChild(undoButton);
	menuBar_->addChild(redoButton);
	menuBar_->addChild(selectionList);

	addComponent(menuBar_);
}

void PaintFrame::eventHandler(MyEvent e) {
	Frame::eventHandler(e);

	if (e.isLButtonDown() || e.isRButtonDown()) {
		start_ = e.getPos();
	}
	else if (e.isLButtonUp() || e.isLButtonUp()) {
		if (!menuBar_->isInComponent(e.getPos())) {
			Command* command = Command::createCommand(start_, e, figureManager_);
			commandManager_->execute(command);
		}
	}
	
}

void PaintFrame::repaint() {
	for (Figure* figure : figureManager_->getFigures()) {
		figure->paint(hDC_);
	}

	Frame::repaint();
}
