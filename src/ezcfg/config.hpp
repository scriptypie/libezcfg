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

typedef std::pair<VariableName, ConfigValue> VariableDefinition;
typedef std::vector<VariableDefinition> ConfigDictionary;

class Config
{
    ConfigDictionary dictionary;
public:
    Config() {}
    ~Config() {}

    void SaveToFile(const string& filename);
    void SaveToMemory(string& data);
    void LoadFromFile(const string& filename);
    void LoadFromMemory(const string& data);
    void Set(const VariableName& name, const ConfigValue& value);
    const ConfigValue Find(const VariableName& name);
    inline const ConfigValue Get(const VariableName& name) { return Find(name); }
private:
    ConfigValue& FindVarRef(const VariableName& name);
};

void Config::Set(const VariableName& name, const ConfigValue& value)
{
    ConfigValue& val = FindVarRef(name);
    if (val != nullvalue) 
    {
        val = value;
        return;
    }
    VariableDefinition def(name, value);
    dictionary.push_back(def);
}

const ConfigValue Config::Find(const VariableName& name)
{
    for (size_t i = 0; i < dictionary.size(); i++)
        if (dictionary[i].first == name)
            return dictionary[i].second;
    return nullvalue;
}

ConfigValue& Config::FindVarRef(const VariableName& name)
{
    for (size_t i = 0; i < dictionary.size(); i++)
        if (dictionary[i].first == name)
            return dictionary[i].second;
    return nullvalue;
}

void Config::SaveToFile(const string& filename)
{
    std::ofstream f(filename + ".ezcfg", std::ios::binary);
    if (f.is_open())
    {
        std::stringstream ss;
        for (size_t i = 0; i < dictionary.size(); i++)
        {
            if (dictionary[i].second.m_type == ConfigValue::INTNUM)
                ss << dictionary[i].first << " = " << dictionary[i].second.m_data.int64 << std::endl;
            else
            if (dictionary[i].second.m_type == ConfigValue::FLOATNUM)
                ss << dictionary[i].first << " = " << dictionary[i].second.m_data.float64 << std::endl;
            else
            if (dictionary[i].second.m_type == ConfigValue::BOOLEAN)
                ss << dictionary[i].first << " = " << (dictionary[i].second.m_data.boolean ? "true" : "false") << std::endl;
            else
                ss << dictionary[i].first << " = " << dictionary[i].second << std::endl;
        }
        f << ss.str();
        f.close();
    }
}

void Config::SaveToMemory(string& data)
{
    if (!dictionary.empty())
    {
        std::stringstream ss;
        for (size_t i = 0; i < dictionary.size(); i++)
        {
            if (dictionary[i].second.m_type == ConfigValue::INTNUM)
                ss << dictionary[i].first << " = " << dictionary[i].second.m_data.int64 << std::endl;
            else
            if (dictionary[i].second.m_type == ConfigValue::FLOATNUM)
                ss << dictionary[i].first << " = " << dictionary[i].second.m_data.float64 << std::endl;
            else
            if (dictionary[i].second.m_type == ConfigValue::BOOLEAN)
                ss << dictionary[i].first << " = " << (dictionary[i].second.m_data.boolean ? "true" : "false") << std::endl;
            else
                ss << dictionary[i].first << " = " << dictionary[i].second << std::endl;
        }
        data = ss.str();
        ss.clear();
    }
}

void Config::LoadFromFile(const string& filename)
{
    std::ifstream f(filename + ".ezcfg", std::ios::binary);
    if (f.is_open())
    {
        dictionary.clear();
        char equal[3] = {' ', '=', ' '};
        VariableName name, valuestr;
        while (f >> name >> equal >> valuestr)
        {
            ConfigValue value(valuestr.c_str());
            VariableDefinition pair(name, value);
            dictionary.push_back(pair);
        }
        f.close();
    }
}

void Config::LoadFromMemory(const string& data)
{
    if (!data.empty())
    {
        std::stringstream ss(data.c_str());
        dictionary.clear();
        char equal[3] = {' ', '=', ' '};
        VariableName name, valuestr;
        while (ss >> name >> equal >> valuestr)
        {
            ConfigValue value(valuestr.c_str());
            VariableDefinition pair(name, value);
            dictionary.push_back(pair);
        }
        ss.clear();
    }
}

}

#endif
