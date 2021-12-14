#pragma once

#include <list>

#include "Component.h"

class Container : public Component {
public:
	enum class Orientation {
		VERTICAL, HORIZONTAL
	};

	Container(MyPoint start, int width, int height, Orientation orientation);
	Container(MyPoint start, int width, int height, bool paintBorder, Orientation orientation);
	virtual ~Container();
	void onClick(MyEvent e) override;
	int getContentWidth() const override;
	int getContentHeight() const override;
	void setOrientation(Orientation orientation);
	void setStartPoint(MyPoint at) override;
	void moveStartPoint(MyPoint at) override;
	bool isInComponent(MyPoint at) const override;

	virtual void addChild(Component* component);

	static const int DEFAULT_PADDING = 10;

protected:
	void paintContent(HDC hDC) override;
	std::list<Component*> components_;

private:
	int getMaxWidth() const;
	int getMaxHeight() const;
	int getTotalWidth() const;
	int getTotalHeight() const;

	void setChildHorizontal(Component* component);
	void setChildVertical(Component* component);

	void setOnClickListener(OnClickListener* listener) override;

	Orientation orientation_;
};
