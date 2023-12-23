#include<iostream>
#include<vector>
#include<algorithm>

std::vector <std::string> A;

void partition(const int l, const int r, int &p) {
    /* Nach Voraussetzung: 0 <= l < r <= A.size() = n */
    int i = l + 1;
    int j = r - 1;
    std::string pivot = A[l];
    while (i <= j) {
        while (i <= j && A[i] <= pivot) { ++i; }
        while (i < j && A[j] > pivot) { --j; }
        if (i == j) { --j; }
        if (i < j) { std::swap(A[i++], A[j--]); }
    }
    if (l < j) { std::swap(A[l], A[j]); }
    p = j;
}

// r_qsort mit dem globalen Array A
// Aufruf r_qsort(l,r) soll A[l..r-1] sortieren!
void r_qsort(const int l, const int r) {
    int p;
    if (l < r) {
        partition(l, r, p);
        r_qsort(l, p);
        r_qsort(p + 1, r);
    }
}

// Hauptschleife
int main() {
    int n;
    while (std::cin >> n) {
        A.resize(n);
        for (std::string &s: A) {
            std::cin >> s;
        }
        r_qsort(0, n);
        if (n > 0) {
            std::cout << A[0];
            for (int i = 1; i < (int) A.size(); ++i) {
                std::cout << " " << A[i];
            }
        }
        std::cout << std::endl;
    }
}