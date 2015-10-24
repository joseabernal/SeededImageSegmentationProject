#include "mathexception.h"

MathException::MathException(const string& messageIn) 
    : Exception("MathException", messageIn) {}