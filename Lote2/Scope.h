#pragma once
#include <map>
#include "Object.h"
using namespace std;

typedef map<string, Object*> Refs;

class Scope {
protected:
	Refs refs;
public:
	Scope() {
		refs = Refs();
	}
	Object* GetObject(string name);
	string GetName(Object* pobject);
	bool Assign(string name, Object* value);
};