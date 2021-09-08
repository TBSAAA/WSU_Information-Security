//
// Created by Jack Huang on 25/7/21.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <cctype>
#include <vector>

#define TotalCharacters 128

using namespace std;

struct letters {
    int alphabets;
    int count;
};

bool comp(const letters &a, const letters &b) {
    return a.count > b.count;
}

void ImportFile(string *);

void keyboardInput(string *);

int main() {
    string str;
    int choice;
    while (true) {
        cout << "1. Import from file\n";
        cout << "2. Keyboard input\n";
        cout << "3. Exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                ImportFile(&str);
                break;
            case 2:
                keyboardInput(&str);
                break;
            case 3:
                return 0;
            default:
                break;
        }
    }
}

void Analyze(string &str) {
    int sum = 0, alphabet[TotalCharacters] = {0};
    vector<letters> vectorLetters;
    letters tem{};
    for (int i = 0; i < (int) str.size(); i++) {
        if (isalpha(str[i])) {
            alphabet[tolower(str[i])]++;
            sum++;
        }
    }
    for (int j = 0; j < TotalCharacters; j++) {
        if (j >= 'a' && j <= 'z') {
            // put into vector, ready to sort
            tem.alphabets = j;
            tem.count = alphabet[j];
            vectorLetters.push_back(tem);
        }
    }
    cout << "Below is the chart display" << endl;

    sort(vectorLetters.begin(), vectorLetters.end(), comp);
    vector<letters>::iterator it;
    for (it = vectorLetters.begin(); it != vectorLetters.end(); it++) {
        cout << (char) it->alphabets << ": ";
        for (int k = 0; k < round((double) it->count / sum * 1000); k++) {
            cout << "■";
        }
        cout << "  percentage: " << round((double) it->count / sum * 1000) / 10 << "%, " << "number: " << it->count
             << endl;
    }

    cout << "sum: " << sum << " total letters.\n" << endl;
}

void ImportFile(string *str) {
    string filename, word;
    cout << "Input a file name (data_in.txt): \n";
    cin >> filename;
    string f = "../" + filename;
    ifstream fin(f);
    if (!fin) {
        cerr << "Cannot open the file!" << endl;
        exit(1);
    }
    *str = "";
    while (!fin.eof()) {
        fin >> word;
        *str += word + " ";
    }
    fin.close();
    cout << filename << " file import success!" << endl;
    Analyze(*str);
}

void keyboardInput(string *str) {
    cout << "Please enter the string: ";
    getline(cin, *str);
    getline(cin, *str);
    Analyze(*str);
}



