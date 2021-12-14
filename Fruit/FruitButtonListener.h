#pragma once

#include <string>

#include "OnClickListener.h"

class Label;

class FruitButtonListener : public OnClickListener {
public:
	FruitButtonListener(Label* label, std::string text);
	void onClick(MyEvent e) override;
private:
	Label* label_;
	std::string text_;
};
