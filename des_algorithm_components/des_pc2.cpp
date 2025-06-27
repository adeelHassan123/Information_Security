#include <iostream>
#include <bitset>

using namespace std;

int pc2Table[48] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

bitset<48> desPermutedChoice2(const bitset<56> &inputKey)
{
    bitset<48> permutedKey;

    for (int i = 0; i < 48; i++)
    {
        permutedKey[i] = inputKey[pc2Table[i] - 1];
    }

    return permutedKey; 
}

void printInMatrixInput(const bitset<56> &block)
{
    string blockString = block.to_string();
    cout << "Input Key (56-bit):\n";
    for (int i = 0; i < 56; i += 8)
    {
        cout << blockString.substr(i, 8)<< endl; 
    }
}

void printInMatrix(const bitset<48> &block)
{
    string blockString = block.to_string();
    cout << "Permuted Key (48-bit):\n";
    for (int i = 0; i < 48; i += 8)
    {
        cout << blockString.substr(i, 8) <<" " <<endl; 
    }
}

int main()
{
    bitset<56> inputKey(string("11010100110101010001111011001100101010101111010101010110011001")); // 56-bits

    bitset<48> permutedKey = desPermutedChoice2(inputKey);

    printInMatrixInput(inputKey);
    printInMatrix(permutedKey);

    return 0;
}
