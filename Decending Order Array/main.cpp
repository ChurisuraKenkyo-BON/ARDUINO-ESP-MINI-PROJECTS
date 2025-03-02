#include <bits/stdc++.h>

using namespace std;

struct oop{
    char ar[10];
    void inputting(char a, int b);
    void original(int b);
    void reversee(int b);
};

void oop::inputting(char a, int b){
    ar[b] = a;
}

void oop::original(int b){
    for (int i = 0; i < b; i++){
        cout << ar[i];
    }
}

void oop::reversee(int b){
    for (int i = b; i >= 0; i--){
        cout << ar[i];
    }
}


int main(){
    oop call;
    string input;
    cout << "Enter your 5-characters string: ";
    cin >> input;
    for (int i = 0; i < input.length(); i++){
         call.inputting(input.at(i), i);
    }
    cout << "\nORIGINAL FORM" << endl;
    call.original(input.length());
    cout << "\nREVERSE FORM" << endl;
    call.reversee(input.length());
    return 0;
}
