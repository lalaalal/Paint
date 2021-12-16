#pragma once

#include "Container.h"

class Menu;

class MenuBar : public Container {
public:
	MenuBar(HWND hWND);

	int getWidth() const override;

	void onClick(MyEvent e) override;

private:
	HWND hWND_;
};

