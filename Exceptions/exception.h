#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

using std::string;

/**
 * This class represents the exceptions that can be in the app. Every exception
 * class should inherit from this one.
 *
 * @author Jose Bernal
 */
class Exception : public std::exception
{
    protected:
        
        /**
         * Name of the exception to display
         */
        const string name;

        /**
         * Message to display
         */
        const string message;

    public:

        /**
         * Default class constructor
         *
         * @param name Name of the exception
         * @param message Message to display
         */
        Exception(const string& name, const string& message);

        /**
         * Default destructor
         */
        virtual ~Exception() throw () {}

        /**
         * Inherited
         */
        virtual const char* what() const throw() {
            return (name + ": " + message).c_str();
        }
};

#endif