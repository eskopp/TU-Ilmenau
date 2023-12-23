#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int n, m;
    int i_1, i_2, j_1, j_2;
    int element;

    //Read elements into matrix
    cin >> n >> m;
    vector <vector<int>> vec(n, vector<int>(m, 0));

    for (int c_n = 0; c_n < n; ++c_n) {
        for (int c_m = 0; c_m < m; ++c_m) {
            cin >> element;
            vec[c_n][c_m] = element;
        }
    }

    //Search and Print smallest element in vec 
    while (cin >> i_1 >> j_1 >> i_2 >> j_2) {
        int min = 2147483647; //max value of int

        //Search smallest element in vec[i_1] - vec[v_2] and update min
        for (int c = i_1; c < i_2; ++c) {
            int tmp = *min_element(vec[c].begin() + j_1, vec[c].begin() + j_2 + 1);
            if (tmp < min) { min = tmp; }
        }
        cout << min << endl;
    }
}