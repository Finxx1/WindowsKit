#include "../include/WindowsKit.h"

void NSObject::retain() {
	this->refs++;
}

void NSObject::release() {
	this->refs--;
	if (refs < 1) delete this;
}

NSObject::NSObject() {
	this->refs = 0;
	this->retain();
}

NSObject::~NSObject() {
	this->release();
}
