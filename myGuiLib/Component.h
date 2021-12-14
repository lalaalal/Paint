#pragma once

#include "Misc.h"

class OnClickListener;
class Container;

class Component {
public:
	Component(MyPoint at, int width, int height, int padding = 0, int margin = 0, bool paintBorder = false);
	virtual ~Component();
	virtual bool isInComponent(MyPoint at) const;
	virtual void onClick(MyEvent e);
	virtual void setOnClickListener(OnClickListener* listener);
	void paint(HDC hDC);
	void setBorder(bool value);

	int getPadding() const;
	int getMargin() const;
	void setPadding(int padding);
	void setMargin(int padding);

	bool isVisible() const;
	void setVisibility(bool value);

	MyPoint getStartPoint() const;
	virtual void setStartPoint(MyPoint at);
	virtual void moveStartPoint(MyPoint delta);
	virtual int getWidth() const;
	virtual int getContentWidth() const = 0;
	virtual int getHeight() const;
	virtual int getContentHeight() const = 0;
	virtual void setWidth(int width);
	virtual void setHeight(int height);

	Container* getParent() const;
	void setParent(Container* parent);

	static const int WRAP_CONTENT = -1;
	static const int MATCH_PARENT = -2;

protected:
	virtual void paintContent(HDC hDC);

	MyPoint at_;

	int padding_;
	int margin_;

	Container* parent_ = nullptr;

private:
	OnClickListener* listener_ = nullptr;
	bool paintBorder_;
	bool isVisible_ = true;

	int width_;
	int height_;
};
