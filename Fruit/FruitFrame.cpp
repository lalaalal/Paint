#include "FruitFrame.h"
#include "button.h"
#include "FruitButtonListener.h"
#include "Misc.h"
#include "Label.h"

FruitFrame::FruitFrame(std::wstring title, int width, int height)
	: Frame(title, width, height) { }

void FruitFrame::initialize() {
	Button* appleButton = new Button(MyPoint(10, 10), MyPoint(100, 45), "Apple");
	Button* bananaButton = new Button(MyPoint(110, 10), MyPoint(200, 45), "Banana");
	Label* fruitLabel = new Label(MyPoint(210, 10), MyPoint(300, 45), "None", 10, false);
	appleButton->setOnClickListener(new FruitButtonListener(fruitLabel, "Apple"));
	bananaButton->setOnClickListener(new FruitButtonListener(fruitLabel, "Banana"));

	addComponent(appleButton);
	addComponent(bananaButton);
	addComponent(fruitLabel);
}