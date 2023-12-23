#include<iostream>
#include<vector>
#include<algorithm>
#include<utility>

std::vector <std::string> A;

// partition mit dem globalen Array A
// Aufruf partition(l,r,p) soll A[l..r-1] mit Pivot A[l] partitionieren
// und Zielposition des Pivotelements über p zurückgeben.
void partition(const int l, const int r, int &p) {
    /* Nach Voraussetzung: 0 <= l < r <= A.size() = n */
    /* TODO */
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

// Hauptschleife
int main() {
    int n, l, r, p;
    while (std::cin >> n >> l >> r) {
        A.resize(n);
        for (std::string &s: A) {
            std::cin >> s;
        }
        partition(l, r, p);
        std::cout << p << " :";
        for (const std::string &s: A) {
            std::cout << " " << s;
        }
        std::cout << std::endl;
    }
}