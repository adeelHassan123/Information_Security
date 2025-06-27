#include <iostream>
#include <cstring>
#include <string.h>
using namespace std;
#define SIZE 60

void toLowerCase(char plain[], int ps)
{
    int i;
    for (i = 0; i < ps; i++) {
        if (plain[i] >= 65 && plain[i] <= 90)  
            plain[i] += 32;
    }
}

int removeSpaces(char* plain, int ps)
{
    int i, count = 0;
    for (i = 0; i < ps; i++) {
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    }
    plain[count] = '\0';  
    return count;
}

void generateKeyTable(char key[], int ks, char keyT[5][5])
{
    int i, j, k;
    int used[26] = { 0 };

    for (i = 0; i < ks; i++) {
        if (key[i] != 'j')
            used[key[i] - 97] = 2;
    }

    used['j' - 97] = 1;

    i = 0;
    j = 0;

    for (k = 0; k < ks; k++) {
        if (used[key[k] - 97] == 2) {
            used[key[k] - 97] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
    for (k = 0; k < 26; k++) {
        if (used[k] == 0) {
            keyT[i][j] = (char)(k + 97);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

void search(char keyT[5][5], char a, char b, int arr[])
{
    int i, j;

    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

int mod5(int a) { return (a % 5); }

int prepare(char str[], int ptrs)
{
    if (ptrs % 2 != 0) {
        str[ptrs++] = 'z';  
        str[ptrs] = '\0';
    }
    return ptrs;
}

void encrypt(char str[], char keyT[5][5], int ps)
{
    int i, a[4];

    for (i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] + 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];
        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];
        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
    cout << "Cipher text: " << str << "\n";
}

void decrypt(char str[], char keyT[5][5], int ps)
{
    int i, a[4];

    for (i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] - 1 + 5)];
            str[i + 1] = keyT[a[0]][mod5(a[3] - 1 + 5)];
        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] - 1 + 5)][a[1]];
            str[i + 1] = keyT[mod5(a[2] - 1 + 5)][a[1]];
        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
        }
    }
    cout << "Deciphered text: " << str << "\n";
}

void cleanInput(char* input)
{
    int count = 0;
    for (int i = 0; input[i] != '\0'; i++) {
        if (isalpha(input[i])) {  
            input[count++] = input[i];
        }
    }
    input[count] = '\0';  
}

void encryptByPlayfairCipher(char str[], char key[])
{
    char ps, ks, keyT[5][5];

    cleanInput(key);
    ks = strlen(key);
    ks = removeSpaces(key, ks);
    toLowerCase(key, ks);

    cleanInput(str);
    ps = strlen(str);
    toLowerCase(str, ps);
    ps = removeSpaces(str, ps);
    ps = prepare(str, ps);

    generateKeyTable(key, ks, keyT);
    encrypt(str, keyT, ps);
    decrypt(str, keyT, ps);
}

int main()
{
    while(1)
    {
    cout<<endl;
    cout<<endl;

    char str[SIZE], key[SIZE];
    
    cout << "Enter the key: ";
    cin.getline(key, SIZE);

    cout << "Enter the plain text: ";
    cin.getline(str, SIZE);

    encryptByPlayfairCipher(str, key);
    }
}
