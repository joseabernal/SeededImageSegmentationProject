#include "userinputexception.h"

UserInputException::UserInputException(const string& messageIn) 
    : Exception("UserInputException", messageIn) {}