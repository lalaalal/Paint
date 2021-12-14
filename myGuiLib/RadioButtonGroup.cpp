#include "RadioButtonGroup.h"
#include "RadioButton.h"

RadioButtonGroup::RadioButtonGroup(MyPoint at, int width, int height, bool paintBorder)
	: Container(at, width, height, paintBorder, Orientation::VERTICAL) { }

RadioButtonGroup::RadioButtonGroup(int width, int height)
	: RadioButtonGroup({0, 0}, width, height) { }

void RadioButtonGroup::addChild(Component* component) {
	RadioButton* radioButton = dynamic_cast<RadioButton*>(component);
	if (radioButton != nullptr) {
		Container::addChild(component);
		radioButton->setChecked(false);
	}
}

void RadioButtonGroup::select(RadioButton* radioButton) {	
	for (Component* component : components_) {
		RadioButton* element = dynamic_cast<RadioButton*>(component);
		if (element != nullptr && element != radioButton) {
			element->setChecked(false);
		}		
	}
	radioButton->setChecked(true);
	selected_ = radioButton;
}

RadioButton* RadioButtonGroup::getSelected() const {
	return selected_;
}