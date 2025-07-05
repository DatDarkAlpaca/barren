#include <assert.h>
#include "memory_utils.h"
#include "utils/math.h"

u64 align(u64 index, u64 alignment)
{
    assert(is_square_number(alignment));

    u64 modulo = index & (alignment - 1);
    
    if (modulo == 0)
        return index;

    return index + alignment - modulo;
}
