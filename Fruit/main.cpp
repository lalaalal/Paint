#include <exception>
#include <iostream>

#include "FruitFrame.h"

Frame* mainWindow = nullptr;

int main() {
	try {
		mainWindow = new FruitFrame(L"��ü������Ʈ", 1000, 800);
		//mainWindow = new Frame();
		mainWindow->run();
	}
	catch (std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return 0;
}