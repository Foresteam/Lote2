#pragma once
#include <string>
using namespace std;

class Exception {
protected:
	string msg;
public:
	Exception() {
		throw exception(("Exception: " + msg).c_str());
	}
};

class ConstReAssign : Exception {
protected:
	string msg = "tried to re-assign a constant value";
};
class EmptyStack : Exception {
protected:
	string msg = "tried to re-assign a constant value";
};
class NullReference : Exception {
protected:
	string msg = "null reference";
};
class AlreadyDefined : Exception {
protected:
	string msg = "already defined in the scope";
};