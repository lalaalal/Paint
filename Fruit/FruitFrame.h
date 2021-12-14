#pragma once

#include <string>

#include "frame.h"

class FruitFrame : public Frame {
public:
	FruitFrame(std::wstring title, int width, int height);
	void initialize() override;
};

