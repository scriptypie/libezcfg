/** 
 * Copyright (R) scriptypie - All Rights Reserved
 *
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Krivenko (scriptypie) Slava <miracl303@mail.ru>, 6 October 2022
 */
#pragma once
#ifndef ezcfg__numerics_hpp
#define ezcfg__numerics_hpp

#include "base.hpp"

namespace ezcfg
{

bool isfloat(const string& s)
{
    char c;
    bool has_a_dot = false;
    for (size_t i = 0; i < s.size(); i++)
    {
        c = s.at(i);
        if (s.at(i) == 46) 
        {
            if (!has_a_dot)
            {
                has_a_dot = true;
                continue;
            }
            return false;
        }
        if (::isdigit(s.at(i))) { continue; }
        if (::isalpha(s.at(i))) return false;
        if (c == 32) continue;
    }
    return has_a_dot;
}

bool isdigit(const string& s)
{
    for (size_t i = 0; i < s.size(); i++)
        if (!::isdigit(s.at(i)))
            return false;
    return true;
}

}

#endif
