#include "EditText.h"
#include "frame.h"

EditText::EditText(int width, int height, Frame* frame)
	: Component({ 0, 0 }, width, height, DEFAULT_PADDING, true), frame_(frame), etWidth_(width), etHeight_(DEFAULT_ET_HEIGHT) {
	static int id = 1001;

	if (height < DEFAULT_ET_HEIGHT)
		height = DEFAULT_ET_HEIGHT;
	setPadding((height - DEFAULT_ET_HEIGHT) / 2);
	etWidth_ = width - padding_ * 2;
	editId_ = (HMENU)id++;
	hEdit_ = CreateWindow(L"edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER |
		ES_AUTOHSCROLL, at_.x_ + padding_, at_.y_ + padding_, etWidth_, etHeight_, frame->getHWND(), (HMENU)editId_, GetModuleHandle(NULL), NULL);

	frame->addHWND(hEdit_);
	ShowWindow(hEdit_, SW_HIDE);
}

EditText::~EditText() {
	frame_->removeHWND(hEdit_);
}

int EditText::getContentWidth() const {
	return etWidth_;
}

int EditText::getContentHeight() const {
	return etHeight_;
}

void EditText::paintContent(HDC hDC) {
	Component::paintContent(hDC);
	ShowWindow(hEdit_, SW_SHOW);
	MoveWindow(hEdit_, at_.x_ + padding_, at_.y_ + padding_, etWidth_, etHeight_, true);
}

std::string EditText::getText() const {
	char buf[128];
	GetWindowTextA(hEdit_, buf, 128);

	return buf;
}