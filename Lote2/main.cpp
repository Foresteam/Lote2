#include <iostream>
#include <fstream>
#include "Runtime.h"
#include "Module.h"
#include "Utils.h"
#include "CFunction.h"
using namespace std;

int main(int argc, char* argv[]) {
	string fileName = "../hello.lote";
	Module mainModule = Module("__main__", fileName);
	scopes.push_back(&mainModule);

	Operators::Init();
	CFunction::Init();

	mainModule.Exec(0);
}