#include<iostream>
#include<vector>
#include<algorithm>

std::vector <std::string> A;

// partition mit dem globalen Array A
// Aufruf partition(l,r,p1,p2) soll A[l..r-1] mit Pivot A[l] partitionieren
// und Bereichsgrenzen über p1 und p2 zurückgeben.
void partition(const int l, const int r, int &p1, int &p2) {
    /* Nach Voraussetzung: 0 <= l < r <= A.size() = n */
    int red = l;
    int white = l;
    int blue = r - 1;
    std::string pivot = A[l];
    while (white <= blue) {
        if (A[white] < pivot) {
            std::swap(A[white++], A[red++]);
        } else if (A[white] > pivot) {
            std::swap(A[white], A[blue--]);
        } else {
            ++white;
        }
    }
    p1 = red;
    p2 = blue;
}

// Hauptschleife
int main() {
    int n, l, r, p1, p2;
    while (std::cin >> n >> l >> r) {
        A.resize(n);
        for (std::string &s: A) {
            std::cin >> s;
        }
        partition(l, r, p1, p2);
        std::cout << p1 << " " << p2 << " :";
        for (const std::string &s: A) {
            std::cout << " " << s;
        }
        std::cout << std::endl;
    }
}