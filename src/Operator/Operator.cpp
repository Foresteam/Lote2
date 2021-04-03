#include "../Runtime.h"
#include "../Lib/Utils.h"
#include "../Object/Function/Function.h"
#include "../Object/Pointer/Pointer.h"
#include <iostream>
void Operators::Init() {
	static bool building = false;
	// string building
	operators.push_back([](vsi& it) {
		static list<string> builded;
		string word = *it;

		if (building) {
			if (Str::endsWith(word, "'") && !Str::endsWith(word, "\\'")) {
				word.erase(word.size() - 1);
				building = false;
			}
			builded.push_back(word);
			if (building)
				return true;
		}
		else if (Str::startsWith(word, "'") && !Str::startsWith(word, "\\'")) {
			building = true;
			word.erase(word.begin());
			if (Str::endsWith(word, "'") && !Str::endsWith(word, "\\'")) {
				word.erase(word.size() - 1);
				building = false;
			}
			builded.push_back(word);
			if (building)
				return true;
		}

		if (!building && builded.size() > 0) {
			string* sv = new string(Str::join(builded, " "));
			/*if (Str::startsWith(*sv, " "))
				sv->erase(sv->begin());*/
			if (Str::endsWith(*sv, " "))
				sv->erase(sv->end() - 1);
			size_t pos;
			while ((pos = sv->find("\\n")) != string::npos)
				sv->replace(pos, 2, "\n");
			mainStack.Push(new Object(*sv, sv, "string"));
			builded.clear();
			return true;
		}

		return false;
	});
	// vars
	operators.push_back([](vsi& it) {
		string word = *it;
		if (word == "define") {
			bool global = false;
			Scope* to = scopes.back();
			string name;
			{
				auto t = mainStack.Pop();
				name = t->SEval();
				Runtime::DObject(t);
			}
			if (name == "global") {
				global = true;
				{
					auto t = mainStack.Pop();
					name = t->SEval();
					Runtime::DObject(t);
				}
				to = scopes.front();
			}
			if (to->GetObject(name))
				throw AlreadyDefined();

			Object* no = new Object();
			to->Assign(name, no);
			mainStack.Push(new Pointer(no));

			return true;
		}
		else if (Str::endsWith(word, "&") || word == "var") {
			string vname = word;
			if (Str::endsWith(vname, "&"))
				vname = vname.substr(0, vname.size() - 1);
			else {
				Object* ovname = mainStack.Pop();
				vname = ovname->SEval();
				Runtime::DObject(ovname);
			}
			mainStack.Push(new Pointer(Runtime::FindObjectByName(vname)));
			return true;
		}
		else if (word == "assign" || word == "=") {
			Object* pnvalue = mainStack.Pop();
			Object* pvar = mainStack.Pop();
			/*if (Object* np = reinterpret_cast<Object*>(pnvalue->Eval()))
				pnvalue = np;*/
			*reinterpret_cast<Object*>(pvar->Eval()) = *pnvalue;
			Runtime::DObject(pvar);
			Runtime::DObject(pnvalue);
			return true;
		}
		else if (word == "unlink") {
			bool global;
			Object* pvarname;
			pvarname = mainStack.Pop();
			if (pvarname->SEval() == "global") {
				global = true;
				Runtime::DObject(pvarname);
				pvarname = mainStack.Pop();
			}
			else
				global = false;
			Runtime::Unlink(pvarname->SEval(), global);
			Runtime::DObject(pvarname);
			return true;
		}
		else if (word == "delete") {
			Object* pobj = mainStack.Pop();
			Runtime::DObject(pobj, true);
			return true;
		}
		return false;
	});
	// eval & call
	operators.push_back([](vsi& it) {
		string word = *it;
		Object* po = nullptr;
		if (Str::endsWith(word, "()") || word == "call") {
			word = word != "call" ? word.erase(word.size() - 2, 2) : "";
			string fn;
			if (word.size() > 0)
				fn = word;
			else {
				Object* o = mainStack.Pop();
				fn = o->SEval();
				Runtime::DObject(o);
			}
			po = Runtime::FindObjectByName(fn);
			if (!po)
				return true;
		}
		else if (word == "eval") {
			Object* ptr = mainStack.Pop();
			po = reinterpret_cast<Object*>(ptr->Eval());
			if (!po)
				return true;
			Runtime::DObject(ptr);
		}
		if (po) {
			if (Str::startsWith(po->GetType(), "Function."))
				po->Eval();
			else {
				po->AddRef();
				mainStack.Push(po);
			}
			return true;
		}
		return false;
	});
	// binary operators
	operators.push_back([](vsi& it) {
		string word = *it;
		if (word.size() != 1)
			return false;

		Object *b, *a;
		auto _ = [&a, &b]() { b = mainStack.Pop(), a = mainStack.Pop(); };
		switch (word[0]) {
			case '+':
				_();
				*a + *b;
				break;
			/*case '-':
				_();
				rs = *a - *b;
				break;
			case '*':
				_();
				rs = *a * *b;
				break;*/
			default:
				return false;
		}
		Runtime::DObject(b);
		mainStack.Push(a);

		return true;
	});
	// default
	operators.push_back([](vsi& it) {
		mainStack.Push(new Object(*it));
		return true;
	});
}