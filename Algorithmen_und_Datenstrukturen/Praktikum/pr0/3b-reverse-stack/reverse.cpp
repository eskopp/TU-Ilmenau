#include <iostream>
#include <stack>

using namespace std;

int main() {
    stack<int> s;
    int size;
    int element;
    while (cin.good()) {
        cin >> size;
        for (int i = 0; i < size; ++i) {
            cin >> element;
            s.push(element);
        }
        while (!s.empty()) {
            element = s.top();
            s.pop();
            if (s.empty()) {
                cout << element << endl;
            } else {
                cout << element << " ";
            }
        }
        size = 0;
        element = 0;
    }
}
