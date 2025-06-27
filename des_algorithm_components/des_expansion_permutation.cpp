#include <iostream>
#include <bitset>

using namespace std;

int expansionTable[48] = {32, 1, 2, 3, 4, 5,
                          4, 5, 6, 7, 8, 9,
                          8, 9, 10, 11, 12, 13,
                          12, 13, 14, 15, 16, 17,
                          16, 17, 18, 19, 20, 21,
                          20, 21, 22, 23, 24, 25,
                          24, 25, 26, 27, 28, 29,
                          28, 29, 30, 31, 32, 1};  

bitset<48> expansionPermutation(const bitset<32> &inputBlock)
{
    bitset<48> expandedBlock;  

    for (int i = 0; i < 48; i++)
    {
        expandedBlock[i] = inputBlock[expansionTable[i] - 1];  
    }

    return expandedBlock;  
}

void printInputBlock(const bitset<32>& inputBlock) {
    for (int i = 0; i < 32; i += 4) {
        cout << inputBlock.to_string().substr(i, 4) << " ";
    }
    cout << endl;
}

void printExpandedBlock(const bitset<48>& expandedBlock) {
    for (int i = 0; i < 48; i += 6) {
        cout << expandedBlock.to_string().substr(i, 6) << " ";
    }
    cout << endl;
}

int main()
{
    bitset<32> inputBlock(string("11001011001101010101010101110101"));
    // bitset<32> inputBlock(string("10101010101010101010101010101010"));
    //bitset<32> inputBlock(string("11111111111111111111111111111111"));
    //bitset<32> inputBlock(string("00000000000000000000000000000000"));



    bitset<48> expandedBlock = expansionPermutation(inputBlock);

    cout << "Input Block (32-bit): ";
    printInputBlock(inputBlock);

    cout << "Expanded Block (48-bit): ";
    printExpandedBlock(expandedBlock);

    return 0;
}
