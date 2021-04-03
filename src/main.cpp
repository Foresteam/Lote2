#include <iostream>
#include <fstream>
#include "Runtime.h"
#include "Scope/Module.h"
#include "Lib/Utils.h"
#include "Object/Function/CFunction.h"
#include "subprocess.hpp"
using namespace std;

int main(int argc, char* argv[]) {
	string fileName = "../hello.lote";
	Module mainModule = Module("__main__", fileName);
	scopes.push_back(&mainModule);

	Operators::Init();
	CFunction::Init();

	mainModule.Exec(0);

	auto o = subprocess::check_output({ "ls" });
	cout << endl << o.buf.data() << endl;
}