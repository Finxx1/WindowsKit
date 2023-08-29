#include "../include/WindowsKit.h"

NSWindow* NSWindow::alloc() {
	return new NSWindow();
}

NSWindow* NSWindow::init() {
	return this->initWithContentRect(NSMakeRect(0, 0, 150, 150), NSWindowStyleMask::NSWindowStyleMaskTitled, NSBackingStoreType::NSBackingStoreBuffered, false);
}

NSWindow* NSWindow::initWithContentRect(NSRect contentRect, unsigned int styleMask, NSBackingStoreType backing, bool defer) {
	this->frame = contentRect;
	this->winStyleMask = styleMask;
	this->winBacking = backing;
	this->winDefer = defer;

	this->show = false;

	this->contentView = NSView::alloc()->initWithFrame(this->frame);

	return this;
}

void NSWindow::cascadeTopLeftFromPoint(NSPoint point) {
	this->frame.x += point.x;
	this->frame.y += point.y;
}

void NSWindow::setTitle(NSString* str) {
	this->winTitle = str;
}

void NSWindow::makeKeyAndOrderFront() {
	this->show = true;
}
