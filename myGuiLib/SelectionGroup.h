#pragma once

#include "Container.h"

class SelectionComponent;

class SelectionGroup : public Container {
public:
	SelectionGroup(MyPoint at);
	void openList();
	void closeList();
	void toggle();
	void select(SelectionComponent* select);
	SelectionComponent* getSelected() const;
private:
	SelectionComponent* selected_ = nullptr;
};

