#include "Object.h"

void* Object::Eval(bool toStack) {
    return nullptr;
}
string Object::SEval(bool toStack) {
    return svalue;
}

void* Object::GetModigy() {
    return value;
}

void* Object::GetReAssign() {
   /* if (constant)
        throw ConstReAssign();*/
    return constant ? value : nullptr;
}

bool Object::IsNumber() {
    return this->type == "int" || this->type == "float"/* || this->type == "bool"*/;
}

Object Object::operator+(Object other) {
    Object result;
    if (IsNumber() && other.IsNumber()) {
        if (type == "int" && other.type == "int")
            result = Object("", new long int(*reinterpret_cast<long int*>(value) + *reinterpret_cast<long int*>(other.value)), "int");
        else {
            long double* sum = new long double();
            if (type == "float")
                *sum = *reinterpret_cast<long double*>(value);
            else
                *sum = (long double)*reinterpret_cast<long int*>(value);
            if (other.type == "float")
                *sum += *reinterpret_cast<long double*>(other.value);
            else
                *sum += (long double)*reinterpret_cast<long int*>(other.value);
            result = Object("", sum, "float");
        }
    }
    else
        result = Object(svalue + other.svalue);
    return result;
}
