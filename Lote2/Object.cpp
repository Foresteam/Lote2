#include "Object.h"

void Object::ValueFromString() {
	if (type == "string")
		value = new string(svalue);
	else if (IsNumber()) {
		stringstream ss;
		ss << svalue;
		if (type == "int") {
			value = new long int();
			ss >> *reinterpret_cast<long int*>(value);
		}
		else {
			value = new long double();
			ss >> *reinterpret_cast<long double*>(value);
		}
	}
	else if (type == "bool")
		value = new bool(svalue == "true");
	else if (type == "unknown_pointer")
		value = Str::toPtr(svalue);
}

void Object::StringFromValue() {
	if (type == "bool")
		svalue = *reinterpret_cast<bool*>(value) ? "true" : "false";
	else if (IsNumber()) {
		stringstream ss;
		if (type == "float")
			ss << *reinterpret_cast<long double*>(value);
		else if (type == "int")
			ss << *reinterpret_cast<long int*>(value);
		ss >> svalue;
	}
	else if (type == "string")
		svalue = *reinterpret_cast<string*>(value);
}

void Object::FindType() {
	if (value == nullptr && svalue == "null")
		type = "null";
	else if (svalue == "true" || svalue == "false")
		type = "bool";
	else if (Str::isNumeric(svalue)) {
		if (svalue.find(".") == string::npos)
			type = "int";
		else
			type = "float";
	}
	else if (Str::startsWith(svalue, "0x") && Str::isHexNumeric(svalue.substr(2)))
		type = "unknown_pointer";
	else
		type = "string";
}

Object::Object(string svalue, void* value, string type, bool constant) {
	this->constant = constant;
	this->svalue = svalue;
	this->type = type;
	this->value = value;
	krefs = 1;

	if (type == "auto")
		FindType();
	if (svalue.size() == 0 && this->value)
		StringFromValue();
	if (!this->value)
		ValueFromString();
}

Object::~Object() {
	auto _ = (string*)value;
	if (type != "null" && type != "unknown_pointer" && value)
		if (type == "string")
			delete (string*)value;
}

void* Object::Eval() {
	if (Str::startsWith(type, "*"))
		return Str::toPtr(SEval());
	return nullptr;
}
string Object::SEval() {
	return svalue;
}

string Object::GetType() {
	return type;
}
void Object::SetType(string type) {
	this->type = type;
	if (type == "auto")
		FindType();
}

bool Object::SetValue(void* value, string type) {
	this->value = value;
	SetType(type);
	return true;
}

bool Object::GetReAssign() {
   /* if (constant)
		throw ConstReAssign();*/
	return !constant;
}

bool Object::IsNumber() {
	return this->type == "int" || this->type == "float"/* || this->type == "bool"*/;
}

size_t Object::GetKRefs() {
	return krefs;
}

void Object::AddRef() {
	krefs++;
}

void Object::RemoveRef() {
	if (krefs > 0)
		krefs--;
}

Object* Object::operator+(Object& other) {
	void* t;
	if (IsNumber() && other.IsNumber()) {
		if (type == "int" && other.type == "int") {
			t = new long int(*reinterpret_cast<long int*>(value) + *reinterpret_cast<long int*>(other.value));
			delete reinterpret_cast<long long*>(value);
		}
		else {
			t = new long double((long double)*reinterpret_cast<long int*>(value) + (long double)*reinterpret_cast<long int*>(other.value));
			if (type == "float")
				delete reinterpret_cast<long double*>(value);
			else
				delete reinterpret_cast<long long*>(value);
			type = "float";
		}
	}
	else {
		string s1 = SEval(), s2 = other.SEval();
		t = new string(SEval() + other.SEval());
		if (value)
			delete reinterpret_cast<string*>(value); // mmm, unsafe
	}
	value = t;
	auto tt = (string*)value;
	StringFromValue();

	return this;
}