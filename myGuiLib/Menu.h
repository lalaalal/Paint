#pragma once
 
#include "Button.h"

class PopUpList;

class Menu : public Button {
public:
	Menu(MyPoint at, int width, int height, std::string text);
	Menu(int width, int height, std::string text);
	virtual ~Menu();
	void openList();
	void closeList();
	void toggleList();
	void addComponent(Component* component);

	void setStartPoint(MyPoint at) override;
	void moveStartPoint(MyPoint delta) override;

	bool isInComponent(MyPoint at) const override;
	void onClick(MyEvent e) override;

protected:
	void paintContent(HDC hDC) override;
	PopUpList* menuList_ = nullptr;
	int interval_ = 5;

private:
	void setOnClickListener(OnClickListener* listener) override;
};

