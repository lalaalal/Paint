#pragma once

#include "Button.h"

class SelectionComponent : public Button {
public:
	SelectionComponent(int width, int height, std::string text);

	void onClick(MyEvent e) override;
private:
	Component* selected_ = nullptr;
};
