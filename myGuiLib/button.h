#pragma once

#include <string>
#include "Misc.h"
#include "Component.h"

class Frame;
class OnClickListener;

class Button : public Component {
public:
	Button(MyPoint at, int width, int height, std::string text, bool paintBorder = true);

	std::string getText() const;
	void setText(std::string text);

	int getContentWidth() const override;
	int getContentHeight() const override;

	static const int DEFAULT_PADDING = 10;
	static const int DEFAULT_MARGIN = 0;

	static const int LETTER_WIDTH = 9;
	static const int LETTER_HEIGHT = 16;
	
protected:
	void paintContent(HDC hDC) override;

	std::string text_;
};
