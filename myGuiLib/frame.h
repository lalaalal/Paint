#pragma once
#include "Windows.h"
#include <string>
#include <list>
#include "Misc.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Component;

class Frame {
protected:
	// Window 프로그래밍을 위한 기본 변수들이다. 건드리지 않는다.
	HINSTANCE hInst_;
	HWND hWnd_;
	HDC hDC_;    // 이 변수가 있어야 그림을 그릴 수 있다.

	std::list<Component*> components_;
	std::list<HWND> hwndList_;
public:
	Frame();
	Frame(std::wstring, int, int);
	virtual ~Frame();
	virtual void initialize();
	virtual void run();

	virtual void eventHandler( MyEvent e);
	virtual void repaint();
	void invalidate();

	void addHWND(HWND hwnd);
	void removeHWND(HWND hwnd);
	HWND getHWND() const;

	void addComponent(Component* component);
	Component* findComponent(MyPoint at) const;
};