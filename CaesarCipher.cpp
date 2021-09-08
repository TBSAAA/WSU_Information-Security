//
// Created by Jack Huang on 25/7/21.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <stdio.h>
#include <fstream>

#define lettersNumber 26

using namespace std;

void ImportFile(string *);

void keyboardInput(string *);

void Encrypt(string *);

void Decrypt(string *);

void ExportFile(string *);

void ForceAttack(string *);

int main() {
    string str = "Hello word!";
    int choice;
    while (true) {
        cout << "The current string is: " << str << endl;
        cout << "This is Caesar Cipher.\n";
        cout << "1. Import from file\n";
        cout << "2. Keyboard input\n";
        cout << "3. Encrypt\n";
        cout << "4. Decrypt\n";
        cout << "5. Export to file\n";
        cout << "6. Brute-force attack\n";
        cout << "7. exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                ImportFile(&str);
                break;
            case 2:
                keyboardInput(&str);
                break;
            case 3:
                Encrypt(&str);
                break;
            case 4:
                Decrypt(&str);
                break;
            case 5:
                ExportFile(&str);
                break;
            case 6:
                ForceAttack(&str);
                break;
            case 7:
                return 0;
            default:
                break;
        }
    }
}

void ForceAttack(string *str){
    string::iterator it;
    for(int key = 0; key < lettersNumber; key++){
        for (it = str->begin(); it != str->end(); it++) {
            if (*it >= 'A' && *it <= 'Z') {
                *it = char(((*it - 'A') + key) % lettersNumber + 'A');
            } else if (*it >= 'a' && *it <= 'z') {
                *it = char(((*it - 'a') + key) % lettersNumber + 'a');
            }
        }
        cout << key <<": "<< *str<<endl;
    }

}

void ExportFile(string *str) {
    ofstream fout;
    fout.open("data_out.txt");
    if (fout.fail()) {
        cout << "Output file opening failed.\n";
        exit(1);
    }
    fout << *str;
    fout.close();
}

void ImportFile(string *str) {
    ifstream fin;
    fin.open("data_in.txt");
    if (fin.fail()) {
        cout << "Input file opening failed.\n";
        exit(1);
    }
    *str = "";
    string word;
    fin >> word;
    *str += word;
    while (!fin.eof()) {
        fin >> word;
        *str += " "+word;
    }
    fin.close();
}

void keyboardInput(string *str) {
    cout << "Please enter the string: ";
    getline(cin, *str);
    getline(cin, *str);
}

void Encrypt(string *str) {
    int key;
    cout << "Please enter the key: ";
    cin >> key;
    string::iterator it;
    for (it = str->begin(); it != str->end(); it++) {
        if (*it >= 'A' && *it <= 'Z') {
            *it = char(((*it - 'A') + key) % lettersNumber + 'A');
        } else if (*it >= 'a' && *it <= 'z') {
            *it = char(((*it - 'a') + key) % lettersNumber + 'a');
        }
    }
}

void Decrypt(string *str) {
    int key;
    cout << "Please enter the key: ";
    cin >> key;
    key = lettersNumber - key;
    string::iterator it;
    for (it = str->begin(); it != str->end(); it++) {
        if (*it >= 'A' && *it <= 'Z') {
            *it = char(((*it - 'A') + key) % lettersNumber + 'A');
        } else if (*it >= 'a' && *it <= 'z') {
            *it = char(((*it - 'a') + key) % lettersNumber + 'a');
        }
    }
}


