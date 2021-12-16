#include "MenuBar.h"
#include "Menu.h"

MenuBar::MenuBar(HWND hWND)
	: Container({ 0, 0 }, MATCH_PARENT, WRAP_CONTENT, Orientation::HORIZONTAL), hWND_(hWND) { }

int MenuBar::getWidth() const {
	RECT rect;
	if (GetWindowRect(hWND_, &rect))
	{
		int width = rect.right - rect.left;

		return width;
	}
	return 0;
}

void MenuBar::onClick(MyEvent e) {
	for (Component* component : components_) {
		Menu* menu = dynamic_cast<Menu*>(component);
		if (menu != nullptr && !menu->isInComponent(e.getPos())) {
			menu->closeList();
		}
		if (component->isInComponent(e.getPos())) {
			component->onClick(e);
		}
	}
}