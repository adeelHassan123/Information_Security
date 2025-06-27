#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <string>

// Function to read plaintext from a specified file
std::string readPlaintextFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::string plaintext;

    if (inputFile) {
        std::getline(inputFile, plaintext);
        inputFile.close();
    } else {
        throw std::runtime_error("Error: Unable to open file: " + filename);
    }

    return plaintext;
}

// Function to read a key from a specified file
std::string readKeyFromFile(const std::string& filename) {
    std::ifstream inputFile(filename);
    std::string key;

    if (inputFile) {
        std::getline(inputFile, key);
        inputFile.close();
    } else {
        throw std::runtime_error("Error: Unable to open key file: " + filename);
    }

    return key;
}

// Function to split plaintext into 64-bit blocks
std::vector<std::string> desPlaintextBlock(const std::string& plaintext) {
    const size_t block_size = 8; // 8 bytes = 64 bits
    std::vector<std::string> blocks;

    size_t length = plaintext.length();

    // Loop through the plaintext in chunks of block_size
    for (size_t i = 0; i < length; i += block_size) {
        std::string block = plaintext.substr(i, block_size);

        // Pad with '0' if the last block is smaller than 8 bytes
        if (block.size() < block_size) {
            block.append(block_size - block.size(), '0');
        }

        blocks.push_back(block);
    }
    return blocks;
}

// Function to perform the initial permutation
std::bitset<64> desInitialPermutation(const std::bitset<64>& block) {
    std::bitset<64> permuted_block;
    int perm[64] = {58, 50, 42, 34, 26, 18, 10, 2,
                    60, 52, 44, 36, 28, 20, 12, 4,
                    62, 54, 46, 38, 30, 22, 14, 6,
                    64, 56, 48, 40, 32, 24, 16, 8,
                    57, 49, 41, 33, 25, 17, 9, 1,
                    59, 51, 43, 35, 27, 19, 11, 3,
                    61, 53, 45, 37, 29, 21, 13, 5,
                    63, 55, 47, 39, 31, 23, 15, 7};

    // Perform the initial permutation
    for (int i = 0; i < 64; i++) {
        permuted_block[i] = block[perm[i] - 1];
    }

    return permuted_block;
}

// Function to convert a string to a 64-bit bitset
std::bitset<64> stringToBitset64(const std::string& str) {
    std::bitset<64> bits;
    for (size_t i = 0; i < str.size(); i++) {
        for (int j = 0; j < 8; j++) {
            bits[i * 8 + j] = (str[i] >> (7 - j)) & 1; // Convert to bits
        }
    }
    return bits;
}

int main() {
    const std::string plaintextFile = "plainfile.txt";
    const std::string keyFile = "keyfile.txt";

    // Initialize a default file with test text
    std::ofstream outputFile(plaintextFile);
    if (outputFile) {
        outputFile << "hello how are youjhud"; // Example plaintext
        outputFile.close();
    } else {
        std::cerr << "Error: Unable to create default plaintext file!" << std::endl;
        return 1;
    }

    // Initialize a default file with an example key
    std::ofstream keyOutputFile(keyFile);
    if (keyOutputFile) {
        keyOutputFile << "mysecret"; // Example key (should be 8 characters for 64 bits)
        keyOutputFile.close();
    } else {
        std::cerr << "Error: Unable to create default key file!" << std::endl;
        return 1;
    }

    try {
        // Read plaintext from the file
        std::string plaintext = readPlaintextFromFile(plaintextFile);
        std::cout << "Plaintext: " << plaintext << std::endl;

        // Read key from the file
        std::string key = readKeyFromFile(keyFile);
        std::cout << "Key : " << key << std::endl;

        // Split the plaintext into 64-bit blocks
        std::vector<std::string> blocks = desPlaintextBlock(plaintext);

        // Process each block, perform DES initial permutation and print the result
        for (const auto& block : blocks) {
            // std::bitset<64> bitBlock = stringToBitset64(block);
            // std::bitset<64> permutedBlock = desInitialPermutation(bitBlock);

            // std::cout << "Original Block: " << block << "\n";
            // std::cout << "Permuted Block: " << permutedBlock << "\n\n";
        }
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}