#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

string preprocessText(string text) {
    string result;
    for (char ch : text) {
        if (isalpha(ch)) {
            result.push_back(tolower(ch));  // Keep only alphabets and convert to lowercase
        }
    }
    return result;
}

string encryptRailFence(string text, int key) {
    if (key == 1) {
        return text;
    }

    char rail[key][text.length()];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            rail[i][j] = '\n';

    bool dir_down = false;
    int row = 0, col = 0;

    for (int i = 0; i < text.length(); i++) {
        if (row == 0 || row == key - 1)
            dir_down = !dir_down;
        rail[row][col++] = text[i];
        dir_down ? row++ : row--;
    }

    string result;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < text.length(); j++)
            if (rail[i][j] != '\n')
                result.push_back(rail[i][j]);

    return result;
}

string decryptRailFence(string cipher, int key) {
    if (key == 1) {
        return cipher;
    }

    char rail[key][cipher.length()];
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            rail[i][j] = '\n';

    bool dir_down;
    int row = 0, col = 0;

    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;
        rail[row][col++] = '*';
        dir_down ? row++ : row--;
    }

    int index = 0;
    for (int i = 0; i < key; i++)
        for (int j = 0; j < cipher.length(); j++)
            if (rail[i][j] == '*' && index < cipher.length())
                rail[i][j] = cipher[index++];

    string result;
    row = 0, col = 0;
    for (int i = 0; i < cipher.length(); i++) {
        if (row == 0)
            dir_down = true;
        if (row == key - 1)
            dir_down = false;
        if (rail[row][col] != '*')
            result.push_back(rail[row][col++]);
        dir_down ? row++ : row--;
    }

    return result;
}

int main() {
    int choice, key;
    string text, processedText;

    cout << "Enter 1 for Encryption or 2 for Decryption: ";
    cin >> choice;
    cin.ignore();  // To consume the newline character after entering choice

    if (choice == 1) {
        cout << "Enter the plain text: ";
        getline(cin, text);
        processedText = preprocessText(text);
        cout << "Enter the key: ";
        cin >> key;
        string encryptedText = encryptRailFence(processedText, key);
        cout << "Encrypted Text: " << encryptedText << endl;
    } else if (choice == 2) {
        cout << "Enter the cipher text: ";
        getline(cin, text);
        cout << "Enter the key: ";
        cin >> key;
        string decryptedText = decryptRailFence(text, key);
        cout << "Decrypted Text: " << decryptedText << endl;
    } else {
        cout << "Invalid choice!" << endl;
    }

    return 0;
}
