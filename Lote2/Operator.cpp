#include "Runtime.h"
#include "Utils.h"
#include "Function.h"
#include <iostream>

void Operators::Init() {
	// string building
	operators.push_back([](vsi& it) {
		static bool building = false;
		static list<string> builded;
		string word = *it;

		list<string::iterator> indexes = list<string::iterator>();
		for (auto it = word.rbegin(); it != word.rend() - 1; it++)
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
			if (*sv == "  ")
				sv->erase(sv->begin());
			mainStack.Push(Object(*sv, sv, "String"));
			builded.clear();
			return true;
		}

		return false;
	});
	// binary operators
	operators.push_back([](vsi& it) {
		string word = *it;
		if (word.size() != 1)
			return false;

		Object b, a;
		Object rs;
		switch (word[0]) {
			case '+':
				b = mainStack.Pop(), a = mainStack.Pop();
				rs = a + b;
				break;
			default:
				return false;
		}
		mainStack.Push(rs);

		return true;
	});
	// function calling
	operators.push_back([](vsi& it) {
		string word = *it;
		if (Str::endsWith(word, "()")) {
			word = word.erase(word.size() - 2, 2);
			string fn;
			if (word.size() > 0)
				fn = word;
			else {
				Object o = mainStack.Pop();
				fn = o.SEval();
			}
			Function::Call(fn);
			return true;
		}
		return false;
	});
	// default
	operators.push_back([](vsi& it) {
		mainStack.Push(Object(*it));
		return true;
	});
}