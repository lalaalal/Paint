#include "Component.h"
#include "Container.h"
#include "OnClickListener.h"

Component::Component(MyPoint at, int width, int height, int padding, bool paintBorder)
	: at_(at), rawWidth_(width), rawHeight_(height), padding_(padding), paintBorder_(paintBorder) { }

Component::~Component() {

}

bool Component::isInComponent(MyPoint at) const {
	return isVisible()
		&& (at.x_ >= at_.x_ && at.x_ <= at_.x_ + getWidth())
		&& (at.y_ >= at_.y_ && at.y_ <= at_.y_ + getHeight());
}

void Component::onClick(MyEvent e) {
	if (listener_ != nullptr) {
		listener_->onClick(e);
	}
}

void Component::setOnClickListener(OnClickListener* listener) {
	if (listener != nullptr) {
		listener_ = listener;
	}
}

void Component::paint(HDC hDC) {
	if (isVisible_) {
		paintContent(hDC);
	}
}

void Component::paintContent(HDC hDC) {
	if (paintBorder_) {
		Rectangle(hDC, at_.x_, at_.y_, at_.x_ + getWidth(), at_.y_ + getHeight());
	}
}

void Component::setBorder(bool value) {
	paintBorder_ = value;
}

int Component::getPadding() const {
	return padding_;
}

void Component::setPadding(int padding) {
	if (padding >= 0) {
		padding_ = padding;
	}
}

bool Component::isVisible() const {
	return isVisible_;
}

void Component::setVisibility(bool value) {
	isVisible_ = value;
}

MyPoint Component::getStartPoint() const {
	return at_;
}

void Component::setStartPoint(MyPoint at) {
	at_ = at;
}

void Component::moveStartPoint(MyPoint delta) {
	at_ += delta;
}

int Component::getWidth() const {
	if (rawWidth_ == WRAP_CONTENT) {
		return getContentWidth() + padding_ * 2;
	}
	else if (rawWidth_ == MATCH_PARENT) {
		if (parent_ != nullptr) {
			return parent_->getWidth();
		}
	}
	return rawWidth_ + padding_ * 2;
}

int Component::getHeight() const {
	if (rawHeight_ == WRAP_CONTENT) {
		return getContentHeight() + padding_ * 2;
	}
	else if (rawHeight_ == MATCH_PARENT) {
		if (parent_ != nullptr) {
			return parent_->getWidth();
		}
	}
	return rawHeight_ + padding_ * 2;
}

void Component::setWidth(int width) {
	rawWidth_ = width;
}

void Component::setHeight(int height) {
	rawHeight_ = height;
}

Container* Component::getParent() const {
	return parent_;
}

void Component::setParent(Container* parent) {
	parent_ = parent;
}