#include <iostream>
#include <vector>
#include <algorithm>

//a) (10^4)^3 = 10^12, 10^12 / 10^9 = 10^3 s = 16 min
//b) (10^4)^2 = 10^8, 10^8 / 10^9 = 10^-1 s = 100 ms

int maxsum(const std::vector<int> &A) {
    int best = 0;
    int size = A.size();
    for (int i = 0; i < size; ++i) {
        int tempSum = 0;
        for (int j = i; j < size; ++j) {
            tempSum += A[j];
            if (best < tempSum) { best = tempSum; }
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