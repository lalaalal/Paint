#pragma once

#include "Container.h"

class RadioButton;

class RadioButtonGroup : public Container {
public:
	RadioButtonGroup(MyPoint at, int width, int height, bool paintBorder = true);
	RadioButtonGroup(int width, int height);

	void addChild(Component* component) override;
	void select(RadioButton* radioButton);
	RadioButton* getSelected() const;

private:
	RadioButton* selected_ = nullptr;
};

