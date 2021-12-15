#include "Menu.h"
#include "PopUpList.h"

Menu::Menu(MyPoint at, int width, int height, std::string text) 
	: Button(at, width, height, text) {
	MyPoint menuListPoint(at_.x_, at_.y_ + getHeight() + interval_);
	menuList_ = new PopUpList(menuListPoint);
	menuList_->closeList();
}

Menu::Menu(int width, int height, std::string text) 
	: Menu({ 0, 0 }, width, height, text) { }

Menu::~Menu() {
	delete menuList_;
}

void Menu::openList() {
	menuList_->openList();
}

void Menu::closeList() {
	menuList_->closeList();
}

void Menu::toggleList() {
	menuList_->toggleList();
}

void Menu::addComponent(Component* component) {
	if (component != nullptr) {
		menuList_->addChild(component);
	}
}

void Menu::paintContent(HDC hDC) {
	Button::paintContent(hDC);

	menuList_->paint(hDC);
}

void Menu::setStartPoint(MyPoint at) {
	MyPoint delta = at - getStartPoint();
	moveStartPoint(delta);
}

void Menu::moveStartPoint(MyPoint delta) {
	at_ += delta;
	menuList_->moveStartPoint(delta);
}

bool Menu::isInComponent(MyPoint at) const {
	return Button::isInComponent(at) 
		|| (menuList_->isVisible() && menuList_->isInComponent(at));
}

void Menu::onClick(MyEvent e) {
	if (menuList_->isInComponent(e.getPos())) {
		menuList_->onClick(e);
	}
	else {
		toggleList();
	}
}

void Menu::setOnClickListener(OnClickListener* listener) { }