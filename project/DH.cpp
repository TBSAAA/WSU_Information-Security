//
// Created by Jack Huang on 13/9/21.
//

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Manually();

void Randomly();

bool Check_prime(int number);

bool Primitive_root(int number, int p);

bool Check_g(int number, int p);

bool Check_p(int number);

bool Check_x(int number, int p);

void Dec_to_bin(int dec, int *bin);

int Power_modulo_operation(int a, int b_dec, int n);

int Cal_num_digits(int input);

struct dh {
    int p, g, x, y, k;
};

void Cal_key(dh *alice, dh *bob);

int main() {
    int choice;
    unsigned seed = time(nullptr);
    srand(seed);
    while (true) {
        cout << "This is Diffie-Hellman Key Exchange system.\n";
        cout << "1. Enter the value manually.\n";
        cout << "2. Enter a value randomly.\n";
        cout << "3. exit\n";
        cin >> choice;
        switch (choice) {
            case 1:
                Manually();
                break;
            case 2:
                Randomly();
                break;
            case 3:
                return 0;
            default:
                break;
        }
    }
}

void Manually() {
    dh alice{}, bob{};
    int tem;
    bool flag = true;

    cout << "All input number must be integer!!\n";
    do {
        cout << "p must be prime number and range is 3 to 100\n";
        cout << "p = ";
        cin >> tem;
        flag = Check_p(tem);
    } while (flag);
    alice.p = bob.p = tem;

    do {
        cout << "g must be prime number too and range is 1 to " << alice.p - 1 << endl;
        cout << "g = ";
        cin >> tem;
        flag = Check_g(tem, alice.p);
    } while (flag);
    alice.g = bob.g = tem;

    do {
        cout << "xa range is 2 to " << alice.p - 1 << endl;
        cout << "xa = ";
        cin >> tem;
        flag = Check_x(tem, alice.p);
    } while (flag);
    alice.x = tem;

    do {
        cout << "xb range is 2 to " << alice.p - 1 << endl;
        cout << "xb = ";
        cin >> tem;
        flag = Check_x(tem, bob.p);
    } while (flag);
    bob.x = tem;

    Cal_key(&alice, &bob);

}

void Randomly() {

    dh alice{}, bob{};
    int tem;
    bool flag = true;


    do {
        // 3-100
        tem = 3 + rand() % 98;
        flag = Check_p(tem);
    } while (flag);
    alice.p = bob.p = tem;

    do {
        // 1-(p-1)
        tem = 1 + rand() % (alice.p - 1);
        flag = Check_g(tem, alice.p);
    } while (flag);
    alice.g = bob.g = tem;

    do {
        // 2-(p-1)
        tem = 2 + rand() % (alice.p - 2);
        flag = Check_x(tem, alice.p);
    } while (flag);
    alice.x = tem;

    do {
        // 2-(p-1)
        tem = 2 + rand() % (alice.p - 2);
        flag = Check_x(tem, bob.p);
    } while (flag);
    bob.x = tem;

    cout << "The random numbers are as follows:" << endl;
    cout << "p = " << alice.p << endl;
    cout << "g = " << alice.g << endl;
    cout << "xa = " << alice.x << endl;
    cout << "xb = " << bob.x << endl;

    Cal_key(&alice, &bob);

}

void Cal_key(dh *alice, dh *bob) {
    alice->y = Power_modulo_operation(alice->g, alice->x, alice->p);
    bob->y = Power_modulo_operation(bob->g, bob->x, bob->p);
    alice->k = Power_modulo_operation(bob->y, alice->x, alice->p);
    bob->k = Power_modulo_operation(alice->y, bob->x, bob->p);
    cout << "alice's key = " << alice->k << endl;
    cout << "bob's key = " << bob->k << endl;
    cout << endl << endl;
}

int Power_modulo_operation(int a, int b_dec, int n) {
    int c = 0, d = 1, index;
    // Calculate how big the array is.
    index = Cal_num_digits(b_dec);
    int b_bin[index];
    // Convert decimal to binary.
    Dec_to_bin(b_dec, b_bin);
    for (index = index - 1; index >= 0; index--) {
        c *= 2;
        d = d * d % n;
        if (b_bin[index] == 1) {
            c += 1;
            d = d * a % n;
        }
    }
    return d;
}

// Calculate how big the array is.
int Cal_num_digits(int input) {
    int size = 0;
    while (input) {
        input /= 2;
        size++;
    }
    return size;
}

// Decimal to Binary
void Dec_to_bin(int dec, int *bin) {
    int i = 0;
    while (dec) {
        bin[i] = dec % 2;
        dec /= 2;
        i++;
    }
}

bool Check_x(int number, int p) {
    // range
    if (number < 2 || number > p - 1)
        return true;
    return false;
}

bool Check_g(int number, int p) {
    // range
    if (number < 1 || number > p - 1)
        return true;
    // Primitive Root
    if (!Primitive_root(number, p))
        return false;
    return true;
}

bool Check_p(int number) {
    // range
    if (number < 3 || number > 100)
        return true;
    // prime number
    if (Check_prime(number))
        return false;
    return true;
}

bool Primitive_root(int g, int p) {
    bool check[p - 1];
    int location;
    // Initially all set to false
    memset(check, false, sizeof(check));
    for (int i = 1; i < p; i++) {
        // Get array number
        location = Power_modulo_operation(g, i, p) - 1;
        if (!check[location]) {
            check[location] = true;
        } else
            return true;
    }
    return false;
}

bool Check_prime(int number) {
    for (int i = 2; i <= number; i++) {
        if (number % i == 0 && i != number)
            return false;
    }
    return true;
}

