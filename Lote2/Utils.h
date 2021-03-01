#pragma once
#include <string>
#include <vector>
#include <list>
using namespace std;

namespace Str {
	void replaceAll(string& str, string what, string with);
	vector<string> split(string str, string by);
	bool startsWith(string what, string with);
	bool endsWith(string what, string with);
	string join(list<string> what, string with);
}