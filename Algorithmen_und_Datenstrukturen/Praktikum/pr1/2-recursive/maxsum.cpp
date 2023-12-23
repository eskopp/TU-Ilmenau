#include <iostream>
#include <vector>
#include <algorithm>


int maxsum(const std::vector<int> &A) {
    /* Schritt 0: Trivialitätstest */
    if (A.size() == 0) { return 0; }
    if (A.size() == 1) { return A[0]; }

    /* Schritt 1: Teile */
    int m = A.size() / 2;
    const std::vector<int> Aleft(A.begin(), A.begin() + m);
    const std::vector<int> Aright(A.begin() + m, A.end());

    /* Schritt 2: Rekursion */
    const int r1 = maxsum(Aleft);
    const int r2 = maxsum(Aright);

    /* Schritt 3: Kombiniere */
    int best = 0;
    int bestL = 0;

    int bestR = 0;
    int temp = 0;
    //Find MaxSum from middle to right site
    for (int i = 0; i < Aright.size(); ++i) {
        temp += Aright[i];
        if (bestR < temp) { bestR = temp; }
    }
    //Find MaxSum from middle to left site
    temp = 0;
    for (int i = Aleft.size() - 1; i >= 0; --i) {
        temp += Aleft[i];
        if (bestL < temp) { bestL = temp; }
    }
    //Test if MaxSum goes over the middle of the array 
    if (bestL + bestR > r1 && bestL + bestR > r2) {
        best = bestL + bestR;
    }
        //MaxSum doesn´t go over the middle of the array, test in which site of the array is MaxSum
    else {
        if (r1 > r2) { best = r1; }
        else { best = r2; }
    }
    return best;
}

int maxsumtest(const std::vector<int> &A) {
    //Test if MaxSum >= 0 else set it to 0
    int sum = maxsum(A);
    if (sum >= 0) { return sum; }
    else { return 0; }
}

int main() {
    int size;
    while (std::cin >> size) {
        std::vector<int> v(size);
        for (int &x: v) std::cin >> x;
        std::cout << maxsumtest(v) << std::endl;
    }
}