#include "Module.h"
#include "Runtime.h"
#include <fstream>

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