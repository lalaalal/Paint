#include "CheckBox.h"

const std::string CheckBox::CHECKED = "[V]";
const std::string CheckBox::NOT_CHECKED = "[  ]";
const std::string CheckBox::INTERVAL_BLANK = "  ";

CheckBox::CheckBox(MyPoint at, int width, int height, std::string text)
	: Component(at, width, height, DEFAULT_PADDING, true), text_(text) { }

CheckBox::CheckBox(int width, int height, std::string text)
	: CheckBox({0, 0}, width, height, text) { }

void CheckBox::paintContent(HDC hDC) {
	Component::paintContent(hDC);

	int left = at_.x_ + padding_;
	int top = at_.y_ + padding_;

	std::string output = getCheckStateText() + INTERVAL_BLANK + text_;

	TextOutA(hDC, left, top, output.c_str(), (int)output.length());
}

int CheckBox::getContentWidth() const {
	std::string output = getCheckStateText() + INTERVAL_BLANK + text_;
	return LETTER_WIDTH * (int)output.length();
}

int CheckBox::getContentHeight() const {
	return LETTER_HEIGHT;
}

void CheckBox::onClick(MyEvent e) {
	toggle();
	Component::onClick(e);
}

std::string CheckBox::getText() const {
	return text_;
}

void CheckBox::setText(std::string text) {
	text_ = text;
}

bool CheckBox::isChecked() const {
	return checked_;
}

void CheckBox::setChecked(bool value) {
	checked_ = value;
}

void CheckBox::toggle() {
	checked_ = !checked_;
}

std::string CheckBox::getCheckStateText() const {
	return checked_ ? CHECKED : NOT_CHECKED;
}
