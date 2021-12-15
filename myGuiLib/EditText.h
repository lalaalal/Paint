#pragma once

#include <string>

#include "Component.h"
#include "Misc.h"

class Frame;

class EditText : public Component {
public:
	EditText(int width, int height, Frame* frame);
	~EditText();

	int getContentWidth() const override;
	int getContentHeight() const override;

	void paintContent(HDC hDC) override;

	std::string getText() const;

	static const int DEFAULT_PADDING = 10;
	static const int DEFAULT_ET_HEIGHT = 20;
private:
	HMENU editId_;
	HWND hEdit_;
	Frame* frame_;

	int etWidth_;
	int etHeight_;
};
