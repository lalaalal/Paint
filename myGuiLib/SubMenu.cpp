#include "SubMenu.h"
#include "PopUpList.h"

SubMenu::SubMenu(MyPoint at, int width, int height, std::string text)
	: Menu(at, width, height, text) {
	interval_ = 15;
	MyPoint menuListPoint(at_.x_ + getWidth() + interval_, at_.y_);
	menuList_->setStartPoint(menuListPoint);
}

void SubMenu::onClick(MyEvent e) {
	PopUpList* parent = dynamic_cast<PopUpList*>(getParent());
	if (parent != nullptr) {
		parent->closeOtherSubMenu(this);
	}

	Menu::onClick(e);
}