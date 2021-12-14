#include "Container.h"

Container::Container(MyPoint start, int width, int height, Orientation orientation)
	: Component(start, width, height, DEFAULT_PADDING, false), components_(), orientation_(orientation) { }

Container::Container(MyPoint start, int width, int height, bool paintBorder, Orientation orientation)
	: Component(start, width, height, DEFAULT_PADDING, paintBorder), components_(), orientation_(orientation) { }

Container::~Container() {
	while (!components_.empty()) {
		Component* component = components_.front();
		delete component;
		components_.pop_front();
	}
}

void Container::onClick(MyEvent e) {
	for (Component* component : components_) {
		if (component->isVisible() 
			&& component->isInComponent(e.getPos())) {
			component->onClick(e);
			return;
		}
	}
}

void Container::paintContent(HDC hDC) {
	Component::paintContent(hDC);
	for (Component* component : components_) {
		component->paint(hDC);
	}
}

int Container::getContentWidth() const {
	if (orientation_ == Orientation::HORIZONTAL) {
		return getTotalWidth();
	}
	else {
		return getMaxWidth();
	}
}

int Container::getContentHeight() const {
	if (orientation_ == Orientation::VERTICAL) {
		return getTotalHeight();
	}
	else {
		return getMaxHeight();
	}
}

int Container::getMaxWidth() const {
	int max = 0;
	for (Component* component : components_) {
		if (component->getWidth() > max) {
			max = component->getWidth();
		}
	}
	return max;
}

int Container::getMaxHeight() const {
	int max = 0;
	for (Component* component : components_) {
		if (component->getHeight() > max) {
			max = component->getHeight();
		}
	}
	return max;
}

int Container::getTotalWidth() const {
	int sum = 0;
	for (Component* component : components_) {
		sum += component->getWidth();
	}

	return sum;
}

int Container::getTotalHeight() const {
	int sum = 0;
	for (Component* component : components_) {
		sum += component->getHeight();
	}

	return sum;
}

void Container::setOrientation(Orientation orientation) {
	orientation_ = orientation;

}

void Container::setStartPoint(MyPoint at) {
	MyPoint delta = at - getStartPoint();
	moveStartPoint(delta);
}

void Container::moveStartPoint(MyPoint delta) {
	at_ += delta;
	for (Component* component : components_) {
		component->moveStartPoint(delta);
	}
}

bool Container::isInComponent(MyPoint at) const {
	for (Component* component : components_) {
		if (component->isInComponent(at)) {
			return true;
		}
	}
	return false;
}

void Container::addChild(Component* component) {
	if (component != nullptr) {
		component->setParent(this);

		if (orientation_ == Orientation::HORIZONTAL) {
			setChildHorizontal(component);
		}
		else {
			setChildVertical(component);
		}
		
		components_.push_back(component);
	}
}

void Container::setChildHorizontal(Component* component) {
	int start_x = at_.x_ + padding_;
	int start_y = at_.y_ + padding_;
	if (!components_.empty()) {
		auto last = components_.back();
		MyPoint startPoint = last->getStartPoint();
		start_x = startPoint.x_ + last->getWidth();
	}
	component->setStartPoint({ start_x, start_y });
}

void Container::setChildVertical(Component* component) {
	int start_x = at_.x_ + padding_;
	int start_y = at_.y_ + padding_;
	if (!components_.empty()) {
		auto last = components_.back();
		MyPoint startPoint = last->getStartPoint();
		start_y = startPoint.y_ + last->getHeight();
	}
	component->setStartPoint({ start_x, start_y });
}

void Container::setOnClickListener(OnClickListener* listener) {

}