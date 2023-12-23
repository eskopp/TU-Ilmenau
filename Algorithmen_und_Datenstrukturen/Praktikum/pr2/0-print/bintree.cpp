#include <iostream>
#include <cassert>
#include <vector>

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
    /*
     * Verwendung:
     * Tree* T = nullptr;
     * std::cout << T << std::endl; // -
     * T = new Tree{nullptr,2,new Tree{nullptr,4,nullptr}};
     * std::cout << T << std::endl; // (-,2,(-,4,-))
     */
    if (!T)
        return out << "-";
    else
        return out << "(" << T->left << "," << T->key << "," << T->right << ")";
}

int main() {
    std::vector < Tree * > trees = {
            nullptr,
            new Tree{nullptr, 13, nullptr},
            new Tree{new Tree{nullptr, 7, nullptr}, 13, new Tree{nullptr, 23, nullptr}},
            new Tree{new Tree{new Tree{nullptr, 0, nullptr}, 7, nullptr}, 13,
                     new Tree{new Tree{nullptr, 21, nullptr}, 23,
                              new Tree{nullptr, 42, new Tree{nullptr, 1337, nullptr}}}}
    };
    for (Tree *t: trees) {
        std::cout << t << std::endl;
        delete t;
    }
    assert(livingTrees == 0);
}