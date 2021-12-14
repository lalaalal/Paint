#pragma once

#include "Container.h"

class SubMenu;

class PopUpList : public Container {
public:
	PopUpList(MyPoint at);

	void closeList();
	void closeSubMenu();
	void closeOtherSubMenu(SubMenu* target);
	void openList();
	void toggleList();
};

