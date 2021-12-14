#include <iostream>

#include "PaintFrame.h"
#include "box.h"
#include "figure.h"
#include "button.h"
#include "PaintOnClickListeners.h"
#include "Label.h"
#include "MenuBar.h"
#include "Menu.h"
#include "Command.h"
#include "CommandManager.h"
#include "PaintButtons.h"
#include "SubMenu.h"

PaintFrame::PaintFrame(std::wstring title, int width, int height)
	: Frame(title, width, height), type_(Figure::Type::None), commandManager_(new CommandManager()) { }

PaintFrame::~PaintFrame() {
	/*while (!figures_.empty()) {
		Figure* figure = figures_.front();
		delete figure;
		figures_.pop_front();
	}*/
	delete commandManager_;
}

void PaintFrame::initialize() {
	Frame::initialize();

	Button* rectangleButton = new Button({ 0, 0 }, 90, Component::WRAP_CONTENT, "Rectangle", true);
	Button* ellipseButton = new Button({ 0, 0 }, 90, Component::WRAP_CONTENT, "Ellipse", true);
	Label* figureLabel = new Label({ 0, 0 }, 90, Component::WRAP_CONTENT, "None", true);
	rectangleButton->setOnClickListener(new FigureButtonListener(this, figureLabel, Figure::Type::RectangleType));
	ellipseButton->setOnClickListener(new FigureButtonListener(this, figureLabel, Figure::Type::EllipseType));

	UndoButton* undoButton = new UndoButton({ 0, 0 }, 90, Component::WRAP_CONTENT, commandManager_);
	RedoButton* redoButton = new RedoButton({ 0, 0 }, 90, Component::WRAP_CONTENT, commandManager_);
	undoButton->setOnClickListener(new UndoButtonListener(commandManager_));
	redoButton->setOnClickListener(new RedoButtonListener(commandManager_));
	commandManager_->addObserver(undoButton);
	commandManager_->addObserver(redoButton);

	Menu* tools = new Menu({ 0, 0 }, 90, Component::WRAP_CONTENT, "Tools");
	SubMenu* figureMenu = new SubMenu({ 0, 0 }, 90, Component::WRAP_CONTENT, "Figure");
	tools->addComponent(figureMenu);
	figureMenu->addComponent(rectangleButton);
	figureMenu->addComponent(ellipseButton);

	menuBar_ = new MenuBar(hWnd_);
	menuBar_->setPadding(0);
	menuBar_->setBorder(true);
	menuBar_->addChild(tools);
	menuBar_->addChild(figureLabel);
	menuBar_->addChild(undoButton);
	menuBar_->addChild(redoButton);

	addComponent(menuBar_);
}

void PaintFrame::eventHandler(MyEvent e) {
	Frame::eventHandler(e);

	// �̺�Ʈ�� ������ �ľ��ؼ� �簢�� �׸��⸦ ���⼭ ���ش�.
	if (e.isLButtonDown() || e.isRButtonDown()) {
		start_ = e.getPos();
	}
	else if (e.isLButtonUp() || e.isLButtonUp()) {
		if (!menuBar_->isInComponent(e.getPos())) {
			Command* command = Command::createCommand(start_, e, this);
			commandManager_->execute(command);
		}
	}
	
}

void PaintFrame::repaint() {
	// �׷����� ��� ���� ���⿡.
	for (Figure* figure : figures_) {
		figure->paint(hDC_);
	}

	Frame::repaint();
}

void PaintFrame::addFigure(Figure* figure) {
	if (figure != nullptr) {
		figures_.push_back(figure);
	}
	
}

void PaintFrame::removeFigure(Figure* figure) {
	figures_.remove(figure);
}

void PaintFrame::setFigureType(Figure::Type type) {
	type_ = type;
}

Figure::Type PaintFrame::getFigureType() const {
	return type_;
}

std::list<Figure*> PaintFrame::findFigures(MyPoint start, MyPoint end) const {
	std::list<Figure*> figures;
	if (start.x_ > end.x_) {
		std::swap(start.x_, end.x_);
	}
	if (start.y_ > end.y_) {
		std::swap(start.y_, end.y_);
	}

	for (Figure* figure : figures_) {
		if (figure->isInArea(start, end)) {
			figures.push_back(figure);
		}
	}

	return figures;
}

Figure* PaintFrame::findFigure(MyPoint at) const {
	for (auto i = figures_.rbegin(); i != figures_.rend(); ++i) {
		if ((*i)->isInFigure(at)) {
			return *i;
		}
	}

	return nullptr;
}

void PaintFrame::moveFigure(MyPoint from, MyPoint to) {
	Figure* figure = findFigure(from);
	if (figure != nullptr) {
		figure->move(to - from);
	}
}

Box* PaintFrame::groupFigures(MyPoint start, MyPoint end) {
	std::list<Figure*> figures = findFigures(start, end);

	for (Figure* figure : figures) {
		figures_.remove(figure);
	}

	Box* box = new Box(figures);
	figures_.push_back(box);

	return box;
}

void PaintFrame::unGroupFigures(Box* box) {
	for (Figure* figure : figures_) {
		if (figure == box) {
			figures_.remove(box);
			std::list<Figure*> children = box->getChildren();
			figures_.splice(figures_.end(), children);
			return;
		}
	}
}