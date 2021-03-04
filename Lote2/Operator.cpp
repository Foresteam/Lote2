#include "Runtime.h"
#include "Utils.h"
#include "Function.h"
#include <iostream>
#include "Pointer.h"
void Operators::Init() {
	static bool building = false;
	// string building
	operators.push_back([](vsi& it) {
		static list<string> builded;
		string word = *it;

		list<string::iterator> indexes = list<string::iterator>();
		for (auto it = word.rbegin(); it.base() != word.begin(); it++)
			if (*it == 'n' && *(it + 1) == '\\' && ((it + 2) == word.rend() || *(it + 2) != '\\'))
				indexes.push_back(it.base());
		for (auto it : indexes)
			word.replace(it, it + 1, "\n");

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
			mainStack.Push(new Object(*sv, sv, "string"));
			builded.clear();
			return true;
		}

		return false;
	});
	// vars
	operators.push_back([](vsi& it) {
		if (*it == "define") {
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
		else if (*it == "var") {
			string name;
			{
				auto t = mainStack.Pop();
				name = t->SEval();
				Runtime::DObject(t);
			}
			mainStack.Push(new Pointer(Runtime::FindObjectByName(name)));
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
	// function calling
	operators.push_back([](vsi& it) {
		string word = *it;
		if (Str::endsWith(word, "()") || word == "eval") {
			word = word.erase(word.size() - 2, 2);
			string fn;
			if (word.size() > 0)
				fn = word;
			else {
				Object* o = mainStack.Pop();
				fn = o->SEval();
				Runtime::DObject(o);
			}
			Runtime::FindObjectByName(fn)->Eval();
			return true;
		}
		return false;
	});
	// default
	operators.push_back([](vsi& it) {
		mainStack.Push(new Object(*it));
		return true;
	});
}