#include <stdbool.h>
#include "math.h"

bool is_square_number(u64 number)
{
    return (number & (number - 1)) == 0;
}

u64 get_next_square_number(u64 number)
{
    return (number - (number >> 1)) << 1;
}
