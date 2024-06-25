#include <bits/stdc++.h>
using namespace std;
struct Psa {
    vector<vector<int>> psa;  
    int n, m;

    Psa() {}
    Psa(int n, int m) : n(n), m(m), psa(vector<vector<int>>(n, vector<int>(m, 0))) {}

    Psa(vector<vector<int>> const &a) : n(a.size()), m(a[0].size()), psa(a) {
        for (int i = 1; i < m; i++) psa[0][i] += psa[0][i-1];
        for (int i = 1; i < n; i++) psa[i][0] += psa[i-1][0];
        for (int i = 1; i < n; i++) {
            for (int j = 1; j < m; j++) {
                psa[i][j] += psa[i-1][j] + psa[i][j-1] - psa[i-1][j-1];
            }
        }
    }

    int q(int x, int y) const {
        if (x < 0 || y < 0) return 0;
        return psa[x][y];
    }

    int sum(int x1, int y1, int x2, int y2) const {
        return q(x2, y2)-q(x1-1, y2)-q(x2, y1-1)+q(x1-1,y1-1);
    }
};

int main() {
    vector<vector<int>> g(10, vector<int>(10, 0));
    g[1][2] = 1;
    g[3+1][4+1] = 1;
    g[1][4+1] = -1;
    g[3+1][2] = -1;
    g[4][5] = 1;
    Psa psa(g);
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 ;j++) {
            cout << psa.psa[i][j] << " ";
        } cout << "\n";
    }
}