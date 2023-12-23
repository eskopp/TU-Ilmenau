#include <iostream>

struct Point {
    int x, y;
};

int main() {
    Point p1;
    Point p2;
    char c;
    while (std::cin >> c >> p1.x >> c >> p1.y >> c >> c >> p2.x >> c >> p2.y >> c) {
        std::cout << "(" << p1.x + p2.x << "," << p1.y + p2.y << ")" << std::endl;
    }
    return 0;
}
