#ifndef USER_INPUT_EXCEPTION_H
#define USER_INPUT_EXCEPTION_H

#include <string>

#include "exception.h"

using std::string;

/**
 * This class represents the exceptions that have place when the inputs are
 * not the expected.
 *
 * @author Jose Bernal
 */
class UserInputException : public Exception
{
    public:

        /**
         * Default constructor of the class
         *
         * @param message Message to display
         */
        UserInputException(const string& message);
};

#endif