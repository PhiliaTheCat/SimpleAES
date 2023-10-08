#include <iostream>

#include "../include/Key"
#include "../include/Block"
#include "../include/AESAlgo"
#include "../include/SimpleAES"

using namespace std;
using namespace ptc;

int main()
{
    char msg[33];
    char key[33];
    char res[33];
    cin >> msg >> key;
    Encryption(msg, key, res);
    return 0;
}

void ptc::Encryption(const char msg[33], const char key[33], char res[33])
{
    Block m(msg);
    Key k(key);
    Key arr[11];
    arr[0] = k;
    for (int i = 1; i <= 10; i += 1)
        arr[i] = arr[i - 1].Get_New_Key(i);
    m = AddRndKey(m, arr[0]);
    for (int i = 1; i <= 9; i += 1)
        m = Round(m, arr[i]);
    m = FinalRound(m, arr[10]);
    m.ToStr(res);
    cout << res << endl;
    return;
}
