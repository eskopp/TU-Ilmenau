#include <iostream>
#include <vector>

int main() {
    int n;
    int e;
    while (true) {
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = n; i != 0; i--) { std::cin >> a[i - 1]; }
        for (int i = 0; i < n; i++) { std::cout << a[i] << " "; }
        std::cout << std::endl;
    }
    return 0;
}
