#pragma once
#include <list>
#include <iostream>
#include "Stack.h"
#include "Object.h"
#include "Scope.h"
#include "Operator.h"

extern Stack<Object*> mainStack;
extern list<Scope*> scopes;
extern list<Operator> operators;

namespace Runtime {
	Object* FindObjectByName(string name);
	//string FindObjectReference(Object* pobject);
	bool ObjectHasReference(Object* pobject);

	void DObject(Object* pobject, bool anyway = false);
	void Unlink(string name, bool global);
}