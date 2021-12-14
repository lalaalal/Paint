#include "SelectionComponent.h"
#include "PopUpList.h"
#include "SelectionGroup.h"

SelectionComponent::SelectionComponent(int width, int height, std::string text)
	: Button(width, height, text) { }

void SelectionComponent::onClick(MyEvent e) {
	SelectionGroup* selectionGroup = dynamic_cast<SelectionGroup*>(getParent());
	if (selectionGroup != nullptr) {
		selectionGroup->select(this);
	}
}
