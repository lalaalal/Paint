#include "MenuBar.h"

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