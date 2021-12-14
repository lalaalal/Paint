#include "Component.h"
#include "Container.h"
#include "OnClickListener.h"

Component::Component(MyPoint at, int width, int height, int padding, int margin, bool paintBorder)
	: at_(at), width_(width), height_(height), padding_(padding), margin_(margin), paintBorder_(paintBorder) { }

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

int Component::getMargin() const {
	return margin_;
}

void Component::setPadding(int padding) {
	if (padding >= 0) {
		padding_ = padding;
	}
}

void Component::setMargin(int margin) {
	if (margin >= 0) {
		margin_ = margin;
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
	if (width_ == WRAP_CONTENT) {
		return getContentWidth() + padding_ * 2;
	}
	else if (width_ == MATCH_PARENT) {
		if (parent_ != nullptr) {
			return parent_->getWidth();
		}
	}
	return width_ + padding_ * 2;
}

int Component::getHeight() const {
	if (height_ == WRAP_CONTENT) {
		return getContentHeight() + padding_ * 2;
	}
	else if (height_ == MATCH_PARENT) {
		if (parent_ != nullptr) {
			return parent_->getWidth();
		}
	}
	return height_ + padding_ * 2;
}

void Component::setWidth(int width) {
	width_ = width;
}

void Component::setHeight(int height) {
	height_ = height;
}

Container* Component::getParent() const {
	return parent_;
}

void Component::setParent(Container* parent) {
	parent_ = parent;
}