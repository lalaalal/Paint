#pragma once

#include "CheckBox.h"

class RadioButton : public CheckBox {
public:
	RadioButton(int width, int height, std::string text);

	void onClick(MyEvent e) override;

	static const std::string CHECKED;
	static const std::string NOT_CHECKED;
protected:
	std::string getCheckStateText() const override;

};
