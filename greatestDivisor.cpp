//
// Created by Jack Huang on 16/8/21.
//

#include <iostream>

using namespace std;

void swap(int &A, int &B){
    int tem = A;
    A = B;
    B = tem;
}

int gcd(int A, int B) {
    if (A == 0)
        return B;

    if (B == 0)
        return A;

    if (A > B)
        swap(A, B);

    for (int R = A % B; R > 0; R = A % B) {
        A = B;
        B = R;
    }
    return B;
}

int main(){
    int numberA, numberB, result;
    cout << "Please input the two integers" << endl;
    cout << "first number: ";
    cin >> numberA;
    cout << "second number: ";
    cin >> numberB;
    cout << "Input two numbers are " << numberA<<", "<< numberB << endl;
    result = gcd(numberA, numberB);
    cout << "The greatest divisor is: "<< result << endl;
}

