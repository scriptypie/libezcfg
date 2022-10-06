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
    union data_t
    {
        int64_t int64;
        double  float64;
        bool    boolean;
    };
    data_t data;
    enum type_t
    {
        undefined, str, intnum, floatnum, boolean, intvector, floatvector
    };
    type_t type;
    
    template<class T>
    T as() const { return T(-1); }

    template<class T>
    std::vector<T> as_ptr() const { return std::vector<T>(-1); }

    value_t(const char* s, const uint32_t& t) : _v(s), type((type_t)t) {}
    value_t(const char* s) : _v(s)
    {
        if (isdigit(_v)) { type = intnum; data.int64 = atoll(_v.c_str()); return; }
        if (isfloat(_v)) { type = floatnum; data.float64 = atof(_v.c_str()); return; }
        if (_v == "true" || _v == "false") { type = boolean; data.boolean = _v == "true" ? true : false; return; }
        type = str;
    }
    value_t(const int& s) : type(intnum) { data.int64 = s; }
    value_t(const double& s) : type(floatnum) { data.float64 = s; }
    value_t(const float& s) : type(floatnum) { data.float64 = s; }
    value_t(const bool& s) : type(boolean) { data.boolean = s; }
    value_t(const std::vector<int>& iv) : type(intvector)
    {
        _v = "(";
        for (size_t i = 0; i < iv.size(); i++)
        {
            _v += std::to_string(iv[i]);
            if (i + 1 < iv.size())
                _v += ",";
        }
        _v += ")";
    }
    value_t(const std::vector<float>& iv) : type(intvector)
    {
        _v += "(";
        for (size_t i = 0; i < iv.size(); i++)
        {
            _v += std::to_string(iv[i]);
            if (i + 1 < iv.size())
                _v += ",";
        }
        _v += ")";
    }
    value_t(const std::vector<double>& iv) : type(floatvector)
    {
        _v += "(";
        for (size_t i = 0; i < iv.size(); i++)
        {
            _v += std::to_string(iv[i]);
            if (i + 1 < iv.size())
                _v += ",";
        }
        _v += ")";
    }

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
    return (type == intnum) ? data.int64 : 0;
}

template<>
std::vector<float> value_t::as_ptr<float>() const
{
    std::vector<float> tmp;
    std::string t;

    for (size_t i = 0; i < _v.size(); i++)
    {
        if (_v[i] == '(')
        {
            i += 1;
            while (i < _v.size())
            {
                for (; i < _v.size() && _v[i] != 41 && _v[i] != 44; i++)
                {
                    t += _v[i];
                }
                tmp.push_back(atof(t.c_str()));
                t = "";
                i += 1;
            }
        }
    }
    return tmp;
}

template<>
std::vector<double> value_t::as_ptr<double>() const
{
    std::vector<double> tmp;
    std::string t;

    for (size_t i = 0; i < _v.size(); i++)
    {
        if (_v[i] == '(')
        {
            i += 1;
            while (i < _v.size())
            {
                for (; i < _v.size() && _v[i] != 41 && _v[i] != 44; i++)
                {
                    t += _v[i];
                }
                tmp.push_back(atof(t.c_str()));
                t = "";
                i += 1;
            }
        }
    }
    return tmp;
}

template<>
std::vector<int> value_t::as_ptr<int>() const 
{
    std::vector<int> tmp;
    std::string t;

    for (size_t i = 0; i < _v.size(); i++)
    {
        if (_v[i] == '(')
        {
            i += 1;
            while (i < _v.size())
            {
                for (; i < _v.size() && _v[i] != 41 && _v[i] != 44; i++)
                {
                    t += _v[i];
                }
                tmp.push_back(atoi(t.c_str()));
                t = "";
                i += 1;
            }
        }
    }
    return tmp;
}

template<>
float value_t::as<float>() const
{
    return (type == floatnum) ? data.float64 : 0;
}

template<>
double value_t::as<double>() const
{
    return (type == floatnum) ? data.float64 : 0;
}

template<>
bool value_t::as<bool>() const
{
    return (type == boolean) ? data.boolean : 0;
}

}

#endif
