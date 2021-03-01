#include "CFunction.h"
#include <iostream>

void CFunction::Register(string name, lfunction eval) {
	Function::Register(name, new CFunction(name, eval));
}

void CFunction::Init() {
	Register("print", [](Scope* s) {
		void* result = nullptr;

		cout << mainStack.Pop().SEval() << endl;

		return result;
	});
}

void* CFunction::Eval(bool toStack) {
	return eval(origin);
}
