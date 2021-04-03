#include "Utils.h"
#include <cmath>
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

string Str::fromPtr(void* p) {
	string r;
	stringstream ss;
	ss << p;
	ss >> r;
	return "0x" + r;
}

void* Str::toPtr(string s) {
	s.erase(0, 2);
	unsigned int t = 0;

	auto it = s.end();
	int i = 0;
	do {
		it--;
		for (int j = 0; j < 16; j++)
			if (*it == hexAlph[j]) {
				t += j * pow(16, i);
				break;
			}
		i++;
	} while (it != s.begin());

	return reinterpret_cast<void*>(t);
}

bool Str::isNumeric(string what) {
	const string numchars = "0123456789.";
	for (char c : what)
		if (numchars.find(c) == string::npos)
			return false;
	return true;
}

bool Str::isHexNumeric(string what) {
	for (char c : what)
		if (hexAlph.find(c) == string::npos)
			return false;
	return true;
}
