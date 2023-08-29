#include "../include/WindowsKit.h"

#include <Windows.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	switch (msg) {
	case WM_CREATE: {
		NSApp->window->contentView->handle = hwnd;
		break;
	}
	case WM_PAINT: {
		RECT rc;
		GetUpdateRect(hwnd, &rc, FALSE);
		NSRect nsrc = NSMakeRect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top);
		NSApp->window->contentView->drawRect(nsrc);
		break;
	}
	case WM_CLOSE: {
		PostQuitMessage(0);
		break;
	}
	}
	return DefWindowProcW(hwnd, msg, wparam, lparam);
}

NSApplication* NSApplication::alloc() {
	return new NSApplication();
}

void NSApplication::setWindow(NSWindow* win) {
	this->window = win;
}

void NSApplication::run() {
	NSApp = this;

	unsigned int nssm = this->window->winStyleMask;
	DWORD style = 0;
	
	if ((nssm & NSWindowStyleMaskFullSizeContentView) == 0) {
		style |= ((nssm & NSWindowStyleMaskTitled) != 0) ? WS_CAPTION : 0;
		style |= ((nssm & NSWindowStyleMaskClosable) != 0) ? WS_SYSMENU : 0;
		style |= ((nssm & NSWindowStyleMaskMiniaturizable) != 0) ? WS_MINIMIZEBOX : 0;
		style |= ((nssm & NSWindowStyleMaskResizable) != 0) ? WS_THICKFRAME | WS_MAXIMIZEBOX : 0;
	}

	style |= (this->window->show) ? WS_VISIBLE : 0;

	WNDCLASSW wc = {0};
	wc.lpszClassName = L"windowskit";
    wc.hInstance     = GetModuleHandleW(NULL);
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpfnWndProc   = WndProc;
    wc.hCursor       = LoadCursor(0, IDC_ARROW);
	RegisterClassW(&wc);

	NSRect nsrc = this->window->frame;
	RECT rc = {};
	rc.right = nsrc.w;
	rc.bottom = nsrc.h;
	AdjustWindowRect(&rc, style, NULL);
	rc.left += nsrc.x;
	rc.top += nsrc.y;
	rc.right += nsrc.x;
	rc.bottom += nsrc.y;

	HWND hwnd = CreateWindowW(L"windowskit", this->window->winTitle->str, style, rc.left, rc.top, rc.right, rc.bottom, NULL, NULL, GetModuleHandleW(NULL), NULL);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
}

void NSApplication::setActivationPolicy(NSApplicationActivationPolicy policy) {
	this->appPolicy = policy;
}
