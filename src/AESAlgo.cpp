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
        std::bitset<8> a1, a2, a3, a4;
        for (int i = 0; i < 4; i += 1)
        {
            a1 = src.mat[i][0];
            a2 = src.mat[i][1];
            a3 = src.mat[i][2];
            a4 = src.mat[i][3];
            res.mat[i][0] = Mul02(a1) ^ Mul03(a2) ^ a3 ^ a4;
            res.mat[i][1] = a1 ^ Mul02(a2) ^ Mul03(a3) ^ a4;
            res.mat[i][2] = a1 ^ a2 ^ Mul02(a3) ^ Mul03(a4);
            res.mat[i][3] = Mul03(a1) ^ a2 ^ a3 ^ Mul02(a4);
        }
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

    std::bitset<8> Mul02(const std::bitset<8> &src)
    {

        std::bitset<8> res;
        res = src << 1;
        if (src[7])
            res ^= 0b00011011;
        return res;
    }

    std::bitset<8> Mul03(const std::bitset<8> &src)
    {
        std::bitset<8> res;
        res = src << 1;
        if (src[7])
            res ^= 0b00011011;
        res ^= src;
        return res;
    }
}
