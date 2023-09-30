#include <bitset>

#include "../include/AESAlgo"

namespace ptc
{
    Block Round(const Block &src, const Key &key)
    {
        Block t1 = ByteSub(src);
        Block t2 = ShiftCol(src);
        Block t3 = MixRow(src);
        Block t4 = AddRndKey(src, key);
    }
}
