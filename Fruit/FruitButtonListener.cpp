#include "FruitButtonListener.h"
#include "Label.h"

FruitButtonListener::FruitButtonListener(Label* label, std::string text)
	: label_(label), text_(text) { }

void FruitButtonListener::onClick(MyEvent e) {
	if (label_ != nullptr) {
		label_->setText(text_);
	}
}