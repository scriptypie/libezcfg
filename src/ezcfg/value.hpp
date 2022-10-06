/** 
 * Copyright (R) scriptypie - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Krivenko (scriptypie) Slava <miracl303@mail.ru>, 6 October 2022
 */
#pragma once
#ifndef ezcfg__value_hpp
#define ezcfg__value_hpp

#include "base.hpp"
#include "numerics.hpp"

namespace ezcfg
{

struct value_t
{
    string _v;
    enum type_t
    {
        undefined, str, intnum, floatnum, boolean
    };
    type_t type;
    
    template<class T>
    T as() const { return T(-1); }

    value_t(const char* s, const uint32_t& t) : _v(s), type((type_t)t) {}
    value_t(const char* s) : _v(s)
    {
        if (isdigit(_v)) { type = intnum; return; }
        if (isfloat(_v)) { type = floatnum; return; }
        if (_v == "true" || _v == "false") { type = boolean; return; }
        type = str;
    }
    value_t(const int& s) : _v(std::to_string(s)), type(intnum) {}
    value_t(const double& s) : _v(std::to_string(s)), type(floatnum) {}
    value_t(const bool& s) : _v(std::to_string(s)), type(boolean) {}

    bool operator==(const value_t& b) const;

};  

std::ostream& operator<<(std::ostream& os, const value_t& v)
{
    return os << v._v;
}

static value_t nullvalue = value_t("null", value_t::undefined);

bool value_t::operator==(const value_t& b) const
{
    return _v == b._v;
}


template<>
const char* value_t::as<const char*>() const
{
    return (type == str) ? _v.c_str() : "<NaS>";
}

template<>
std::string value_t::as<std::string>() const
{
    return (type == str) ? _v : "<NaS>";
}

template<>
int value_t::as<int>() const
{
    return (type == intnum) ? atoi(_v.c_str()) : 0;
}

template<>
float value_t::as<float>() const
{
    return (type == floatnum) ? atof(_v.c_str()) : 0;
}

template<>
double value_t::as<double>() const
{
    return (type == floatnum) ? atof(_v.c_str()) : 0;
}

template<>
bool value_t::as<bool>() const
{
    return (type == boolean) ? ((_v == "true") ? true : false) : 0;
}

}

#endif
