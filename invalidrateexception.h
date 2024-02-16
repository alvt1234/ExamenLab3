// invalidrateexception.h
#ifndef INVALIDRATEEXCEPTION_H
#define INVALIDRATEEXCEPTION_H

#include <stdexcept>
#include <string>

class InvalidRateException : public std::invalid_argument {
public:
    InvalidRateException(int rate);
};

#endif // INVALIDRATEEXCEPTION_H
