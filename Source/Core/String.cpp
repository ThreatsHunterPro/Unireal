#include "String.h"

#include <cstring>

String::String()
{
    buffer = nullptr;
    length = 0;
}

String::String(const char* _string)
{
    buffer = nullptr;
    length = 0;

    if (_string)
    {
        length = strlen(_string);
        buffer = new char[length + 1];
        strcpy(buffer, _string);
    }
}

String::String(string _string)
{
    length = _string.length();
    buffer = new char[length + 1];
    strcpy(buffer, _string.c_str());
}

String::String(const String& _other)
{
    buffer = nullptr;
    length = _other.length;

    if (_other.buffer)
    {
        buffer = new char[length + 1];
        strcpy(buffer, _other.buffer);
    }
}

String::~String()
{
    // delete[] buffer;
}

String String::ToString(const char* _number)
{
    const char* GetData() const {
        return data;
    }

    std::string ToString() const {
        return std::string(data);
    }
}


String String::FromInt(int _number)
{
    return to_string(_number).c_str();
}

String String::FromDouble(double _number)
{
    return to_string(_number).c_str();
}