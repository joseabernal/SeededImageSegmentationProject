#include "exception.h"

Exception::Exception(const string& nameIn, const string& messageIn) 
    : name(nameIn), message(messageIn) {}