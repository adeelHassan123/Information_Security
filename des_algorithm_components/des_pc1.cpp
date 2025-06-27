#include <iostream>
#include <bitset>

using namespace std;

int pc1Table[56] = {57, 49, 41, 33, 25, 17, 9,
                    1, 58, 50, 42, 34, 26, 18,
                    10, 2, 59, 51, 43, 35, 27,
                    19, 11, 3, 60, 52, 44, 36,
                    63, 55, 47, 39, 31, 23, 15,
                    7, 62, 54, 46, 38, 30, 22,
                    14, 6, 61, 53, 45, 37, 29,
                    21, 13, 5, 28, 20, 12, 4};

bitset<56> desPermutedChoice1(const bitset<64> &inputKey)
{
    bitset<56> permutedKey; 

    for (int i = 0; i < 56; i++)
    {
        permutedKey[i] = inputKey[pc1Table[i] - 1];  
    }

    return permutedKey;
}

void printPC1Table()
{
    cout << "PC1 Table (8x7 matrix):" << endl;
    for (int i = 0; i < 56; i++)
    {
        cout << pc1Table[i] << "\t";
        if ((i + 1) % 7 == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
}

void printInputBlock(const bitset<64>& inputBlock)
{
    cout << "Input Key (64-bit in 8x8 matrix):" << endl;
    for (int i = 63; i >= 0; i -= 8)
    {
        for (int j = 7; j >= 0; j--)
        {
            cout << inputBlock[i - j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
}

void printPermutedBlock(const bitset<56>& permutedBlock)
{
    cout << "Permuted Key (56-bit in 8x7 matrix):" << endl;
    for (int i = 55; i >= 0; i -= 7)
    {
        for (int j = 6; j >= 0; j--)
        {
            cout << permutedBlock[i - j]<<" ";
        }
        cout << endl;
    }
    cout << endl;
}

int main()
{
    bitset<64> inputKey(string("1010101101100000111010100110111010101010101101010101100110"));

    bitset<56> permutedKey = desPermutedChoice1(inputKey);

    printPC1Table();

    printInputBlock(inputKey);

    printPermutedBlock(permutedKey);

    return 0;
}
