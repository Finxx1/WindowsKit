#include "../include/WindowsKit.h"

#include <Windows.h>

NSString* NSString::alloc() {
	return new NSString();
}

NSString* NSString::init() {
	this->str = new wchar_t[1];
	this->str[0] = '\0';

	return this;
}

NSString* NSString::initWithUTF8String(const char* nullTerminatedCString) {
	int len = MultiByteToWideChar(CP_UTF8, 0, nullTerminatedCString, -1, NULL, 0);
	this->str = new wchar_t[len];
	MultiByteToWideChar(CP_UTF8, 0, nullTerminatedCString, -1, this->str, len);

	return this;
}

NSString* NSString::string() {
	NSString* r = NSString::alloc();
	r->str = new wchar_t[1];
	r->str[0] = '\0';
	return r;
}