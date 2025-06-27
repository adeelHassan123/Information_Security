#include <iostream>
#include <bitset>

using namespace std;

bitset<28> desLeftShift(const bitset<28> &inputBlock, int round)
{
    bitset<28> shiftedBlock;

    int shiftAmount = (round == 1 || round == 2 || round == 9 || round == 16) ? 1 : 2;

    for (int i = 0; i < 28; i++)
    {
        shiftedBlock[i] = inputBlock[(i + shiftAmount) % 28];
    }

    return shiftedBlock;  
}

void printInPatches(const bitset<28> &block)
{
    string blockString = block.to_string();
    for (int i = 0; i < 28; i += 8)
    {
        cout << blockString.substr(i, 8) << " "; 
    }
    cout << endl;
}

int main()
{
    bitset<28> inputBlock(string("1101101010101001101100011100"));

    cout << "Input Block (28-bit): ";
    printInPatches(inputBlock);

    for (int round = 1; round <= 16; ++round)
    {
        bitset<28> shiftedBlock = desLeftShift(inputBlock, round);

        cout << "Round " << round << ": ";
        printInPatches(shiftedBlock);

        inputBlock = shiftedBlock;
    }

    return 0;
}
