#include "../include/WindowsKit.h"

#include <Windows.h>

class WKView : public NSView {
public:
	static WKView* WKView::alloc() {
		return new WKView();
	}
	void drawRect(NSRect dirtyRect) {
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint((HWND)this->handle, &ps);

		Rectangle(hdc, 0, 0, 50, 50);

		EndPaint((HWND)this->handle, &ps);
	}
};

int main() {
	NSApplication::sharedApplication();

	unsigned int style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable | NSWindowStyleMaskResizable;

	NSWindow* window = NSWindow::alloc()->initWithContentRect(NSMakeRect(0, 0, 480, 360), style, NSBackingStoreBuffered, false);
	window->setTitle(NSString::alloc()->initWithUTF8String("i forgor"));
	window->cascadeTopLeftFromPoint(NSMakePoint(50, 50));
	window->contentView = WKView::alloc()->initWithFrame(window->frame);
	window->makeKeyAndOrderFront();

	NSApp->setWindow(window);
	NSApp->run();
}
