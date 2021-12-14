#include "Label.h"

Label::Label(MyPoint at, int width, int height, std::string text, bool paintBorder)
	: Component(at, width, height, DEFAULT_PADDING, DEFAULT_MARGIN, paintBorder), text_(text) { }

void Label::setText(std::string text) {
	text_ = text;
}

std::string Label::getText() const {
	return text_;
}

void Label::paintContent(HDC hDC) {
	Component::paintContent(hDC);
	TextOutA(hDC, at_.x_ + padding_, at_.y_ + padding_, text_.c_str(), text_.length());
}

void Label::onClick(MyEvent e) { }

void Label::setOnClickListener(OnClickListener *listener) { }

int Label::getContentWidth() const {
	return LETTER_WIDTH * text_.length();
}

int Label::getContentHeight() const {
	return LETTER_HEIGHT;
}