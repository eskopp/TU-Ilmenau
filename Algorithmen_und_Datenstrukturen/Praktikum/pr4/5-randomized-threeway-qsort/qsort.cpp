#include<iostream>
#include<vector>
#include<algorithm>
#include<random>

std::vector <std::string> A;
std::default_random_engine gen;

int wuerfel(int a, int b) {
    std::uniform_int_distribution<int> verteilung(a, b);
    return verteilung(gen);
}

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

// r_qsort mit dem globalen Array A
// Aufruf r_qsort(l,r) soll A[l..r-1] sortieren!
void r_qsort(const int l, const int r) {
    int p1, p2;

    if (l < r) {
        int s = wuerfel(l, r - 1);
        std::swap(A[l], A[s]);
        partition(l, r, p1, p2);
        r_qsort(l, p1);
        r_qsort(p2 + 1, r);
    }
}

// Hauptschleife
int main() {
    int n;
    while (std::cin >> n) {
        A.resize(n, "");
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