#include <iostream>
#include <vector>
#include <algorithm>

int maxsum(const std::vector<int> &A) {
    int best = 0;
    int temp = 0;
    for (int e: A) {
        if (temp + e > 0) { temp += e; }
        else { temp = 0; }
        if (temp > best) { best = temp; }
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