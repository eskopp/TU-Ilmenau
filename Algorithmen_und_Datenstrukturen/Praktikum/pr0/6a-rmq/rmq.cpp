#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int size;
    int element;
    int i;
    int j;
    vector<int> vec;

    //Read Elements
    cin >> size;
    for (int c = 0; c < size; ++c) {
        cin >> element;
        vec.push_back(element);
    }
    //Search and Print smallest element in range i - j
    while (cin >> i >> j) {
        cout << *min_element(vec.begin() + i, vec.begin() + j) << endl;
    }
}