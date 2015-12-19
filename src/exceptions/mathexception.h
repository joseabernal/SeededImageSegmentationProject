#ifndef MATH_EXCEPTION_H
#define MATH_EXCEPTION_H

#include <string>

#include "exception.h"

using std::string;

/**
 * This class represents the mathematical exceptions that have place in the app.
 *
 * @author Jose Bernal
 */
class MathException : public Exception
{
    public:
        
        /**
         * Default constructor of the class
         *
         * @param message Message to display
         */
        MathException(const string message);
};

#endif