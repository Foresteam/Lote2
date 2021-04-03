#include "Module.h"
#include "../Runtime.h"
#include <fstream>

Module::Module(string name, string fileName) {
	this->name = name;
	ifstream file(fileName.c_str());
	string tcontent;
	string line;
	while (file.is_open() && !file.eof()) {
		getline(file, line);
		if (!Str::startsWith(line, "--"))
			tcontent += line + ' ';
	}
	file.close();
	Str::replaceAll(tcontent, "\n", " ");
	Str::replaceAll(tcontent, "\t", "");
	code = Str::split(tcontent, " ");
}

void Module::Exec(size_t from, size_t to) {
	for (auto it = code.begin(); it != code.end(); it++) {
		for (auto op : operators)
			if (op(it))
				break;
	}
}
void Module::Exec(size_t from) {
	Exec(from, code.size());
}

void Module::Export(string name, Module another) {
	for (auto& pair : refs)
		another.refs.insert_or_assign(name + pair.first, pair.second);
}