#include <iostream>
#include <vector>
#include <algorithm>

struct Sum {
    int i, j, s;
};

std::ostream &operator<<(std::ostream &s, const Sum &x) {
    return s << "(" << x.i << "," << x.j << "," << x.s << ")";
}

bool operator<(const Sum &x, const Sum &y) {
    if (x.i < y.i) { return true; }
    if (x.i == y.i) {
        if (x.j <= y.j) { return true; }
        else { return false; }
    } else { return false; }
}

Sum maxsum(const std::vector<int> &A) {
    Sum best{0, -1, 0};
    Sum temp{0, -1, 0};
    for (int i = 0; i < A.size(); ++i) {
        int e = A[i];
        if (temp.s + e >= 0) { temp.s += e; }
        else {
            if (e == 0) {
                temp.s = 0;
            } else {
                temp.i = i + 1;
                temp.s = 0;
            }
        }
        if (temp.s == best.s) {
            temp.j = i;
            if (temp < best) {
                best = temp;
            }
        }
        if (temp.s > best.s) {
            temp.j = i;
            best = temp;
        }
    }
    return best;
}

int main() {
    int size;
    while (std::cin >> size) {
        std::vector<int> v(size);
        for (int &x: v) std::cin >> x;
        std::cout << maxsum(v) << std::endl;
    }
}