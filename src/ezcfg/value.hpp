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

struct ConfigValue
{
    string m_string;
    union ConfigValueStoredData
    {
        int64_t int64;
        double  float64;
        bool    boolean;
    };
    ConfigValueStoredData m_data;
    enum ConfigValueDataType
    {
        UNDEFINED, STRINGVAR, INTNUM, FLOATNUM, BOOLEAN, INTVECTOR, FLOATVECTOR
    };
    ConfigValueDataType m_type;
    
    template<class T>
    T As() const { return T(-1); }

    template<class T>
    std::vector<T> AsPtr() const { return std::vector<T>(-1); }

    ConfigValue(const char* s, const uint32_t& t) : m_string(s), m_type((ConfigValueDataType)t) {}
    ConfigValue(const char* s) : m_string(s)
    {
        if (IsDigit(m_string)) { m_type = INTNUM; m_data.int64 = atoll(m_string.c_str()); return; }
        if (IsFloat(m_string)) { m_type = FLOATNUM; m_data.float64 = atof(m_string.c_str()); return; }
        if (m_string == "true" || m_string == "false") { m_type = BOOLEAN; m_data.boolean = m_string == "true" ? true : false; return; }
        m_type = STRINGVAR;
    }
    ConfigValue(const int& s) : m_type(INTNUM) { m_data.int64 = s; }
    ConfigValue(const double& s) : m_type(FLOATNUM) { m_data.float64 = s; }
    ConfigValue(const float& s) : m_type(FLOATNUM) { m_data.float64 = s; }
    ConfigValue(const bool& s) : m_type(BOOLEAN) { m_data.boolean = s; }
    ConfigValue(const std::vector<int>& iv) : m_type(INTVECTOR)
    {
        m_string = "(";
        for (size_t i = 0; i < iv.size(); i++)
        {
            m_string += std::to_string(iv[i]);
            if (i + 1 < iv.size())
                m_string += ",";
        }
        m_string += ")";
    }
    ConfigValue(const std::vector<float>& iv) : m_type(INTVECTOR)
    {
        m_string += "(";
        for (size_t i = 0; i < iv.size(); i++)
        {
            m_string += std::to_string(iv[i]);
            if (i + 1 < iv.size())
                m_string += ",";
        }
        m_string += ")";
    }
    ConfigValue(const std::vector<double>& iv) : m_type(FLOATVECTOR)
    {
        m_string += "(";
        for (size_t i = 0; i < iv.size(); i++)
        {
            m_string += std::to_string(iv[i]);
            if (i + 1 < iv.size())
                m_string += ",";
        }
        m_string += ")";
    }

    bool operator!=(const ConfigValue& b) const;

};  

std::ostream& operator<<(std::ostream& os, const ConfigValue& v)
{
    return os << v.m_string;
}

static ConfigValue nullvalue = ConfigValue("null", ConfigValue::UNDEFINED);

bool ConfigValue::operator!=(const ConfigValue& b) const
{
    return !(m_string == b.m_string);
}

template<>
const char* ConfigValue::As<const char*>() const
{
    return (m_type == STRINGVAR) ? m_string.c_str() : "<NaS>";
}

template<>
std::string ConfigValue::As<std::string>() const
{
    return (m_type == STRINGVAR) ? m_string : "<NaS>";
}

template<>
int ConfigValue::As<int>() const
{
    return (m_type == INTNUM) ? m_data.int64 : 0;
}

template<>
std::vector<float> ConfigValue::AsPtr<float>() const
{
    std::vector<float> tmp;
    std::string t;

    for (size_t i = 0; i < m_string.size(); i++)
    {
        if (m_string[i] == '(')
        {
            i += 1;
            while (i < m_string.size())
            {
                for (; i < m_string.size() && m_string[i] != 41 && m_string[i] != 44; i++)
                {
                    t += m_string[i];
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
std::vector<double> ConfigValue::AsPtr<double>() const
{
    std::vector<double> tmp;
    std::string t;

    for (size_t i = 0; i < m_string.size(); i++)
    {
        if (m_string[i] == '(')
        {
            i += 1;
            while (i < m_string.size())
            {
                for (; i < m_string.size() && m_string[i] != 41 && m_string[i] != 44; i++)
                {
                    t += m_string[i];
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
std::vector<int> ConfigValue::AsPtr<int>() const 
{
    std::vector<int> tmp;
    std::string t;

    for (size_t i = 0; i < m_string.size(); i++)
    {
        if (m_string[i] == '(')
        {
            i += 1;
            while (i < m_string.size())
            {
                for (; i < m_string.size() && m_string[i] != 41 && m_string[i] != 44; i++)
                {
                    t += m_string[i];
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
float ConfigValue::As<float>() const
{
    return (m_type == FLOATNUM) ? m_data.float64 : 0;
}

template<>
double ConfigValue::As<double>() const
{
    return (m_type == FLOATNUM) ? m_data.float64 : 0;
}

template<>
bool ConfigValue::As<bool>() const
{
    return (m_type == BOOLEAN) ? m_data.boolean : 0;
}

}

#endif
