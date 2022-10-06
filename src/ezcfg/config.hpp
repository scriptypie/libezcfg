/** 
 * Copyright (R) scriptypie - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Krivenko (scriptypie) Slava <miracl303@mail.ru>, 6 October 2022
 */
#pragma once
#ifndef ezcfg__config_hpp
#define ezcfg__config_hpp

#include <vector>
#include <utility>
#include <fstream>
#include <sstream>

#include "value.hpp"

namespace ezcfg
{

typedef std::pair<name_t, value_t> linepair_t;
typedef std::vector<linepair_t> dictionary_t;

class ezconfig
{
    dictionary_t dictionary;
public:
    ezconfig() {}
    ~ezconfig() {}

    void save(const string& filename);
    void load(const string& filename);
    void set(const name_t& name, const value_t& value);
    const value_t find(const name_t& name);
    inline const value_t get(const name_t& name) { return find(name); }
private:
    value_t& find_val(const name_t& name);
};

void ezconfig::set(const name_t& name, const value_t& value)
{
    linepair_t pair(name, value);
    value_t& tmp = find_val(name);
    if (tmp == nullvalue)
        dictionary.push_back(pair);
    else
        tmp = value;
}

const value_t ezconfig::find(const name_t& name)
{
    for (size_t i = 0; i < dictionary.size(); i++)
        if (dictionary[i].first == name)
            return dictionary[i].second;
    return nullvalue;
}

value_t& ezconfig::find_val(const name_t& name)
{
    for (size_t i = 0; i < dictionary.size(); i++)
        if (dictionary[i].first == name)
            return dictionary[i].second;
    return nullvalue;
}

void ezconfig::save(const string& filename)
{
    std::ofstream f(filename + ".ezcfg", std::ios::binary);
    if (f.is_open())
    {
        std::stringstream ss;
        for (size_t i = 0; i < dictionary.size(); i++)
        {
            ss << dictionary[i].first << " = " << dictionary[i].second << std::endl;
        }
        f << ss.str();
        f.close();
    }
}

void ezconfig::load(const string& filename)
{
    std::ifstream f(filename + ".ezcfg", std::ios::binary);
    if (f.is_open())
    {
        dictionary.clear();
        char equal[3] = {' ', '=', ' '};
        name_t name, valuestr;
        while (f >> name >> equal >> valuestr)
        {
            value_t value(valuestr.c_str());
            linepair_t pair(name, value);
            dictionary.push_back(pair);
        }
        f.close();
    }
}

}

#endif
