#include <iostream>

#include "../include/Key"

namespace ptc
{
    Key::Key(const char str[33])
    {
        for (int i = 0; i < 32; i += 2)
        {
            int tar = 0;
            if (str[i] >= '0' && str[i] <= '9')
                tar += (str[i] - '0') * 16;
            else if (str[i] >= 'A' && str[i] <= 'F')
                tar += (str[i] - 'A' + 10) * 16;
            if (str[i + 1] >= '0' && str[i + 1] <= '9')
                tar += str[i + 1] - '0';
            else if (str[i + 1] >= 'A' && str[i + 1] <= 'F')
                tar += str[i + 1] - 'A' + 10;
            mat[i / 2 / 4][i / 2 % 4] = tar;
        }
    }

    Key::Key(const Key &src)
    {
        for (int i = 0; i < 4; i += 1)
        {
            for (int j = 0; j < 4; j += 1)
                mat[i][j] = src.mat[i][j];
        }
    }

    Key Key::Get_New_Key(const int &iter) const
    {
        Key res;
        std::bitset<8> t[4];
        // Get previous byte
        for (int i = 0; i < 4; i += 1)
            t[i] = mat[3][i];
        // Left Rotation
        std::bitset<8> tmp = t[0];
        t[0] = t[1];
        t[1] = t[2];
        t[2] = t[3];
        t[3] = tmp;
        // S Box
        for (int i = 0; i < 4; i += 1)
            t[i] = S[t[i].to_ulong()];
        // Xor first byte with Rcon
        t[0] ^= Rcon[iter];
        // Xor t with first 4 bytes of previous key, stored in res
        for (int i = 0; i < 4; i += 1)
            res.mat[0][i] = t[i] ^ mat[0][i];
        // Remaining
        for (int i = 1; i < 4; i += 1)
        {
            for (int j = 0; j < 4; j += 1)
                res.mat[i][j] = res.mat[i - 1][j] ^ mat[i][j];
        }
        return res;
    }

    void Key::ToStr(char res[33]) const
    {
        int cnt = 0, sum = 0, p = 0;
        for (int i = 0; i < 4; i += 1)
        {
            for (int j = 0; j < 4; j += 1)
            {
                for (int k = 7; k > -1; k -= 1)
                {
                    sum *= 2;
                    sum += mat[i][j][k];
                    cnt += 1;
                    if (cnt == 4)
                    {
                        if (sum >= 0 && sum <= 9)
                            res[p] = '0' + sum;
                        else if (sum >= 10 && sum <= 15)
                            res[p] = 'A' + sum - 10;
                        cnt = 0;
                        sum = 0;
                        p += 1;
                    }
                }
            }
        }
        res[p] = 0;
        return;
    }
}
