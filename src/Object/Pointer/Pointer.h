#pragma once
#include "../Object.h"
#include "../../Lib/Utils.h"
class Pointer : public Object {
public:
	Pointer(Object* value) {
		this->value = value;
		type = "*" + value->GetType();
		svalue = Str::fromPtr(value);
	}
};

