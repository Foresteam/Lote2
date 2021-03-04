#include "Function.h"

void Function::Register(string name, Function* function) {
	Scope* scope = scopes.back();
	if (scope->GetObject(name)) {
		delete function;
		return;// decide what to do with constants
	}
	scope->Assign(name, function);
}
void Function::Register(string name, size_t start, size_t end) {
	Register(name, new Function(name, start, end));
}

void* Function::Eval(bool toStack) {
	return nullptr;
}
