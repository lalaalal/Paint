#pragma once

#include "frame.h"

class CommandManager;
class FigureManager;
class MenuBar;

class PaintFrame : public Frame {
public:
	PaintFrame(std::wstring title, int width, int height);
	virtual ~PaintFrame();

	void initialize() override;
	void eventHandler(MyEvent e) override;
	void repaint() override;

	int save();
private:
	// 응용을 위해 필요한 변수
	MyPoint start_;

	MenuBar* menuBar_ = nullptr;
	CommandManager* commandManager_;
	FigureManager* figureManager_;
};
