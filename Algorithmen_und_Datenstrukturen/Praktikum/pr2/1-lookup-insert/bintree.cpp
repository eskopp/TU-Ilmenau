#include <iostream>
#include <cassert>

int livingTrees = 0;

struct Tree {
    Tree *left;
    int key;
    Tree *right;

    Tree(Tree *l, int k, Tree *r) : left(l), key(k), right(r) {
        ++livingTrees;
    }

    ~Tree() {
        delete left;
        delete right;
        --livingTrees;
    }
};

std::ostream &operator<<(std::ostream &out, const Tree *T) {
    if (!T)
        return out << "-";
    else
        return out << "(" << T->left << "," << T->key << "," << T->right << ")";
}

bool lookup(const Tree *T, const int key) {
    /*
     * Verwendung:
     * Tree* T = new Tree{nullptr,2,nullptr}; // T == (-,2,-)
     * bool b = lookup(T, 4); // T == (-,2,-), b == false
     */
    /* TODO */

    if (T == nullptr) {
        return false;
    }
    if (T->key == key) {
        return true;
    }
    if (T->key < key) {
        return lookup(T->right, key);
    } else {
        return lookup(T->left, key);
    }
}

Tree *insert(Tree *T, const int key) {
    /*
     * Verwendung:
     * Tree* T = nullptr; // T == -
     * T = insert(T, 2);  // T == (-,2,-)
     * T = insert(T, 4);  // T == (-,2,(-,4,-))
     */
    /* TODO */
    if (T == nullptr) {
        Tree *new_T = new Tree{nullptr, key, nullptr};
        return new_T;
    }
    if (T->key == key) {
        return T;
    }
    if (T->key < key) {
        T->right = insert(T->right, key);
        return T;
    } else {
        T->left = insert(T->left, key);
        return T;
    }
}

int main() {
    char c;
    int key;
    Tree *T = nullptr;
    while (std::cin >> c >> key) {
        /* TODO */
        if (c == 'i') {
            T = insert(T, key);
            std::cout << T << std::endl;
        }
        if (c == 'l') {
            std::cout << lookup(T, key) << std::endl;
        }
    }
    delete T;
    T = nullptr;
    assert(livingTrees == 0);
}