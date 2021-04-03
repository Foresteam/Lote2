#pragma once
#include <list>
#include <iostream>
#include "Lib/Stack/Stack.h"
#include "Object/Object.h"
#include "Scope/Scope.h"
#include "Operator/Operator.h"

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