#include "frame.h"
#include "Misc.h"
#include "button.h"
#include "Container.h"
#include <iostream>
// 일단은 전역 변수 1개는 사용한다.
extern Frame* mainWindow;
// 전역함수로는 윈도 메시지 처리 함수가 있다.

LRESULT CALLBACK WndProc(HWND Hw, UINT Msg, WPARAM wParam, LPARAM lParam)
{

	switch (Msg)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
	case WM_LBUTTONDOWN:
	case WM_LBUTTONDBLCLK:
	case WM_LBUTTONUP:
	case WM_RBUTTONDOWN:
	case WM_RBUTTONDBLCLK:
	case WM_RBUTTONUP:
	case WM_KEYDOWN:
	case WM_KEYUP:
	case WM_CHAR:
	case WM_SIZE:
		if (mainWindow != nullptr)
			mainWindow->eventHandler(MyEvent(Msg, wParam, lParam));
		break;
	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(Hw, &ps);
		// TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...
		if (ps.fErase) {
			OutputDebugString(L"배경을 그려야함\n");  // 이 줄은 테스트용이니 나중에 없앤다.
		}
		// MainWindow  객체의 repaint 를 호출한다.
		
		//Rectangle(hdc, 100, 100, 200, 300);   // 이것도 테스트용이니 없앤다.
		if (mainWindow != nullptr)
			mainWindow->repaint();
		EndPaint(Hw, &ps);  // BeginPaint의 짝이 된다

	}
	default: return DefWindowProc(Hw, Msg, wParam, lParam);
	}
	return 0;
}

Frame::Frame() : Frame(L"", 800, 600) {
	//
}
Frame::Frame(std::wstring title, int width, int height) {
	hInst_ = GetModuleHandle(NULL);
	FreeConsole(); // No console
	// Register win class
	WNDCLASSEX Wc;

	Wc.cbSize = sizeof(WNDCLASSEX);
	Wc.style = CS_HREDRAW | CS_VREDRAW;
	Wc.lpfnWndProc = WndProc;
	Wc.cbClsExtra = 0;
	Wc.cbWndExtra = 0;
	Wc.hInstance = hInst_;
	Wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	Wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	Wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	Wc.lpszMenuName = NULL;
	Wc.lpszClassName = L"MyWin";
	Wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&Wc);
	//WS_EX_TOPMOST
	hWnd_ = CreateWindowExW(WS_EX_COMPOSITED, L"MyWIn", (WCHAR*)title.c_str(),
		WS_OVERLAPPED |
		WS_SYSMENU | WS_MAXIMIZEBOX | WS_MINIMIZEBOX | // 종료 최소화 최대화 아이콘
		WS_THICKFRAME,  // resize가 가능하게
		0, 0, width, height, // x, y, width, height
		NULL, NULL, hInst_, NULL);  // Parent, Menu, instance handle, lpParam
	if (!hWnd_) throw 0;

	ShowWindow(hWnd_, SW_SHOW);
	UpdateWindow(hWnd_); 
	SetFocus(hWnd_);
	hDC_ = GetDC(hWnd_);
	invalidate();
}

Frame::~Frame() {
	while (!components_.empty()) {
		Component* component = components_.front();
		delete component;
		components_.pop_front();
	}
}

void Frame::initialize() {

}

void Frame::run() {
	//HACCEL hAccelTable = LoadAccelerators(hInst_, MAKEINTRESOURCE(IDI_APPLICATION));
	initialize();

	MSG msg;

	// 기본 메시지 루프입니다:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		//if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg)
		if (!TranslateAccelerator(msg.hwnd, NULL, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void Frame::eventHandler(MyEvent e)
{
	if (e.isRButtonUp() || e.isLButtonUp()) {
		MyPoint point = e.getPos();
		Component* component = findComponent(point);
		if (component != nullptr) {
			component->onClick(e);
		}
	}

	invalidate();
}

void Frame::invalidate() {
	InvalidateRect(hWnd_, nullptr, true);
	for (HWND hwnd : hwndList_) {
		ShowWindow(hwnd, SW_HIDE);
	}
}

void Frame::addHWND(HWND hwnd) {
	hwndList_.push_back(hwnd);
}

void Frame::removeHWND(HWND hwnd) {
	hwndList_.remove(hwnd);
}

HWND Frame::getHWND() const {
	return hWnd_;
}

void Frame::repaint() {
	SelectObject(hDC_, GetStockObject(BLACK_PEN));
	for (Component* component : components_) {
		component->paint(hDC_);
	}
}

void Frame::addComponent(Component* component) {
	if (component != nullptr) {
		components_.push_back(component);
	}
}

Component* Frame::findComponent(MyPoint at) const {
	for (Component* component : components_) {
		if (component->isInComponent(at)) {
			return component;
		}
	}
	return nullptr;
}