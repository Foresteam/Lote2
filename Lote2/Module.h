#pragma once
#include <string>
#include <fstream>
#include "Utils.h"
#include "Scope.h"
#include <iostream>
using namespace std;

class Module : public Scope {
private:
	size_t pointer;
	vector<string> code;
	string name;
public:
	Module(string name, string fileName);
	void Exec(size_t from, size_t to);
	void Exec(size_t from);
	void Export(string moduleName, Module another);
};