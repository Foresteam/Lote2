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
	else {
		stringstream ss;
		if (type == "float")
			ss << *reinterpret_cast<long double*>(value);
		else if (type == "int")
			ss << *reinterpret_cast<long int*>(value);
		else if (type == "string")
			ss << *reinterpret_cast<string*>(value);
		ss >> svalue;
	}
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
	krefs = 0;

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

void* Object::Eval(bool toStack) {
	return nullptr;
}
string Object::SEval(bool toStack) {
	return svalue;
}

string Object::GetType() {
	return type;
}

void* Object::GetModigy() {
	return value;
}

void* Object::GetReAssign() {
   /* if (constant)
		throw ConstReAssign();*/
	return constant ? value : nullptr;
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
		if (value)
			delete reinterpret_cast<string*>(value); // mmm, unsafe
		t = new string(SEval() + other.SEval());
		StringFromValue();
	}
	value = t;
	StringFromValue();

	return this;
}
Object* Object::operator-(Object& other) {
	Object* result;
	if (IsNumber() && other.IsNumber()) {
		if (type == "int" && other.type == "int")
			result = new Object("", new long int(*reinterpret_cast<long int*>(value) - *reinterpret_cast<long int*>(other.value)), "int");
		else
			result = new Object("", new long double((long double)*reinterpret_cast<long int*>(value) - (long double)*reinterpret_cast<long int*>(other.value)), "float");
	}
	else if (svalue.size() >= other.svalue.size())
		result = new Object(svalue.substr(0, svalue.size() - other.svalue.size()));
	else
		result = new Object("", nullptr, "string");
	return result;
}
Object* Object::operator*(Object& other) {
	Object* result;
	if (IsNumber() && other.IsNumber()) {
		if (type == "int" && other.type == "int")
			result = new Object("", new long int(*reinterpret_cast<long int*>(value) * *reinterpret_cast<long int*>(other.value)), "int");
		else
			result = new Object("", new long double((long double)*reinterpret_cast<long int*>(value) * (long double)*reinterpret_cast<long int*>(other.value)), "float");
	}
	else {
		string nvalue = "";
		for (size_t i = 0; i < (other.type == "int" ? *reinterpret_cast<long int*>(other.value) : other.svalue.size()); i++)
			nvalue += svalue;
		result = new Object(nvalue, nullptr, "string");
	}
	return result;
}
