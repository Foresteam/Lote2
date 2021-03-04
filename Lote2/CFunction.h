#pragma once
#include "Function.h"
#include "Runtime.h"
typedef void (*lfunction)(Scope*);


class CFunction : public Function {
private:
	lfunction eval;
public:
	CFunction(string name, lfunction eval) : Function(name, 0, 0) {
		this->eval = eval;
	}


	void* Eval() override;

	static void Register(string name, lfunction eval);
	static void Init();
};