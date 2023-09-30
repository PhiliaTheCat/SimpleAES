#include <iostream>

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
                tar += str[i] - 'A' + 10;
            mat[i / 2 / 4][i / 2 % 4] = tar;
        }
    }
}
