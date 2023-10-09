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

    Block InvRound(const Block &src, const Key &key)
    {
        Block t1 = AddRndKey(src, key);
        Block t2 = InvMixRow(t1);
        Block t3 = InvShiftCol(t2);
        Block t4 = InvByteSub(t3);
        return t4;
    }

    Block InvFinalRound(const Block &src, const Key &key)
    {
        Block t1 = AddRndKey(src, key);
        Block t2 = InvShiftCol(t1);
        Block t3 = InvByteSub(t2);
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
            res.mat[i][0] = Mul(a1, 2) ^ Mul(a2, 3) ^ a3 ^ a4;
            res.mat[i][1] = a1 ^ Mul(a2, 2) ^ Mul(a3, 3) ^ a4;
            res.mat[i][2] = a1 ^ a2 ^ Mul(a3, 2) ^ Mul(a4, 3);
            res.mat[i][3] = Mul(a1, 3) ^ a2 ^ a3 ^ Mul(a4, 2);
        }
        return res;
    }

    Block InvByteSub(const Block &src)
    {
        Block res = src;
        for (int i = 0; i < 4; i += 1)
        {
            for (int j = 0; j < 4; j += 1)
                res.mat[i][j] = InvS[res.mat[i][j].to_ulong()];
        }
        return res;
    }

    Block InvShiftCol(const Block &src)
    {
        Block res = src;
        for (int i = 1; i < 4; i += 1)
        {
            res.mat[0][i] = src.mat[(4 - i) % 4][i];
            res.mat[1][i] = src.mat[(5 - i) % 4][i];
            res.mat[2][i] = src.mat[(6 - i) % 4][i];
            res.mat[3][i] = src.mat[(7 - i) % 4][i];
        }
        return res;
    }

    Block InvMixRow(const Block &src)
    {
        Block res;
        std::bitset<8> a1, a2, a3, a4;
        for (int i = 0; i < 4; i += 1)
        {
            a1 = src.mat[i][0];
            a2 = src.mat[i][1];
            a3 = src.mat[i][2];
            a4 = src.mat[i][3];
            res.mat[i][0] = Mul(a1, 14) ^ Mul(a2, 11) ^ Mul(a3, 13) ^ Mul(a4, 9);
            res.mat[i][1] = Mul(a1, 9) ^ Mul(a2, 14) ^ Mul(a3, 11) ^ Mul(a4, 13);
            res.mat[i][2] = Mul(a1, 13) ^ Mul(a2, 9) ^ Mul(a3, 14) ^ Mul(a4, 11);
            res.mat[i][3] = Mul(a1, 11) ^ Mul(a2, 13) ^ Mul(a3, 9) ^ Mul(a4, 14);
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

    std::bitset<8> Mulx(const std::bitset<8> &src)
    {
        std::bitset<8> res;
        res = src << 1;
        if (src[7])
            res ^= 0b00011011;
        return res;
    }

    std::bitset<8> Mul(const std::bitset<8> &src, int ind)
    {
        std::bitset<8> res = 0;
        std::bitset<8> a[8];
        a[0] = src;
        for (int i = 1; i < 8; i += 1)
            a[i] = Mulx(a[i - 1]);
        for (int i = 0; i < 8; i += 1)
        {
            if (ind % 2 == 1)
                res ^= a[i];
            ind /= 2;
        }
        return res;
    }
}
