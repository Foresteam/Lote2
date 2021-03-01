#include "Utils.h"
#include <iostream>

void Str::replaceAll(string& str, string what, string with) {
	size_t pos;
	while ((pos = str.find(what)) != string::npos)
		str.replace(pos, what.size(), with);
}

vector<string> Str::split(string str, string by) {
	vector<string> result = vector<string>();

	size_t pos;
	while ((pos = str.find(by)) != string::npos) {
		result.push_back(str.substr(0, pos));
		str.erase(0, pos + 1);
	}
	if (str.size() > 0)
		result.push_back(str);

	return result;
}

bool Str::startsWith(string what, string with) {
	if (what.size() < with.size())
		return false;
	return what.substr(0, with.size()) == with;
}
bool Str::endsWith(string what, string with) {
	if (what.size() < with.size())
		return false;
	return what.substr(what.size() - with.size()) == with;
}

string Str::join(list<string> what, string with) {
	string result = "";
	for (auto it = what.begin(); it != what.end(); it++)
		result += *it + (it == what.rbegin().base() ? "" : " ");
	return result;
}
