#include "PopUpList.h"
#include "SubMenu.h"

PopUpList::PopUpList(MyPoint at)
	: Container(at, WRAP_CONTENT, WRAP_CONTENT, true, Orientation::VERTICAL) {

}

void PopUpList::closeList() {
	setVisibility(false);

	closeSubMenu();
}

void PopUpList::closeSubMenu() {
	for (Component* component : components_) {
		SubMenu* subMenu = dynamic_cast<SubMenu*>(component);
		if (subMenu != nullptr) {
			subMenu->closeList();
		}
	}
}

void PopUpList::closeOtherSubMenu(SubMenu* target) {
	for (Component* component : components_) {
		SubMenu* subMenu = dynamic_cast<SubMenu*>(component);
		if (subMenu != nullptr && target != subMenu) {
			subMenu->closeList();
		}
	}
}

void PopUpList::openList() {
	setVisibility(true);
}

void PopUpList::toggleList() {
	if (isVisible()) {
		closeList();
	}
	else {
		openList();
	}
}