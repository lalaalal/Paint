#include "SelectionGroup.h"
#include "SelectionComponent.h"

SelectionGroup::SelectionGroup(MyPoint at)
	: Container(at, WRAP_CONTENT, WRAP_CONTENT, Orientation::VERTICAL) {
	closeList();
	setPadding(0);
}

void SelectionGroup::openList() {
	setVisibility(true);
}

void SelectionGroup::closeList() {
	setVisibility(false);
}

void SelectionGroup::toggle() {
	isVisible() ? closeList() : openList();
}

void SelectionGroup::select(SelectionComponent* select) {
	for (Component* component : components_) {
		SelectionComponent* selectionComponent = dynamic_cast<SelectionComponent*>(component);
		if (selectionComponent != nullptr && selectionComponent == select) {
			selected_ = select;
			closeList();
			return;
		}
	}
}

SelectionComponent* SelectionGroup::getSelected() const {
	return selected_;
}