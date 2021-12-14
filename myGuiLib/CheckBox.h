#pragma once

#include <string>

#include "Component.h"

class CheckBox : public Component {
public:
	CheckBox(MyPoint at, int width, int height, std::string text = "");
	CheckBox(int width, int height, std::string text = "");

	void paintContent(HDC hDC) override;
	
	int getContentWidth() const override;
	int getContentHeight() const override;

	void onClick(MyEvent e) override;

	std::string getText() const;
	void setText(std::string text);

	bool isChecked() const;
	void setChecked(bool value);
	void toggle();

	static const int DEFAULT_PADDING = 10;

	static const int LETTER_WIDTH = 9;
	static const int LETTER_HEIGHT = 16;

	static const std::string CHECKED;
	static const std::string NOT_CHECKED;
	static const std::string INTERVAL_BLANK;

protected:
	virtual std::string getCheckStateText() const;
	bool checked_ = false;

private:
	void setOnClickListener(OnClickListener* listener) override;

	std::string text_;
};
