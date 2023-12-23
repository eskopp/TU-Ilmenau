#include <iostream>

using namespace std;

struct List {
    int data;
    List *next;

    List(int d, List *l) {
        data = d;
        next = l;
    }

    ~List() {}
};

int main() {
    int size;
    int element;
    List *head = nullptr;
    while (cin.good()) {
        cin >> size;
        for (int i = 0; i < size; ++i) {
            cin >> element;
            List *temp = new List(element, head);
            head = temp;
        }
        while (head != nullptr) {
            element = head->data;
            List *temp = head;
            head = head->next;
            delete temp;
            if (head == nullptr) {
                cout << element << endl;
            } else {
                cout << element << " ";
            }
        }
        size = 0;
        head = nullptr;
    }
}
