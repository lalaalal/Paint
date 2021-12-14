#include "SelectionList.h"
#include "SelectionComponent.h"
#include "SelectionGroup.h"

const std::string SelectionList::DEFAULT_TEXT = "--SELECT--";

SelectionList::SelectionList(int width, int height, std::string text)
	: Button(width, height, text) {
	MyPoint groupPoint = { at_.x_, at_.y_ + getHeight() };
	group_ = new SelectionGroup(groupPoint);
}

void SelectionList::onClick(MyEvent e) {
	if (group_->isInComponent(e.getPos())) {
		group_->onClick(e);
		updateText();
	}
	else {
		group_->toggle();
	}	
}

bool SelectionList::isInComponent(MyPoint at) const {
	return Button::isInComponent(at)
		|| group_->isInComponent(at);
}

void SelectionList::paintContent(HDC hDC) {
	Button::paintContent(hDC);
	group_->paint(hDC);
}

void SelectionList::setStartPoint(MyPoint at) {
	MyPoint delta = at - at_;
	moveStartPoint(delta);
}

void SelectionList::moveStartPoint(MyPoint delta) {
	at_ += delta;
	group_->moveStartPoint(delta);
}

void SelectionList::addChild(SelectionComponent* component) {
	group_->addChild(component);
}

SelectionComponent* SelectionList::getSelected() const {
	return group_->getSelected();
}

void SelectionList::updateText() {
	SelectionComponent* selected = getSelected();
	if (selected != nullptr) {
		std::string text = selected->getText();
		setText(text);
	}
}