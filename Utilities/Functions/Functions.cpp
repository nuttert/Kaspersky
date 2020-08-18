#include "Functions.hpp"

#include <stdio.h>
#include <ctype.h>
#include <iostream>
namespace utilities
{
    bool isLetter(int symbol)
    {
        return isalpha(symbol);
    }
} // namespace utilities