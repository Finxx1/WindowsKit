#pragma once

class NSObject {
	int refs;

public:
	void retain();
	void release();

	NSObject();
	~NSObject();
};

class NSString : NSObject{
public:
	wchar_t* str;

	static NSString* alloc();
	NSString* init();
	NSString* initWithUTF8String(const char* nullTerminatedCString);

	static NSString* string();
};

struct NSRect {
	float x, y, w, h;
};

static inline NSRect NSMakeRect(float x, float y, float w, float h) {
	NSRect r;
	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;
	return r;
}

struct NSPoint {
	float x, y;
};

static inline NSPoint NSMakePoint(float x, float y) {
	NSPoint r;
	r.x = x;
	r.y = y;
	return r;
}

enum NSWindowStyleMask {
	NSWindowStyleMaskBorderless = 0,
	NSWindowStyleMaskTitled = 1 << 0,
	NSWindowStyleMaskClosable = 1 << 1,
	NSWindowStyleMaskMiniaturizable = 1 << 2,
	NSWindowStyleMaskResizable = 1 << 3,
	NSWindowStyleMaskTexturedBackground = 1 << 8, // DEPRECATED
	NSWindowStyleMaskUnifiedTitleAndToolbar = 1 << 12,
	NSWindowStyleMaskFullScreen = 1 << 14,
	NSWindowStyleMaskFullSizeContentView = 1 << 15,
	NSWindowStyleMaskUtilityWindow = 1 << 4,
	NSWindowStyleMaskDocModalWindow = 1 << 6,
	NSWindowStyleMaskNonactivatingPanel = 1 << 7,
	NSWindowStyleMaskHUDWindow = 1 << 13
};

enum NSBackingStoreType {
	NSBackingStoreRetained,
	NSBackingStoreNonretained,
	NSBackingStoreBuffered
};

class NSView : NSObject {
public:
	NSRect frame;
	void* handle;
	
	static NSView* alloc();
	NSView* initWithFrame(NSRect frameRect);
	
	virtual void drawRect(NSRect dirtyRect) {};
};

class NSWindow : NSObject {
public:
	NSRect frame;
	unsigned int winStyleMask;
	NSBackingStoreType winBacking;
	bool winDefer;
	NSString* winTitle;
	bool show;
	NSView* contentView;
	
	static NSWindow* alloc();
	NSWindow* init();
	NSWindow* initWithContentRect(NSRect contentRect, unsigned int styleMask, NSBackingStoreType backing, bool defer);
	
	void setTitle(NSString* str);
	void cascadeTopLeftFromPoint(NSPoint point);
	
	void makeKeyAndOrderFront();
};

enum NSApplicationActivationPolicy {
	NSApplicationActivationPolicyRegular,
	NSApplicationActivationPolicyAccessory,
	NSApplicationActivationPolicyProhibited
};

class NSApplication : NSObject {
public:
	NSApplicationActivationPolicy appPolicy;

	NSWindow* window;
	static NSApplication* alloc();
	static void sharedApplication();
	
	void run();

	void setWindow(NSWindow* win);
	void setActivationPolicy(NSApplicationActivationPolicy policy);
};

static NSApplication* NSApp;

inline void NSApplication::sharedApplication() {
	NSApp = new NSApplication();
}