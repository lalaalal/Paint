#pragma once

#include <string>

#include "Component.h"

class Label : public Component {
public:
	Label(MyPoint at, int width, int height, std::string text, bool paintBorder = true);
	Label(int width, int height, std::string text);
	void setText(std::string text);
	std::string getText() const;

	int getContentWidth() const override;
	int getContentHeight() const override;

	static const int DEFAULT_PADDING = 10;

	static const int LETTER_WIDTH = 9;
	static const int LETTER_HEIGHT = 16;

protected:
	void paintContent(HDC hDC) override;

private:
	void onClick(MyEvent e) override;
	void setOnClickListener(OnClickListener* listener) override;

	std::string text_;
};

