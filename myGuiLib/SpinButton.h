#pragma once

#include "Component.h"
#include "OnClickListener.h"
#include "Button.h"

class Label;

class SpinButton : public Component {
public:
	SpinButton(int width, int height);
	virtual ~SpinButton();

	int getContentWidth() const override;
	int getContentHeight() const override;

	void setStartPoint(MyPoint at) override;
	void moveStartPoint(MyPoint delta) override;

	int getValue() const;
	void setValue(int value);
	void addValue(int value);

	bool isInComponent(MyPoint at) const override;
	void onClick(MyEvent e) override;

	static const int MIN_WIDTH = 50;
	
protected:
	void paintContent(HDC hDC) override;

private:
	int value_;
	Label* label_ = nullptr;
	Button* downButton_ = nullptr;
	Button* upButton_ = nullptr;

	class SpinButtonOnClickListener : public OnClickListener {
	public:
		SpinButtonOnClickListener(int adder, SpinButton* spinButton);
		void onClick(MyEvent e) override;
	private:
		int adder_;
		SpinButton* spinButton_;
	};
};

