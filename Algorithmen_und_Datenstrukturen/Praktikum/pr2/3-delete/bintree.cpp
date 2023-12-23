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

Tree *erase(Tree *T, const int key) {
    /*
     * Verwendung:
     * Tree* T = new Tree{nullptr,2,new Tree{nullptr,4,nullptr}}; // T == (-,2,(-,4,-))
     * T = erase(T, 4); // T == (-,2,-)
     */
    /* TODO */
    if (T == nullptr) {
        return T;
    }
    // Wenn der gesuchte Schlüssel größer ist als der aktuelle, dann suche im rechten Unterbaum weiter
    if (T->key < key) {
        T->right = erase(T->right, key);
        return T;
    }
    // Wenn der gesuchte Schlüssel kleiner ist als der aktuelle, dann suche im linken Unterbaum weiter
    if (T->key > key) {
        T->left = erase(T->left, key);
        return T;
    }

    if (T->key == key) {
        // Hat der gefundene Schlüssel zwei nichtleere Unterbäume, so tausche den Schlüssel mit dem durch exractMin im rechten Unterbaum gefundenen Schlüssel
        if (T->left != nullptr && T->right != nullptr) {
            int min = 0;
            T->right = extractMin(T->right, min);
            T->key = min;
            return T;
        }
        // Hat der gefundene Schlüssel nur einen linken Unterbaum, so kann der einfach an den Elternknoten gehängt werden
        if (T->left != nullptr) {
            Tree *new_T = T->left;
            T->left = nullptr;
            delete T;
            return new_T;
        }
            // Hat der gefundene Schlüssel nur einen rechten oder einen leeren Unterbaum, so kann der einfach an den Elternknoten gehängt werden
        else {
            Tree *new_T = T->right;
            T->right = nullptr;
            delete T;
            return new_T;
        }
    }
}

int main() {
    char c;
    int key;
    Tree *T = nullptr;
    bool out_flag = true;
    while (std::cin >> c >> key) {
        /* TODO */
        if (c == 'i') {
            T = insert(T, key);
            if (out_flag) { std::cout << T << std::endl; }
        }
        if (c == 'l') {
            std::cout << lookup(T, key) << std::endl;
        }
        if (c == 'e') {
            int min = 0;
            T = extractMin(T, min);
            if (out_flag) { std::cout << min << " " << T << std::endl; }
        }
        if (c == 'd') {
            T = erase(T, key);
            if (out_flag) { std::cout << T << std::endl; }
        }
        // Ausgabe wird aktiviert oder deaktiviert
        if (c == 'p') {
            key == 0 ? out_flag = false : out_flag = true;
        }
    }
    delete T;
    T = nullptr;
    assert(livingTrees == 0);
}