#include "Utilities.hpp"
#include <stdio.h>
#include <ctype.h>

namespace utilities{
    bool isLetter(int symbol){
        return isalpha(symbol) || 
               (symbol >= 1040 && symbol <= 1103) ||
               symbol == 1025;
    }
}