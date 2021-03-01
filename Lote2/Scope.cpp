#include "Scope.h"

Object* Scope::GetObject(string name) {
	auto it = refs.find(name);
	return it != refs.end() ? (*it).second : nullptr;
}

bool Scope::Assign(string name, Object* value) {
	auto it = refs.find(name);
	if (it == refs.end())
		refs.insert(pair<string, Object*>(name, value));
	else if ((*it).second->GetReAssign())
		*(*it).second = *value;
	else
		return false;
	return true;
}
