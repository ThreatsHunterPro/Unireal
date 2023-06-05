#pragma once
#include "Macros.h"

class String
{
    char* buffer;
    size_t length;
    
public:
    FORCEINLINE size_t Lenght() const { return length; }
    
public:
    String();
    String(const char* _string);
    String(string _string);
    String(const String& _other);
    ~String();

public:
    static String FromInt(int _number);
    static String FromDouble(double _number);
    
public:
    operator const char*() const
    {
        return buffer;
    }
    String operator+(const char* _string) const
    {
        const size_t _length = std::strlen(_string);
        const size_t _newLength = length + _length;
        char* _newBuffer = new char[_newLength + 1];
        
        std::strcpy(_newBuffer, buffer);
        std::strcat(_newBuffer, _string);
        
        String _result(_newBuffer);
        delete[] _newBuffer;
        return _result;
    }
    String operator+(const String& _other) const
    {
        String _result;
        _result.length = length + _other.length;
        _result.buffer = new char[_result.length + 1];

        strcpy(_result.buffer, buffer);
        strcpy(_result.buffer + length, _other.buffer);

        return _result;
    }
    String& operator=(const char* _string)
    {
        if (buffer)
        {
            delete[] buffer;
        }

        length = strlen(_string);
        buffer = new char[length + 1];
        strcpy(buffer, _string);

        return *this;
    }
    String& operator=(const string& _string)
    {
        if (buffer)
        {
            delete[] buffer;
        }

        length = _string.length();
        buffer = new char[length + 1];
        strcpy(buffer, _string.c_str());

        return *this;
    }
    String& operator+=(const String& _other)
    {
        const size_t _newLenght = length + _other.length;
        char* _newBuffer = new char[_newLenght + 1];

        if (buffer)
        {
            strcpy(_newBuffer, buffer);
            delete[] buffer;
        }

        strcpy(_newBuffer + length, _other.buffer);

        buffer = _newBuffer;
        length = _newLenght;

        return *this;
    }
};