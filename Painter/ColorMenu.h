#pragma once

#include "RadioButtonGroup.h"
#include "RadioButton.h"
#include "EditText.h"
#include "frame.h"
#include "Menu.h"

class ColorMenu : public Menu {
public:
	ColorMenu(Frame* frame);
	COLORREF getColor() const;

private:
	COLORREF getColor(RadioButton* selected) const;

	RadioButtonGroup* colorRadioGroup = nullptr;
	RadioButton* blackColorRadioButton = nullptr;
	RadioButton* blueColorRadioButton = nullptr;
	RadioButton* greenColorRadioButton = nullptr;
	RadioButton* redColorRadioButton = nullptr;
	RadioButton* customColorRadioButton = nullptr;
	EditText* customColorEditText = nullptr;
};
