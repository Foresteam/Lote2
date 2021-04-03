#pragma once
#include <string>
#include <vector>
#include <list>
#include <sstream>
using namespace std;

namespace Str {
	const static string hexAlph = "0123456789ABCDEF";

	void replaceAll(string& str, string what, string with);
	vector<string> split(string str, string by);
	bool startsWith(string what, string with);
	bool endsWith(string what, string with);
	string join(list<string> what, string with);
	bool isNumeric(string what);
	bool isHexNumeric(string what);
	string fromPtr(void* p);
	void* toPtr(string s);
}