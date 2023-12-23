#include <iostream>
#include "fibonacci.h"

using namespace std;

int main() {
    int i;
    while (cin >> i) {
        cout << fib(i) << endl;
    }
}