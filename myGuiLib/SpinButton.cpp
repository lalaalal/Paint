#include "SpinButton.h"
#include "Label.h"
#include "Button.h"


SpinButton::SpinButton(int width, int height)
	: Component({ 0, 0 }, width, height), value_(0) {
	width = (width < MIN_WIDTH ? MIN_WIDTH : width);
	label_ = new Label({ 0, 0 }, width, height, std::to_string(value_));

	downButton_ = new Button(WRAP_CONTENT, WRAP_CONTENT, "-");
	upButton_ = new Button(WRAP_CONTENT, WRAP_CONTENT, "+");

	int labelWidth = width - downButton_->getWidth() - upButton_->getWidth();
	label_->setWidth(labelWidth);
	downButton_->setStartPoint(at_ + MyPoint(labelWidth, 0));
	upButton_->setStartPoint(downButton_->getStartPoint() + MyPoint(downButton_->getWidth(), 0));

	downButton_->setOnClickListener(new SpinButtonOnClickListener(-1, this));
	upButton_->setOnClickListener(new SpinButtonOnClickListener(1, this));
}

SpinButton::~SpinButton() {
	delete label_;
	delete downButton_;
	delete upButton_;
}

int SpinButton::getContentWidth() const {
	return label_->getWidth() + downButton_->getWidth() + upButton_->getWidth();
}

int SpinButton::getContentHeight() const {
	return label_->getHeight();
}

void SpinButton::setStartPoint(MyPoint at) {
	moveStartPoint(at - at_);
}

void SpinButton::moveStartPoint(MyPoint delta) {
	at_ += delta;
	label_->moveStartPoint(delta);
	downButton_->moveStartPoint(delta);
	upButton_->moveStartPoint(delta);
}

int SpinButton::getValue() const {
	return value_;
}

void SpinButton::setValue(int value) {
	value_ = value;
	label_->setText(std::to_string(value_));
}

void SpinButton::addValue(int value) {
	value_ += value;
	label_->setText(std::to_string(value_));
}

bool SpinButton::isInComponent(MyPoint at) const {
	return downButton_->isInComponent(at)
		|| upButton_->isInComponent(at);
}

void SpinButton::onClick(MyEvent e) {
	MyPoint at = e.getPos();
	if (downButton_->isInComponent(at)) {
		downButton_->onClick(e);
	}
	else if (upButton_->isInComponent(at)) {
		upButton_->onClick(e);
	}

	Component::onClick(e);
}

void SpinButton::paintContent(HDC hDC) {
	label_->paint(hDC);
	downButton_->paint(hDC);
	upButton_->paint(hDC);
}


SpinButton::SpinButtonOnClickListener::SpinButtonOnClickListener(int adder, SpinButton* spinButton)
	: adder_(adder), spinButton_(spinButton) { }

void SpinButton::SpinButtonOnClickListener::onClick(MyEvent e) {
	spinButton_->addValue(adder_);
}