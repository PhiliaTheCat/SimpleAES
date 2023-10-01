#include "../include/AESAlgo"

namespace ptc
{
    Block Round(const Block &src, const Key &key)
    {
        Block t1 = ByteSub(src);
        Block t2 = ShiftCol(t1);
        Block t3 = MixRow(t2);
        Block t4 = AddRndKey(t3, key);
        return t4;
    }

    Block FinalRound(const Block &src, const Key &key)
    {
        Block t1 = ByteSub(src);
        Block t2 = ShiftCol(t1);
        Block t3 = AddRndKey(t2, key);
        return t3;
    }

    Block ByteSub(const Block &src)
    {
        Block res = src;
        for (int i = 0; i < 4; i += 1)
        {
            for (int j = 0; j < 4; j += 1)
                res.mat[i][j] = S[res.mat[i][j].to_ulong()];
        }
        return res;
    }

    Block ShiftCol(const Block &src)
    {
        Block res = src;
        for (int i = 1; i < 4; i += 1)
        {
            res.mat[0][i] = src.mat[(0 + i) % 4][i];
            res.mat[1][i] = src.mat[(1 + i) % 4][i];
            res.mat[2][i] = src.mat[(2 + i) % 4][i];
            res.mat[3][i] = src.mat[(3 + i) % 4][i];
        }
        return res;
    }

    Block MixRow(const Block &src)
    {
        Block res;
        for (int i = 0; i < 4; i += 1)
        {
            int t1 = ToInt(src.mat[i][0]);
            int t2 = ToInt(src.mat[i][1]);
            int t3 = ToInt(src.mat[i][2]);
            int t4 = ToInt(src.mat[i][3]);
            std::cout << t1 << t2 << t3 << t4 << std::endl;
            res.mat[i][0] = t1 * 2;
            res.mat[i][1] = t1 + t2 * 2;
            res.mat[i][2] = t1 + t2 + t3 * 2;
            res.mat[i][3] = t1 * 3 + t2 + t3 + t4 * 2;
        }
        char str[33];
        res.ToStr(str);
        std::cout << str << std::endl;
        return res;
    }

    Block AddRndKey(const Block &src, const Key &key)
    {
        Block res;
        for (int i = 0; i < 4; i += 1)
        {
            for (int j = 0; j < 4; j += 1)
                res.mat[i][j] = src.mat[i][j] ^ key.mat[i][j];
        }
        return res;
    }

    int ToInt(const std::bitset<8> &src)
    {
        int res = 0;
        for (int i = 7; i > -1; i -= 1)
        {
            res *= 2;
            res += src[i];
        }
        return res;
    }
}
