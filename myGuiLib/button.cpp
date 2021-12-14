#include "Button.h"
#include "frame.h"
#include "OnClickListener.h"

Button::Button(MyPoint at, int width, int height, std::string text, bool paintBorder)
	: Component(at, width, height, DEFAULT_PADDING, paintBorder), text_(text) { }

Button::Button(int width, int height, std::string text)
	: Button({ 0, 0 }, width, height, text) { }

std::string Button::getText() const {
	return text_;
}

void Button::setText(std::string text) {
	text_ = text;
}

void Button::paintContent(HDC hDC) {
	Component::paintContent(hDC);
	TextOutA(hDC, at_.x_ + padding_, at_.y_ + padding_, text_.c_str(), (int)text_.length());
}

int Button::getContentWidth() const {
	return LETTER_WIDTH * (int)text_.length();
}

int Button::getContentHeight() const {
	return LETTER_HEIGHT;
}