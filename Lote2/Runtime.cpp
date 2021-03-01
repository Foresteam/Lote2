#include "Runtime.h"

Stack<Object> mainStack = Stack<Object>();
list<Scope*> scopes = list<Scope*>();
list<Operator> operators = list<Operator>();