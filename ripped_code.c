#include "includes.h"

bool ColorIsEqual(Color col1, Color col2)
{
    bool result = false;

    if ((col1.r == col2.r) && (col1.g == col2.g) && (col1.b == col2.b) && (col1.a == col2.a)) result = true;

    return result;
}