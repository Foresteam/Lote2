#pragma once
#include "Object.h"
#include "Utils.h"
class Pointer : public Object {
public:
	Pointer(Object* value) {
		this->value = value;
		type = "p_" + value->GetType();
		svalue = Str::fromPtr(value);
	}
};

