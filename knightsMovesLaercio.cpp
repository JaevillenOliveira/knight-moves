#include <iostream>
#include <vector>

#define MAX 100

using namespace std;

int m[MAX][MAX], n, o, p, q, r; 
vector<pair<int, int>> moves = {
    {-1, -2}, {-1, 2}, {1, -2}, {1, 2},
    {-2, -1}, {2, -1}, {-2, 1}, {2, 1}
};

void init() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            m[i][j] = 0;
        }
    }
}

bool checkPosition(int x, int y) {
    return (x >= 0) && (x < n)
        && (y >= 0) && (y < n)
        && !m[x][y];
}

int backtracking(int x, int y) {
    if(m[x][y] == n * n) {
        return 1;
    }
    for(auto move: moves) {
        int x2 = x + move.first;
        int y2 = y + move.second;

        if(checkPosition(x2, y2)) {
            m[x2][y2] = m[x][y] + 1;
            if(backtracking(x2, y2)) {
                return 1;
            }
            m[x2][y2] = 0;
        }
    }
    return 0;
}

void show() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(m[i][j] < 10)
                cout << " ";
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    cin >> n;
    cin >> o;
    
    init();

    for(int i = 0; i < o; i++) {
        cin >> p >> q >> r;
        m[p][q] = r;
    }

    // backtracking(0, 0);
    show();
}