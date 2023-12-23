#include <iostream>

using namespace std;

int living;

struct List {
    int data;
    List *next;

    List(int d, List *l) {
        ++living;
        data = d;
        next = l;
    }

    ~List() {
        --living;
        if (next != nullptr) {
            delete next;
        }
        next = nullptr;
    }
};

int main() {
    int pos;
    int element;
    List *head = nullptr;
    List *temp;
    while (cin >> pos && cin >> element) {
        //create first Element
        if (head == nullptr) {
            head = new List(element, nullptr);
        }

            //insert element
        else {
            temp = head;
            while (temp->data != pos && temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = new List(element, temp->next);
        }

        //print elements
        temp = head;
        while (temp != nullptr) {
            element = temp->data;
            temp = temp->next;
            if (temp == nullptr) {
                cout << element << endl;
            } else {
                cout << element << " ";
            }
        }
    }
    if (head != nullptr) {
        delete head;
    }
}