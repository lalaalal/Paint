#pragma once

#include "Menu.h"

class SubMenu : public Menu {
public:
	SubMenu(MyPoint at, int width, int height, std::string text);
	SubMenu(int width, int height, std::string text);

	void onClick(MyEvent e) override;
};
