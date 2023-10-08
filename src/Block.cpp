#include "../include/Block"

namespace ptc
{
    Block::Block(const char str[33])
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

    Block::Block(const Block &rhs)
    {
        for (int i = 0; i < 4; i += 1)
        {
            for (int j = 0; j < 4; j += 1)
                mat[i][j] = rhs.mat[i][j];
        }
    }

    void Block::ToStr(char res[33]) const
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
