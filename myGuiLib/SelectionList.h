#pragma once

#include "Button.h"

class SelectionGroup;
class SelectionComponent;

class SelectionList : public Button {
public:
	SelectionList(int width, int height, std::string text = DEFAULT_TEXT);

	void onClick(MyEvent e) override;
	bool isInComponent(MyPoint at) const override;
	void paintContent(HDC hDC) override;

	void setStartPoint(MyPoint at) override;
	void moveStartPoint(MyPoint delta) override;

	void addChild(SelectionComponent* component);
	SelectionComponent* getSelected() const;

	static const std::string DEFAULT_TEXT;

private:
	void updateText();
	SelectionGroup* group_ = nullptr;
};
