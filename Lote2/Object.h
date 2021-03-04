#pragma once
#include <string>
#include "Exception.h"
#include <sstream>
#include "Utils.h"
using namespace std;

class Object {
private:
	void ValueFromString();
	void StringFromValue();
	void FindType();
protected:
	size_t krefs;
	string type;
	void* value;
	bool constant;
	string svalue;
public:
	Object(string svalue, void* value = nullptr, string type = "auto", bool constant = false);
	Object(string svalue, string type) : Object(svalue, nullptr, type) {}
	Object(void* value, string type) : Object("", value, type) {}
	Object() : Object("null", nullptr, "null") {}
	~Object();

	virtual void* Eval(bool toStack = true);
	string SEval(bool toStack = true);
	string GetType();
	void* GetModigy();
	virtual void* GetReAssign();

	bool IsNumber();

	size_t GetKRefs();
	void AddRef();
	void RemoveRef();

	Object* operator+(Object& other);
	Object* operator-(Object& other);
	Object* operator*(Object& other);
};