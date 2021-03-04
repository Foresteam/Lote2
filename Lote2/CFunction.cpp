#include "CFunction.h"
#include <iostream>

void CFunction::Register(string name, lfunction eval) {
	Function::Register(name, new CFunction(name, eval));
}

void CFunction::Init() {
	Register("print", [](Scope* s) {
		auto t = mainStack.Pop();
		cout << t->SEval() << endl;
		Runtime::DObject(t);
	});
	Register("printAll", [](Scope* s) {
		auto t = mainStack.Pop();
		string delimiter = t->SEval();
		Runtime::DObject(t);
		while (!mainStack.IsEmpty()) {
			t = mainStack.Pop();
			cout << t->SEval();
			Runtime::DObject(t);
			if (!mainStack.IsEmpty())
				cout << delimiter;
		}
		cout << endl;
	});
	Register("sDupRef", [](Scope* s) {
		(*mainStack.Peek())->AddRef();
		mainStack.Dup();
	});
	Register("sDup", [](Scope* s) {
		mainStack.Push(new Object(**mainStack.Peek()));
	});
	Register("sDrop", [](Scope* s) {
		Object* pobject = mainStack.Pop();
		Runtime::DObject(pobject);
	});
	Register("sRot", [](Scope* s) {
		mainStack.Rot();
	});
	Register("sSwap", [](Scope* s) {
		mainStack.Swap();
	});
	Register("sFlip", [](Scope* s) {
		mainStack.Flip();
	});
	Register("sIsEmpty", [](Scope* s) {
		bool* isEmpty = new bool(mainStack.IsEmpty());
		mainStack.Push(new Object(*isEmpty ? "true" : "false", isEmpty, "bool"));
	});
	Register("typeof", [](Scope* s) {
		auto t = mainStack.Pop();
		string type = t->GetType();
		Runtime::DObject(t);
		mainStack.Push(new Object(type, "string"));
	});
}

void* CFunction::Eval(bool toStack) {
	eval(origin);
	return nullptr;
}
