//
// Created by Jack Huang on 15/8/21.
//

#include <iostream>
#include <algorithm>

#include "S-DES.h"

using namespace std;

void Encrypt(bool *plainText);

void Decrypt(bool *cipherText);

void Fk_func(bool *plainText, bool *tem4, const bool *key);

void S_func(const bool *in, bool *out);

void Left_shift(bool *in, int len_bit, int left_bit);

void Perm_func(bool *in, int size, const int *table);

void S_DES_run(bool type);

void Set_key(bool key[Key_Num]);

bool TransToBool(bool *out, int len, string &in);

void Xor(bool *in, const bool *key, int len);

int main() {
    int choice;
    while (true) {
        cout << "This is S-DES system.\n";
        cout << "1. Encrypt\n";
        cout << "2. Decrypt\n";
        cout << "3. exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                S_DES_run(encrypt);
                break;
            case 2:
                S_DES_run(decrypt);
                break;
            case 3:
                return 0;
            default:
                break;
        }
    }
}

void S_DES_run(bool type) {
    // Judgment symbol
    bool flag = false;
    string tem;
    bool plainText[Plaint_Num], key[Key_Num], ciphertext[Cipher_Num];
    do {
        cout << "Please enter the 10-bit key\n";
        cin >> tem;
        // Check if it meets the requirements, if it doesn't,
        // you can't get out of the loop.
        flag = TransToBool(key, Key_Num, tem);
    } while (flag);
    Set_key(key);

    if (type == encrypt) {
        do {
            cout << "\nPlease enter the 8-bit plaintext\n";
            cin >> tem;
            flag = TransToBool(plainText, Plaint_Num, tem);
        } while (flag);
        Encrypt(plainText);
    } else if (type == decrypt) {
        do {
            cout << "\nPlease enter the 8-bit ciphertext\n";
            cin >> tem;
            flag = TransToBool(ciphertext, Cipher_Num, tem);
        } while (flag);
        Decrypt(ciphertext);
    }

}

void Set_key(bool key[Key_Num]) {
    static bool tem[10];

    // P10
    Perm_func(key, 10, P10);

    cout << "\np10: ";
    for(int i = 0; i < 10; i++){
        cout << " "<< key[i];
    }

    // LS-1
    Left_shift(key, 5, 1);
    Left_shift(key + 5, 5, 1);

    cout << "\nLS1: ";
    for(int i = 0; i < 10; i++){
        cout << " "<< key[i];
    }

    // P8
    memcpy(tem, key, 10);
    Perm_func(tem, 10, P8);
    memcpy(k1, tem, 8);

    cout << "\nkey1: ";
    for(int i = 0; i < 8; i++){
        cout << " "<< k1[i];
    }

    // LS-2
    Left_shift(key, 5, 2);
    Left_shift(key + 5, 5, 2);

    cout << "\nLS-2: ";
    for(int i = 0; i < 10; i++){
        cout << " "<< key[i];
    }

    // P8
    Perm_func(key, 10, P8);
    memcpy(k2, key, 8);

    cout << "\nkey2: ";
    for(int i = 0; i < 8; i++){
        cout << " "<< k2[i];
    }

}

// Complete the position conversion between bits, according to
// the incoming table with different requirements.
void Perm_func(bool *in, int size, const int *table) {
    bool tem[size];
    memcpy(tem, in, size);
    for (int i = 0; i < size; i++) {
        in[i] = tem[table[i] - 1];
    }
}

void Left_shift(bool *in, int len_bit, int left_bit) {
    /* 12345    step 1
     * 23455    step 2
     * 23451    step 3 */
    bool tem[len_bit];
    memcpy(tem, in, len_bit); //step 1
    memcpy(in, tem + left_bit, len_bit - left_bit); //step 2
    memcpy(in + len_bit - left_bit, tem, left_bit); //step 3
}

void Encrypt(bool *plainText) {
    bool tem8[8], tem4[4];
    // IP
    Perm_func(plainText, 8, IP);

    cout << "\nIP: ";
    for(int i = 0; i < 8; i++){
        cout << " "<< plainText[i];
    }

    // FK
    Fk_func(plainText, tem4, k1);

    // Use the pointer to swap the front and rear 4 bits.
    // SW
    memcpy(tem8, plainText + 4, 4);
    memcpy(tem8 + 4, tem4, 4);

    cout << "\nSW: ";
    for(int i = 0; i < 8; i++){
        cout << " "<< tem8[i];
    }

    // FK
    Fk_func(tem8, tem4, k2);

    // IP-1
    memcpy(plainText, tem4, 4);
    memcpy(plainText + 4, tem8 + 4, 4);
    Perm_func(plainText, 8, IP_1);

    cout << "\nCiphertext: ";
    for (int i = 0; i < 8; i++) {
        cout << plainText[i];
    }
    cout << endl<<endl;


}


void Fk_func(bool *plainText, bool *tem4, const bool *key) {
    bool tem8[8];

    // E/P
    memcpy(tem8, plainText + 4, 4);
    Perm_func(tem8, 8, E_P);

    cout << "\nE/P: ";
    for(int i = 0; i < 8; i++){
        cout << " "<< tem8[i];
    }

    // Xor +
    Xor(tem8, key, 8);

    cout << "\nXOR: ";
    for(int i = 0; i < 8; i++){
        cout << " "<< tem8[i];
    }

    // S function
    S_func(tem8, tem4);

    cout << "\nS-BOX: ";
    for(int i = 0; i < 4; i++){
        cout << " "<< tem4[i];
    }

    // P4
    Perm_func(tem4, 4, P4);

    cout << "\nP4: ";
    for(int i = 0; i < 4; i++){
        cout << " "<< tem4[i];
    }

    // Xor +
    Xor(tem4, plainText, 4);

    cout << "\nXOR: ";
    for(int i = 0; i < 4; i++){
        cout << " "<< tem4[i];
    }
}

void S_func(const bool *in, bool *out) {
    int row, col;
    // S0
    // Because we need to determine the rows and columns, we need to convert binary to decimal.
    // Bi_to_Dec
    row = (int) *in * 2 + (int) *(in + 3) * 1;
    col = (int) *(in + 1) * 2 + (int) *(in + 2) * 1;

    // The result needs to be binary, so we convert it back.
    //Dec_to_bi
    *out = S0[row][col] / 2;
    *(out + 1) = S0[row][col] % 2;

    // S1
    // Bi_to_Dec
    row = (int) *(in + 4) * 2 + (int) *(in + 7) * 1;
    col = (int) *(in + 5) * 2 + (int) *(in + 6) * 1;
    // Dec_to_bi
    *(out + 2) = S1[row][col] / 2;
    *(out + 3) = S1[row][col] % 2;

}


void Xor(bool *in, const bool *key, int len) {
    for (int i = 0; i < len; i++)
        in[i] ^= key[i];
}

void Decrypt(bool *cipherText) {
    bool tem8[8], tem4[4];
    // IP
    Perm_func(cipherText, 8, IP);

    // FK
    Fk_func(cipherText, tem4, k2);

    // SW
    memcpy(tem8, cipherText + 4, 4);
    memcpy(tem8 + 4, tem4, 4);

    // FK
    Fk_func(tem8, tem4, k1);

    // IP-1
    memcpy(cipherText, tem4, 4);
    memcpy(cipherText + 4, tem8 + 4, 4);
    Perm_func(cipherText, 8, IP_1);

    cout << "PlaintText: ";
    for (int i = 0; i < 8; i++) {
        cout << cipherText[i];
    }
    cout << endl<<endl;
}

// Because the input is binary, for convenience and saving space, I converted the data to bool type.
bool TransToBool(bool *out, int len, string &in) {
    char tem[len];
    // Check whether the length of the input characters meets the requirements.
    if (in.length() != len) {
        cout << "The input is incorrect, please input " << len << " digits.\n";
        return true;
    }
    // initialization
    in.copy(tem, len, 0);
    // Check whether the characters are 0 and 1 one by one, and if so, store them in out.
    for (int i = 0; i < len; i++) {
        if (tem[i] == '0' || tem[i] == '1')
            out[i] = tem[i] & 1;
        else {
            cout << "You entered is not 0 or 1, please enter again.\n";
            return true;
        }
    }
    return false;
}
