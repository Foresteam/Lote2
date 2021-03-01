#pragma once
#include <list>
#include "Stack.h"
#include "Object.h"
#include "Scope.h"
#include "Operator.h"

extern Stack<Object> mainStack;
extern list<Scope*> scopes;
extern list<Operator> operators;