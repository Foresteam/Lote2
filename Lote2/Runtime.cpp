#include "Runtime.h"

Stack<Object*> mainStack = Stack<Object*>();
list<Scope*> scopes = list<Scope*>();
list<Operator> operators = list<Operator>();

Object* Runtime::FindObjectByName(string name) {
	for (auto it = scopes.rbegin(); it != scopes.rend(); it++)
		if (Object* o = (*it)->GetObject(name))
			return o;
	throw NullReference();
}

//string Runtime::FindObjectReference(Object* pobject) {
//	string name = "";
//	/*bool mmm = name.c_str();
//	cout << (mmm ? '1' : '0') << endl;*/
//	for (auto it = scopes.rbegin(); it != scopes.rend(); it++)
//		if ((name = (*it)->GetName(pobject)).size() > 0)
//			break;
//	return name;
//}

bool Runtime::ObjectHasReference(Object* pobject) {
	return pobject->GetKRefs() > 0;//FindObjectReference(pobject).size() > 0;
}

void Runtime::DObject(Object* pobject) {
	if (ObjectHasReference(pobject))
		pobject->RemoveRef();
	else
		delete pobject;
}
