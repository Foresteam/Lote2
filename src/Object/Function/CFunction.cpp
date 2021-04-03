#include "CFunction.h"
#include <iostream>
#include <array>
#include <memory>
#include <stdexcept>
// #include "../../subprocess.hpp"

void CFunction::Register(string name, lfunction eval) {
	Function::Register(name, new CFunction(name, eval));
}

std::string shellRun(const char* cmd) {
	// subprocess::check_output()
	/* std::array<char, 128> buffer;
	std::string result;
	std::unique_ptr<FILE, decltype(&_pclose)> pipe(_popen(cmd, "r"), _pclose);
	if (!pipe) {
		throw std::runtime_error("popen() failed!");
	}
	while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
		result += buffer.data();
	} */
	return "result";
}

void CFunction::Init() {
	Register("print", [](Scope* s) {
		auto t = mainStack.Pop();
		cout << t->SEval() << endl;
		Runtime::DObject(t);
	});
	Register("printAll", [](Scope* s) {
		auto t = mainStack.Pop();
		string delimiter = t->SEval();
		Runtime::DObject(t);
		while (!mainStack.IsEmpty()) {
			t = mainStack.Pop();
			cout << t->SEval();
			Runtime::DObject(t);
			if (!mainStack.IsEmpty())
				cout << delimiter;
		}
		cout << endl;
	});
	Register("sDupRef", [](Scope* s) {
		(*mainStack.Peek())->AddRef();
		mainStack.Dup();
	});
	Register("sDup", [](Scope* s) {
		mainStack.Push(new Object(**mainStack.Peek()));
	});
	Register("sDrop", [](Scope* s) {
		Object* pobject = mainStack.Pop();
		Runtime::DObject(pobject);
	});
	Register("sRot", [](Scope* s) {
		mainStack.Rot();
	});
	Register("sSwap", [](Scope* s) {
		mainStack.Swap();
	});
	Register("sFlip", [](Scope* s) {
		mainStack.Flip();
	});
	Register("sIsEmpty", [](Scope* s) {
		bool* isEmpty = new bool(mainStack.IsEmpty());
		mainStack.Push(new Object(*isEmpty ? "true" : "false", isEmpty, "bool"));
	});
	Register("typeof", [](Scope* s) {
		auto t = mainStack.Pop();
		string type = t->GetType();
		Runtime::DObject(t);
		mainStack.Push(new Object(type, "string"));
	});
	Register("shellRun", [](Scope* s) {
		Object* pcmd = mainStack.Pop();
		string rs = shellRun(pcmd->SEval().c_str());
		mainStack.Push(new Object(rs));
		Runtime::DObject(pcmd);
	});
}

void* CFunction::Eval() {
	eval(origin);
	return nullptr;
}
