#include "../include/WindowsKit.h"

NSView* NSView::alloc() {
	return new NSView();
}

NSView* NSView::initWithFrame(NSRect frameRect) {
	this->frame = frameRect;
	return this;
}