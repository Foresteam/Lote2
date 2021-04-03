#pragma once
#include <map>
#include "../Object/Object.h"
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
	void Repoint(Object* o, Object* n);
	bool Unlink(string name);
};