#include <iostream>

#include "PaintFrame.h"
#include "Button.h"
#include "PaintOnClickListeners.h"
#include "Label.h"
#include "MenuBar.h"
#include "Menu.h"
#include "Command.h"
#include "CommandManager.h"
#include "PaintButtons.h"
#include "SubMenu.h"
#include "CheckBox.h"
#include "RadioButton.h"
#include "RadioButtonGroup.h"
#include "SelectionList.h"
#include "SelectionComponent.h"
#include "FigureManager.h"
#include "EditText.h"
#include "ColorMenu.h"
#include "SpinButton.h"

PaintFrame::PaintFrame(std::wstring title, int width, int height)
	: Frame(title, width, height), commandManager_(new CommandManager()), figureManager_(new FigureManager()) { }

PaintFrame::~PaintFrame() {
	delete commandManager_;
}

void PaintFrame::initialize() {
	Frame::initialize();
	
	UndoButton* undoButton = new UndoButton(60, Component::WRAP_CONTENT, commandManager_);
	RedoButton* redoButton = new RedoButton(60, Component::WRAP_CONTENT, commandManager_);
	undoButton->setOnClickListener(new UndoButtonListener(commandManager_));
	redoButton->setOnClickListener(new RedoButtonListener(commandManager_));
	commandManager_->addObserver(undoButton);
	commandManager_->addObserver(redoButton);

	Button* saveButton = new Button(90, Component::WRAP_CONTENT, "Save");
	saveButton->setOnClickListener(new SaveButtonListener(this));

    Menu* figureTypeMenu = new Menu(100, Component::WRAP_CONTENT, "Figure Type");
    RadioButtonGroup* figureRadioButtonGroup = new RadioButtonGroup(Component::WRAP_CONTENT, Component::WRAP_CONTENT);
    RadioButton* rectangleButton = new RadioButton(120, Component::WRAP_CONTENT, "Rectangle");
    RadioButton* ellipseButton = new RadioButton(120, Component::WRAP_CONTENT, "Ellipse");
	rectangleButton->setOnClickListener(new FigureButtonListener(figureManager_, nullptr, Figure::Type::RectangleType));
	ellipseButton->setOnClickListener(new FigureButtonListener(figureManager_, nullptr, Figure::Type::EllipseType));
	figureRadioButtonGroup->addChild(rectangleButton);
	figureRadioButtonGroup->addChild(ellipseButton);
    figureRadioButtonGroup->select(rectangleButton);
    figureTypeMenu->addComponent(figureRadioButtonGroup);

	Menu* toolMenu = new Menu(90, Component::WRAP_CONTENT, "Tool");
	RadioButtonGroup* toolRadioGroup = new RadioButtonGroup(Component::WRAP_CONTENT, Component::WRAP_CONTENT);
	RadioButton* penRadioButton = new RadioButton(180, Component::WRAP_CONTENT, "Pen");
	RadioButton* eraserRadioButton = new RadioButton(180, Component::WRAP_CONTENT, "Eraser");
	RadioButton* unGroupRadioButton = new RadioButton(180, Component::WRAP_CONTENT, "Ungroup");
	RadioButton* movePositionRadioButton = new RadioButton(180, Component::WRAP_CONTENT, "Move Position");
	
	SelectionList* positionSelectionList = new SelectionList(180, Component::WRAP_CONTENT, "Position");
	SelectionComponent* frontPositionButton = new SelectionComponent(180, Component::WRAP_CONTENT, "Front");
	SelectionComponent* backPositionButton = new SelectionComponent(180, Component::WRAP_CONTENT, "Back");
	frontPositionButton->setOnClickListener(new MovePositionButtonListener(figureManager_, FigureMovePosition::Front));
	backPositionButton->setOnClickListener(new MovePositionButtonListener(figureManager_, FigureMovePosition::Back));
	positionSelectionList->addChild(frontPositionButton);
	positionSelectionList->addChild(backPositionButton);

	penRadioButton->setOnClickListener(new SetToolButtonListener(figureManager_, PaintTool::Pen));
	eraserRadioButton->setOnClickListener(new SetToolButtonListener(figureManager_, PaintTool::Eraser));
	unGroupRadioButton->setOnClickListener(new SetToolButtonListener(figureManager_, PaintTool::UnGroup));
	movePositionRadioButton->setOnClickListener(new SetToolButtonListener(figureManager_, PaintTool::MovePosition));

	toolRadioGroup->addChild(penRadioButton);
	toolRadioGroup->addChild(eraserRadioButton);
	toolRadioGroup->addChild(unGroupRadioButton);
	toolRadioGroup->addChild(movePositionRadioButton);
	toolRadioGroup->select(penRadioButton);
	toolMenu->addComponent(toolRadioGroup);
	toolMenu->addComponent(positionSelectionList);

	ColorMenu* colorMenu = new ColorMenu(this);
	figureManager_->setColorMenu(colorMenu);

	Menu* etcMenu = new Menu(90, Component::WRAP_CONTENT, "Etc");
	SubMenu* errorRangeSubMenu = new SubMenu(120, Component::WRAP_CONTENT, "Error Range");
	SpinButton* errorRangeSpinButton = new SpinButton(100, Component::WRAP_CONTENT);
	CheckBox* groupBorderCheckBox = new CheckBox(120, Component::WRAP_CONTENT, "Box Border");
	errorRangeSpinButton->setValue(FigureManager::DEFAULT_ERROR_RANGE);
	groupBorderCheckBox->setOnClickListener(new GroupBorderCheckBoxListener(figureManager_, groupBorderCheckBox));
	groupBorderCheckBox->setChecked(true);
	
	errorRangeSubMenu->addComponent(errorRangeSpinButton);
	etcMenu->addComponent(groupBorderCheckBox);
	etcMenu->addComponent(errorRangeSubMenu);

	menuBar_ = new MenuBar(hWnd_);
	menuBar_->setPadding(0);
	menuBar_->setBorder(true);	
	menuBar_->addChild(undoButton);
	menuBar_->addChild(redoButton);
	menuBar_->addChild(saveButton);
    menuBar_->addChild(figureTypeMenu);
	menuBar_->addChild(toolMenu);
	menuBar_->addChild(colorMenu);
	menuBar_->addChild(etcMenu);

    figureManager_->setErrorRangeSpinButton(errorRangeSpinButton);

	addComponent(menuBar_);
}

void PaintFrame::eventHandler(MyEvent e) {
	Frame::eventHandler(e);

	if (e.isLButtonDown() || e.isRButtonDown()) {
		start_ = e.getPos();
	}
	else if (e.isLButtonUp() || e.isLButtonUp()) {
		if (!menuBar_->isInComponent(e.getPos())) {
			Command* command = Command::createCommand(start_, e, figureManager_);
			commandManager_->execute(command);
		}
	}
}

void PaintFrame::repaint() {
	for (Figure* figure : figureManager_->getFigures()) {
		figure->paint(hDC_);
	}

	Frame::repaint();
	
}

int PaintFrame::save() {
    HDC hdcScreen;
    HDC hdcWindow;
    HDC hdcMemDC = NULL;
    HBITMAP hbmScreen = NULL;
    BITMAP bmpScreen;
    DWORD dwBytesWritten = 0;
    DWORD dwSizeofDIB = 0;
    HANDLE hFile = NULL;
    char* lpbitmap = NULL;
    HANDLE hDIB = NULL;
    DWORD dwBmpSize = 0;

    // Retrieve the handle to a display device context for the client 
    // area of the window. 
    hdcScreen = GetDC(NULL);
    hdcWindow = GetDC(hWnd_);

    // Create a compatible DC, which is used in a BitBlt from the window DC.
    hdcMemDC = CreateCompatibleDC(hdcWindow);

    if (!hdcMemDC)
    {
        MessageBox(hWnd_, L"CreateCompatibleDC has failed", L"Failed", MB_OK);
        goto done;
    }

    // Get the client area for size calculation.
    RECT rcClient;
    GetClientRect(hWnd_, &rcClient);

    // Create a compatible bitmap from the Window DC.
    hbmScreen = CreateCompatibleBitmap(hdcWindow, rcClient.right - rcClient.left, rcClient.bottom - rcClient.top);

    if (!hbmScreen)
    {
        MessageBox(hWnd_, L"CreateCompatibleBitmap Failed", L"Failed", MB_OK);
        goto done;
    }

    // Select the compatible bitmap into the compatible memory DC.
    SelectObject(hdcMemDC, hbmScreen);

    // Bit block transfer into our compatible memory DC.
    if (!BitBlt(hdcMemDC,
        0, 0,
        rcClient.right - rcClient.left, rcClient.bottom - rcClient.top,
        hdcWindow,
        0, menuBar_->getHeight(),
        SRCCOPY))
    {
        MessageBox(hWnd_, L"BitBlt has failed", L"Failed", MB_OK);
        goto done;
    }

    // Get the BITMAP from the HBITMAP.
    GetObject(hbmScreen, sizeof(BITMAP), &bmpScreen);

    BITMAPFILEHEADER   bmfHeader;
    BITMAPINFOHEADER   bi;

    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bmpScreen.bmWidth;
    bi.biHeight = bmpScreen.bmHeight - menuBar_->getHeight();
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    dwBmpSize = ((bmpScreen.bmWidth * bi.biBitCount + 31) / 32) * 4 * bmpScreen.bmHeight;

    // Starting with 32-bit Windows, GlobalAlloc and LocalAlloc are implemented as wrapper functions that 
    // call HeapAlloc using a handle to the process's default heap. Therefore, GlobalAlloc and LocalAlloc 
    // have greater overhead than HeapAlloc.
    hDIB = GlobalAlloc(GHND, dwBmpSize);
    lpbitmap = (char*)GlobalLock(hDIB);

    // Gets the "bits" from the bitmap, and copies them into a buffer 
    // that's pointed to by lpbitmap.
    GetDIBits(hdcWindow, hbmScreen, 0,
        (UINT)bmpScreen.bmHeight,
        lpbitmap,
        (BITMAPINFO*)&bi, DIB_RGB_COLORS);

    // A file is created, this is where we will save the screen capture.
    hFile = CreateFile(L"captureqwsx.bmp",
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL, NULL);

    // Add the size of the headers to the size of the bitmap to get the total file size.
    dwSizeofDIB = dwBmpSize + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // Offset to where the actual bitmap bits start.
    bmfHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) + (DWORD)sizeof(BITMAPINFOHEADER);

    // Size of the file.
    bmfHeader.bfSize = dwSizeofDIB;

    // bfType must always be BM for Bitmaps.
    bmfHeader.bfType = 0x4D42; // BM.

    WriteFile(hFile, (LPSTR)&bmfHeader, sizeof(BITMAPFILEHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)&bi, sizeof(BITMAPINFOHEADER), &dwBytesWritten, NULL);
    WriteFile(hFile, (LPSTR)lpbitmap, dwBmpSize, &dwBytesWritten, NULL);

    // Unlock and Free the DIB from the heap.
    GlobalUnlock(hDIB);
    GlobalFree(hDIB);

    // Close the handle for the file that was created.
    CloseHandle(hFile);

    // Clean up.
done:
    DeleteObject(hbmScreen);
    DeleteObject(hdcMemDC);
    ReleaseDC(NULL, hdcScreen);
    ReleaseDC(hWnd_, hdcWindow);

    return 0;
}