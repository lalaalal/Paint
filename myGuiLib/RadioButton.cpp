#include "RadioButton.h"
#include "RadioButtonGroup.h"

const std::string RadioButton::CHECKED = "<V>";
const std::string RadioButton::NOT_CHECKED = "<  >";

RadioButton::RadioButton(int width, int height, std::string text)
	: CheckBox(width, height, text) { }

void RadioButton::onClick(MyEvent e) {
	RadioButtonGroup* radioButtonGroup = dynamic_cast<RadioButtonGroup*>(getParent());
	if (radioButtonGroup != nullptr) {
		radioButtonGroup->select(this);
	}
	Component::onClick(e);
}

std::string RadioButton::getCheckStateText() const {
	return checked_ ? CHECKED : NOT_CHECKED;
}