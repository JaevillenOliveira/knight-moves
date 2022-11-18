#include <iostream>
#include <vector>
#include <utility>
#include <set>
#include <map>

#define MAX 100

using namespace std;

int m[MAX][MAX], n, o, p, q, r, startX = 0, startY = 0, startValue = 1;
set<int> values;
map<int, pair<int, int>> v;
bool hasFirst = false;
vector<pair<int, int>> moves = {
    {-1, -2}, {-1, 2}, {1, -2}, {1, 2},
    {-2, -1}, {2, -1}, {-2, 1}, {2, 1}
};

void show() {
    cout << endl;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            if(m[i][j] < 10)
                cout << " ";
            cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

void init() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            m[i][j] = 0;
        }
    }
}

bool checkPosition(int x, int y, int x2, int y2) {
    return (x >= 0) && (x < n)
        && (y >= 0) && (y < n)
        && (!m[x][y] || m[x][y] == m[x2][y2] + 1);
}

int backtracking(int x, int y) {
    if(m[x][y] == n * n) {
        return 1;
    }
    for(auto move: moves) {
        int x2 = x + move.first;
        int y2 = y + move.second;

        if(checkPosition(x2, y2, x, y)) {
            m[x2][y2] = m[x][y] + 1;
            if(backtracking(x2, y2)) {
                return 1;
            }
            m[x2][y2] = 0;
        }
    }
    return 0;
}

int main() {
    cin >> n;
    cin >> o;
    
    init();

    for(int i = 0; i < o; i++) {
        cin >> p >> q >> r;
        m[p][q] = r;
        v[r] = make_pair(p, q);
    }

    map<int, pair<int, int>>::iterator it=v.begin();
    for (int i = 1; it!=v.end(); ++it, i++) {
        if(it->first == i) {
            startX = it->second.first;
            startY = it->second.second;
            startValue = i+1;
        } else {
            break;
        }
    }

    if(startValue == 1) {
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(!m[i][j]) {
                    m[i][j] = startValue;
                    if(backtracking(i, j)) {
                        show();
                    }
                    m[i][j] = 0;
                }
            }
        }
    } else {
        if(backtracking(startX, startY)) {
            show();
        }
    }
}

/*
5
3
0 0 1
1 4 4
4 1 6
*/
/*
10
8
0 0 12
1 6 5
1 8 23
3 3 14
5 1 2
6 4 20
7 4 33
9 9 28
*/