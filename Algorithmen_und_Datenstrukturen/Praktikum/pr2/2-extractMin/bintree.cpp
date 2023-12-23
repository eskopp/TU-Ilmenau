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

Tree *extractMin(Tree *T, int &minKey) {
    /*
     * Verwendung:
     * Tree* T = new Tree{nullptr,2,new Tree{nullptr,4,nullptr}}; // T == (-,2,(-,4,-))
     * int k; // k == undefiniert
     * T = extractMin(T, k); // T == (-,4,-), k == 2
     */
    /* TODO */
    if (T == nullptr) {
        minKey = -1;
        return T;
    }
    // Wenn es einen linken Weg gibt, dann Folge ihm
    if (T->left != nullptr) {
        T->left = extractMin(T->left, minKey);
        return T;
    }
        // Gibt es keinem linken Weg, dann ist das minimale Element gefunden
    else {
        minKey = T->key;
        Tree *new_T = T->right;
        T->right = nullptr;
        delete T;
        return new_T;
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
        if (c == 'e') {
            int min = 0;
            T = extractMin(T, min);
            std::cout << min << " " << T << std::endl;
        }
    }
    delete T;
    T = nullptr;
    assert(livingTrees == 0);
}