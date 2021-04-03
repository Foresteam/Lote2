#pragma once
#include <vector>
#include <string>
#include <list>
using namespace std;
typedef vector<string>::iterator vsi;
typedef bool (*Operator)(vsi&);

namespace Operators {
	void Init();
}