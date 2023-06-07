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
    String(std::string _string);
    String(const String& _other);
    ~String();

public:
    static String ToString(const char* _number);
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
        
        strcpy_s(_newBuffer, _newLength + 1, buffer);
        strcat_s(_newBuffer, _newLength + 1, _string);
        
        String _result(_newBuffer);
        delete[] _newBuffer;
        return _result;
    }
    String operator+(const String& _other) const
    {
        String _result;
        _result.length = length + _other.length;
        _result.buffer = new char[_result.length + 1];

        strcpy_s(_result.buffer, _result.length + 1, buffer);
        strcpy_s(_result.buffer + length, _result.length + 1, _other.buffer);

        return _result;
    }
    String& operator=(const char* _string)
    {
        delete[] buffer;
        length = strlen(_string);
        buffer = new char[length + 1];
        strcpy_s(buffer, length + 1, _string);

        return *this;
    }
    String& operator=(const std::string& _string)
    {
        delete[] buffer;
        length = _string.length();
        buffer = new char[length + 1];
        strcpy_s(buffer, length + 1, _string.c_str());

        return *this;
    }
    String& operator+=(const String& _other)
    {
        const size_t _newLenght = length + _other.length;
        char* _newBuffer = new char[_newLenght + 1];

        if (buffer)
        {
            strcpy_s(_newBuffer, _newLenght + 1, buffer);
            delete[] buffer;
        }

        strcpy_s(_newBuffer + length, _newLenght + 1, _other.buffer);

        buffer = _newBuffer;
        length = _newLenght;

        return *this;
    }
    bool operator==(const String& _other) const
    {
        return !strcmp(buffer, _other.buffer); 
    }
};