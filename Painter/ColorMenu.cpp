#include "ColorMenu.h"
#include <iostream>

ColorMenu::ColorMenu(Frame* frame) 
	: Menu(90, Component::WRAP_CONTENT, "Color") {
	colorRadioGroup = new RadioButtonGroup(Component::WRAP_CONTENT, Component::WRAP_CONTENT);
	blackColorRadioButton = new RadioButton(110, Component::WRAP_CONTENT, "Black");
	blueColorRadioButton = new RadioButton(110, Component::WRAP_CONTENT, "Blue");
	greenColorRadioButton = new RadioButton(110, Component::WRAP_CONTENT, "Green");
	redColorRadioButton = new RadioButton(110, Component::WRAP_CONTENT, "Red");
	customColorRadioButton = new RadioButton(110, Component::WRAP_CONTENT, "Custom");
	customColorEditText = new EditText(110, Component::WRAP_CONTENT, frame);

	colorRadioGroup->addChild(blackColorRadioButton);
	colorRadioGroup->addChild(blueColorRadioButton);
	colorRadioGroup->addChild(greenColorRadioButton);
	colorRadioGroup->addChild(redColorRadioButton);
	colorRadioGroup->addChild(customColorRadioButton);
	colorRadioGroup->select(blackColorRadioButton);
	addComponent(colorRadioGroup);
	addComponent(customColorEditText);
}

COLORREF ColorMenu::getColor() const {
	RadioButton* selected = colorRadioGroup->getSelected();

	if (selected == customColorRadioButton) {
		std::string hexColorString = customColorEditText->getText();
		int r, g, b;
		if (sscanf_s(hexColorString.c_str(), "%02x%02x%02x", &r, &g, &b) != 3) {
			return RGB(0, 0, 0);
		}
		return RGB(r, g, b);
	}
	return getColor(selected);
}

COLORREF ColorMenu::getColor(RadioButton* selected) const {
	if (selected == blueColorRadioButton) {
		return RGB(0, 0, 255);
	}
	else if (selected == greenColorRadioButton) {
		return RGB(0, 255, 0);
	}
	else if (selected == redColorRadioButton) {
		return RGB(255, 0, 0);
	}
	return RGB(0, 0, 0);
}
