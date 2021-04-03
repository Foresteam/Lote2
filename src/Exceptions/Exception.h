#pragma once
#include <string>
using namespace std;

class Exception : exception {
public:
	string what;
	Exception(string msg, string mname = "", string line = "") : exception() {
		what = "Exception: " + msg + ". Module: " + mname + ", line: " + line;
	}
};

class ConstReAssign : Exception {
public:
	ConstReAssign() : Exception("tried to re-assign a constant value") { throw *this; }
};
class EmptyStack : Exception {
public:
	EmptyStack() : Exception("the stack was empty") { throw *this; }
};
class NullReference : Exception {
public:
	NullReference() : Exception("null reference") { throw *this; }
};
class AlreadyDefined : Exception {
public:
	AlreadyDefined() : Exception("already defined in the scope") { throw *this; }
	string msg = "already defined in the scope";
};