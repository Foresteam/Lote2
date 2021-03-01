#pragma once
#include <string>
#include "Exception.h"
#include <sstream>
using namespace std;

class Object {
protected:
	string type;
	void* value;
	bool constant, destroy;
	string svalue;
public:
	Object(string svalue, void* value = nullptr, string type = "auto", bool constant = false, bool destroy = true) {
		this->constant = constant;
		this->destroy = destroy;

		if (type == "auto") {
			if (value == nullptr && svalue == "null")
				type = "null";
			else if (svalue == "true" || svalue == "false")
				type = "bool";
			else {
				try {
					stringstream ss;
					ss << svalue;
					if (svalue.find(".") == string::npos) {
						if (!value)
							value = new long int();
						ss >> *reinterpret_cast<long int*>(value);
						type = "int";
					}
					else {
						if (!value)
							value = new long double();
						ss >> *reinterpret_cast<long double*>(value);
						type = "float";
					}
				}
				catch (exception e) {
					type = "string";
				}
			}
		}
		this->type = type;
		this->value = value;
		if (svalue.size() > 0)
			this->svalue = svalue;
		else if (value) {
			if (type == "bool")
				svalue = *reinterpret_cast<bool*>(value) ? "true" : "false";
			else {
				stringstream ss;
				if (type == "float")
					ss << *reinterpret_cast<long double*>(value);
				else if (type == "int")
					ss << *reinterpret_cast<long int*>(value);
				ss >> this->svalue;
			}
		}
	}
	Object() : Object("null", nullptr, "null") {}
	~Object() {
		if (destroy && value && type != "null") {
			if (type == "string")
				delete (string*)value;
		}
	}

	virtual void* Eval(bool toStack = true);
	string SEval(bool toStack = true);
	void* GetModigy();
	virtual void* GetReAssign();

	bool IsNumber();

	Object operator+(Object other);
};