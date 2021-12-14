#pragma once
#include "Windows.h"
#include <string>
#include <list>
#include "Misc.h"

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

class Component;

class Frame {
protected:
	// Window ���α׷����� ���� �⺻ �������̴�. �ǵ帮�� �ʴ´�.
	HINSTANCE hInst_;
	HWND hWnd_;
	HDC hDC_;    // �� ������ �־�� �׸��� �׸� �� �ִ�.

	std::list<Component*> components_;


public:
	Frame();
	Frame(std::wstring, int, int);
	virtual ~Frame();
	virtual void initialize();
	virtual void run();

	virtual void eventHandler( MyEvent e);
	virtual void repaint();
	void invalidate();

	void addComponent(Component* component);
	Component* findComponent(MyPoint at) const;
};